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

#include <ctime>
#include <utility>
#include <random>

#include "ssiglib/core/pso.hpp"

#include "ssiglib/core/math.hpp"

static std::mt19937 gen(static_cast<uint>(time(nullptr)));

namespace ssig {
std::unique_ptr<PSO> PSO::create(
  UtilityFunctor& utilityFunction,
  DistanceFunctor& distanceFunction) {
  struct _PSO : PSO {
    _PSO(UtilityFunctor& utilityFunction,
      DistanceFunctor& distanceFunction) :
      PSO(utilityFunction,
          distanceFunction) {};
  };

  return std::unique_ptr<ssig::PSO>(new _PSO(
    utilityFunction,
    distanceFunction));
}

void PSO::setup(cv::Mat_<float>& input) {
  if (input.empty()) {
    for (int i = 0; i < mPopulationLength; ++i) {
      cv::Mat row = randomVector(mDimensions,
                                 mPopulationConstraint.first,
                                 mPopulationConstraint.second);
      mPopulation.push_back(row);
    }
  } else {
    mPopulation = input;

    double min, max;
    cv::minMaxIdx(mPopulation, &min, &max);
    mPopulationConstraint = std::make_pair(static_cast<float>(min) - 25,
                                           static_cast<float>(max) - 50);
  }
  for (int i = 0; i < mPopulationLength; ++i) {
    cv::Mat row = randomVector(mDimensions,
                               mPopulationConstraint.first - 15,
                               2 * mPopulationConstraint.second);
    mVelocities.push_back(row);
  }

  mDimensions = mPopulation.cols;
  mPopulationLength = mPopulation.rows;
  if (mInertia.empty())
    mInertia = cv::Mat_<float>::ones(1, 3);
  mInertia.convertTo(mInertia, CV_32F);
  mLocalBests = mPopulation.clone();
  mLocalUtils.resize(mPopulationLength);
  mUtilities = cv::Mat_<float>::zeros(mPopulationLength, 1);

  for (int i = 0; i < mPopulationLength; ++i) {
    cv::Mat row = mPopulation.row(i);
    float util = utility(row);
    mLocalUtils[i] = util;
    mUtilities.at<float>(i) = util;
    if (util > mBestUtil) {
      mBestUtil = util;
      mBestPosition = row.clone();
    }
  }
}

void PSO::learn(cv::Mat_<float>& input) {
  setup(input);

  float pastUtil = -FLT_MAX;
  for (int it = 0; it < mMaxIterations; ++it) {
    iterate();
    if (std::abs(mBestUtil - pastUtil) < mEps)
      break;
    pastUtil = mBestUtil;
  }
}

void PSO::iterate() {
  #pragma omp parallel for
  for (int r = 0; r < mPopulationLength; ++r) {
    cv::Mat position = mPopulation.row(r),
        localBest = mLocalBests.row(r),
        vel = mVelocities.row(r);
    update(mBestPosition, localBest, mInertia, vel, position);

    float currentUtil = utility(position);
    mLocalUtils[r] = currentUtil;

    #pragma omp critical(UPDATING)
    if (currentUtil >= mBestUtil) {
      mBestPosition = position.clone();
      mBestUtil = currentUtil;
    } else if (currentUtil >= mUtilities.at<float>(r)) {
      localBest = position;
      mUtilities.at<float>(r) = currentUtil;
    }
  }
}

cv::Mat PSO::getInertia() const {
  return mInertia;
}

void PSO::setInertia(const cv::Mat& inertia) {
  mInertia = inertia;
}

int PSO::getPopulationLength() const {
  return mPopulationLength;
}

void PSO::setPopulationLength(const int populationLength) {
  mPopulationLength = populationLength;
}

void PSO::setDimensionality(int d) {
  mDimensions = d;
}

std::pair<float, float> PSO::getPopulationConstraint() const {
  return mPopulationConstraint;
}

void PSO::setPopulationConstraint(const float minRange,
  const float maxRange) {
  mPopulationConstraint = {minRange, maxRange};
}

cv::Mat PSO::getBestPosition() const {
  return mBestPosition;
}

float PSO::getBestUtil() const {
  return mBestUtil;
}

PSO::PSO(UtilityFunctor& utility,
  DistanceFunctor& distance) :
  Optimization(utility, distance) {}

void PSO::update(const cv::Mat& globalBest,
  const cv::Mat& localBest,
  const cv::Mat& inertia,
  cv::Mat& velocity,
  cv::Mat& position) {
  static std::uniform_real_distribution<float> dist(0.0f, 1000.0f);

  float R1 = (dist(gen)) / 1000.f;
  float R2 = (dist(gen)) / 1000.f;
  // v = w_1*v + w_2*R1(LB - X)+ w_3*R2(GB - X) :
  cv::Mat term1 = velocity * inertia.at<float>(0);
  cv::Mat term2 = (localBest - position) * inertia.at<float>(1) * R1;
  cv::Mat term3 = (globalBest - position) * (inertia.at<float>(2) * R2);

  velocity = term1 + term2 + term3;

  // X = X + v :
  position = position + velocity;
}

}  // namespace ssig


