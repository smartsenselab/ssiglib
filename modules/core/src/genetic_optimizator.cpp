/*L*****************************************************************************
*
*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install, copy
*  or use the software.
*
*                Software License Agreement (BSD License)
*             For Smart Surveillance Interest Group Library
*                         http://ssig.dcc.ufmg.br
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#include "ssiglib/core/genetic_optimizator.hpp"
// c++
#include <vector>
#include <algorithm>
#include <random>
// ssiglib
#include <ssiglib/core/math.hpp>
#include <ssiglib/core/util.hpp>


static std::mt19937 gen(static_cast<uint>(time(nullptr)));

namespace ssig {
cv::Ptr<GeneticOptimizator> GeneticOptimizator::create(
  const int seed,
  cv::Ptr<UtilityFunctor>& utilityFunction,
  cv::Ptr<CrossOverFunctor>& crossOverFunction) {
  struct _Gen : GeneticOptimizator {
    _Gen(cv::Ptr<UtilityFunctor> utilityFunction,
         cv::Ptr<CrossOverFunctor> crossover) :
      GeneticOptimizator(utilityFunction,
                         crossover) {}
  };

  auto ans = cv::makePtr<_Gen>(
                               utilityFunction,
                               crossOverFunction);
  ans->setSeed(seed);
  return ans;
}

void GeneticOptimizator::learn(const cv::Mat_<float>& input) {
  setup(input);

  float pastUtil = -FLT_MAX;
  for (int it = 0; it < mMaxIterations; ++it) {
    iterate();
    if (std::abs(mBestUtil - pastUtil) < mEps)
      break;
    pastUtil = mBestUtil;
  }
  mUtilities = cv::Mat_<float>::zeros(mPopulationLength, 1);
  #ifdef _OPENMP
  #pragma omp parallel for
  #endif
  for (int p = 0; p < mPopulationLength; ++p) {
    mUtilities.at<float>(p) = (*utility)(mPopulation.row(p));
  }
}

void GeneticOptimizator::setup(const cv::Mat_<float>& input) {
  mPopulation = input;
  if (mPopulation.empty()) {
    mPopulation = cv::Mat_<float>::zeros(mPopulationLength, mDimensions);
    for (int i = 0; i < mPopulationLength; ++i) {
      for (int d = 0; d < mDimensions; ++d) {
        std::uniform_real_distribution<float> randu(-5.f, 5.f);
        mPopulation.at<float>(i, d) = randu(gen);
      }
    }
  }
}

void GeneticOptimizator::iterate() {
  // evaluation
  cv::Mat_<float> popUtil = cv::Mat_<float>::zeros(mPopulationLength, 1);
  #ifdef _OPENMP
  #pragma omp parallel for
  #endif
  for (int p = 0; p < mPopulationLength; ++p) {
    popUtil.at<float>(p) = (*utility)(mPopulation.row(p));
  }
  cv::exp(popUtil, popUtil);
  cv::normalize(popUtil, popUtil, 1, 0, cv::NORM_L1);

  int newPopLen = static_cast<int>(mPopulationLength * (1 - mElistimFactor));

  // reproduction
  cv::Mat newPopulation;
  applyReproduction(mPopulation, popUtil,
                    newPopLen,
                    *crossOver,
                    mBestUtil,
                    newPopulation);
  // mutation
  applyMutation(
                mMutationRate,
                mMutationType,
                newPopulation,
                static_cast<int>(mMutationRange.x),
                static_cast<int>(mMutationRange.y),
                mRng,
                newPopulation);
}

int GeneticOptimizator::getPopulationLength() const {
  return mPopulationLength;
}

void GeneticOptimizator::setPopulationLength(const int populationLength) {
  mPopulationLength = populationLength;
}

double GeneticOptimizator::getElistimFactor() const {
  return mElistimFactor;
}

void GeneticOptimizator::setElistimFactor(const double elistimFactor) {
  mElistimFactor = elistimFactor;
}

double GeneticOptimizator::getMutationRate() const {
  return mMutationRate;
}

void GeneticOptimizator::setMutationRate(const double mutationRate) {
  mMutationRate = mutationRate;
}

cv::Point2d GeneticOptimizator::getMutationRange() const {
  return mMutationRange;
}

void GeneticOptimizator::setMutationRange(const cv::Point2d& mutationRange) {
  mMutationRange = mutationRange;
}

GeneticOptimizator::MutationType GeneticOptimizator::getMutationType() const {
  return mMutationType;
}

void GeneticOptimizator::setMutationType(const MutationType mutationType) {
  mMutationType = mutationType;
}

float GeneticOptimizator::getBestUtil() const {
  return mBestUtil;
}

void GeneticOptimizator::setSeed(int seed) {
  mRng.state = static_cast<uint64>(seed);
}

int GeneticOptimizator::getSeed() const {
  return static_cast<int>(mRng.state);
}

int GeneticOptimizator::getDimensions() const {
  return mDimensions;
}

void GeneticOptimizator::setDimensions(const int dimensions) {
  mDimensions = dimensions;
}

GeneticOptimizator::GeneticOptimizator(
  cv::Ptr<UtilityFunctor>& utilityFunction,
  cv::Ptr<CrossOverFunctor>& crossOverFunction)
  : crossOver(crossOverFunction), utility(utilityFunction),
    mPopulationLength(100), mElistimFactor(0.1),
    mMutationRate(0.1) { }

GeneticOptimizator::GeneticOptimizator(GeneticOptimizator& rhs) {
  setEps(getEps());
  setMaxIterations(getMaxIterations());

  setElistimFactor(rhs.getElistimFactor());
  setSeed(rhs.getSeed());
  setMutationRange(getMutationRange());
  setMutationType(getMutationType());
  setPopulationLength(getPopulationLength());

  crossOver = rhs.crossOver;
  utility = rhs.utility;
}

void GeneticOptimizator::applyReproduction(
  const cv::Mat& pop,
  const cv::Mat& utilities,
  const int newPopLen,
  const CrossOverFunctor& crossover,
  float& bestUtil,
  cv::Mat& newPop) {
  cv::Mat_<int> ordering;
  cv::sortIdx(utilities, ordering, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  bestUtil = utilities.at<float>(ordering.at<int>(utilities.rows - 1));

  std::vector<float> raffles(newPopLen);
  for (int i = 0; i < static_cast<int>(raffles.size()); ++i) {
    raffles[i] = cv::theRNG().uniform(0.f, 1.f);
  }
  std::vector<int> parents(raffles.size());
  std::sort(raffles.begin(), raffles.end());
  int rafflePtr = 0;
  for (int p = 0; p < pop.rows; ++p) {
    if (raffles[rafflePtr] <= utilities.at<float>(ordering.at<int>(p))) {
      parents[rafflePtr] = ordering.at<int>(p);
      ++rafflePtr;
    }
  }
  parents.resize(rafflePtr);
  newPop = cv::Mat::zeros(pop.rows, pop.cols, CV_32F);
  std::shuffle(parents.begin(), parents.end(),
               std::default_random_engine(static_cast<uint>(time(nullptr))));
  int popPtr = -1;
  const int nParents = static_cast<int>(parents.size());
  for (int p = 0; p < nParents; ++p) {
    const auto& parentA = parents[p];
    const auto& parentB = parents[(p + 1) % nParents];
    cv::Mat child = newPop.row(++popPtr);
    crossover(
              pop.row(parentA),
              pop.row(parentB),
              child);
  }
  for (++popPtr; popPtr < pop.rows; ++popPtr) {
    newPop.row(popPtr) = pop.row(ordering.at<int>(popPtr - nParents)) + 0;
  }
}

void GeneticOptimizator::applyMutation(
  const double mutationRate,
  const MutationType type,
  const cv::Mat& pop,
  const int infLim,
  const int supLim,
  cv::RNG& rng,
  cv::Mat& newPop) {
  cv::Mat ans = pop.clone();
  float left = static_cast<float>(infLim),
      right = static_cast<float>(supLim);

  for (int i = 0; i < pop.rows; ++i) {
    float raffle = cv::theRNG().uniform(0.f, 1.f);
    if (raffle < mutationRate) {
      switch (type) {
      case Gaussian: {
        cv::Mat mu = cv::Mat::zeros(1, 1, CV_32F),
            sigma = cv::Mat::zeros(1, 1, CV_32F);
        cv::Mat noise(1, pop.cols, CV_32F);
        rng.fill(noise, cv::RNG::NORMAL, mu, sigma);
        ans.row(i) = pop.row(i) + noise;
      }
        break;
      case Uniform: {
        int selectedFeat = rng.uniform(0, pop.cols);

        ans.at<float>(i, selectedFeat) = rng.uniform(left, right);
      }
        break;
      case Boundary: {
        int selectedFeat = rng.uniform(0, pop.cols);
        int flip = rng.uniform(0, 1);
        ans.at<float>(i, selectedFeat) = (flip) ? left : right;
      }
        break;
      default: break;
      }
    }
  }
  newPop = ans;
}

}  // namespace ssig
