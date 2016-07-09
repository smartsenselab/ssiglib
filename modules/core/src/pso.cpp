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

#include <opencv2/core.hpp>

#include "ssiglib/core/pso.hpp"
#include "ssiglib/core/math.hpp"

static std::mt19937 gen(static_cast<uint>(time(nullptr)));

namespace ssig {
cv::Ptr<PSO> PSO::create(
  cv::Ptr<UtilityFunctor>& utilityFunction,
  cv::Ptr<DistanceFunctor>& distanceFunction) {
  struct _PSO : PSO {
    _PSO(cv::Ptr<UtilityFunctor> utilityFunction,
      cv::Ptr<DistanceFunctor> distanceFunction) :
      PSO(utilityFunction,
      distanceFunction) {};
  };

  return cv::makePtr<_PSO>(utilityFunction,
    distanceFunction);
}

void PSO::setup(const cv::Mat_<float>& input) {
  if (input.empty()) {
    mPopulation = cv::Mat_<float>::zeros(mPopulationLength, mDimensions);
    for (int i = 0; i < mPopulationLength; ++i) {
      for (int d = 0; d < mDimensions; ++d) {
        std::uniform_real_distribution<float> randu(mMinRange.at<float>(d),
          mMaxRange.at<float>(d));
        mPopulation.at<float>(i, d) = randu(gen);
      }
    }
  } else {
    mPopulation = input;
    const int D = mPopulation.cols;
    double min, max;
    mMinRange = cv::Mat::zeros(1, D, CV_32F);
    mMaxRange = cv::Mat::zeros(1, D, CV_32F);
    for (int d = 0; d < D; ++d) {
      cv::minMaxIdx(mPopulation.col(d), &min, &max);
      mMinRange.at<float>(d) = static_cast<float>(min);
      mMaxRange.at<float>(d) = static_cast<float>(max);
    }
  }

  mVelocities = cv::Mat::zeros(mPopulationLength, mPopulation.cols, CV_32F);
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < mPopulationLength; ++i) {
    cv::RNG lRng(static_cast<uint64>(time(nullptr)));

    cv::Scalar stddev(2);
    cv::Scalar mean(0);
    cv::randn(mVelocities.row(i), mean, stddev);
  }

  mDimensions = mPopulation.cols;
  mPopulationLength = mPopulation.rows;

  mLocalBests = mPopulation.clone();
  mLocalUtils.resize(mPopulationLength);
  mUtilities = cv::Mat_<float>::zeros(mPopulationLength, 1);
  mBestPosition = mPopulation.row(0).clone();

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < mPopulationLength; ++i) {
    cv::Mat row = mPopulation.row(i);
    float util = (*utility)(row);
    mLocalUtils[i] = util;
    mUtilities.at<float>(i) = util;
#ifdef _OPENMP
#pragma omp critical
#endif
    if (util > mBestUtil) {
      mBestUtil = util;
      for (int d = 0; d < mBestPosition.cols; ++d) {
        mBestPosition.at<float>(d) = row.at<float>(d);
      }
    }
  }
}

void PSO::learn(const cv::Mat_<float>& input) {
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
  #ifdef _OPENMP
  #pragma omp parallel for
  #endif
  for (int r = 0; r < mPopulationLength; ++r) {
    cv::Mat position = mPopulation.row(r),
      localBest = mLocalBests.row(r),
      vel = mVelocities.row(r);
    update(mBestPosition, localBest, mInertia, vel, position);

    float currentUtil = (*utility)(position);
    mLocalUtils[r] = currentUtil;
    #ifdef _OPENMP
    #pragma omp critical
    #endif
    {
      if (currentUtil >= mBestUtil) {
        for (int d = 0; d < position.cols; ++d) {
          mBestPosition.at<float>(d) = position.at<float>(d);
        }
        mBestUtil = currentUtil;
      }
      if (currentUtil >= mUtilities.at<float>(r)) {
        for (int d = 0; d < position.cols; ++d) {
          mLocalBests.at<float>(r, d) = position.at<float>(d);
        }
        mUtilities.at<float>(r) = currentUtil;
      }
    }
  }
}

cv::Vec3f PSO::getInertia() const {
  return mInertia;
}

void PSO::setInertia(const cv::Vec3f& inertia) {
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

void PSO::getPopulationConstraint(
  cv::Mat_<float>& min,
  cv::Mat_<float>& max) const {
  min.copyTo(mMinRange);
  max.copyTo(mMaxRange);
}

void PSO::setPopulationConstraint(
  const cv::Mat_<float>& minRange,
  const cv::Mat_<float>& maxRange) {
  mMinRange = minRange.clone();
  mMaxRange = maxRange.clone();
}

cv::Mat PSO::getBestPosition() const {
  return mBestPosition;
}

float PSO::getBestUtil() const {
  return mBestUtil;
}

PSO::PSO(const PSO& rhs) {
  setDimensionality(rhs.mDimensions);
  setInertia(rhs.getInertia());
  getPopulationConstraint(mMinRange, mMaxRange);
  setPopulationLength(getPopulationLength());
  setEps(getEps());
  setMaxIterations(getMaxIterations());
}

PSO::PSO(
  cv::Ptr<UtilityFunctor>& utility,
  cv::Ptr<DistanceFunctor>& distance) :
  Optimization(utility, distance) {}

void PSO::update(const cv::Mat& globalBest,
  const cv::Mat& localBest,
  const cv::Vec3f& inertia,
  cv::Mat& velocity,
  cv::Mat& position) {
  static std::uniform_real_distribution<float> dist(0.0f, 1000.0f);

  float R1 = (dist(gen)) / 1000.f;
  float R2 = (dist(gen)) / 1000.f;
  // v = w_1*v + w_2*R1(LB - X)+ w_3*R2(GB - X) :
  cv::Mat term1 = velocity * inertia[0];
  cv::Mat term2 = (localBest - position) * inertia[1] * R1;
  cv::Mat term3 = (globalBest - position) * (inertia[2] * R2);

  velocity = term1 + term2 + term3;

  // X = X + v :
  position = position + velocity;
}

}  // namespace ssig
