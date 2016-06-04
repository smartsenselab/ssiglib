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

#ifdef _OPENMP
#include <omp.h>
#endif

#include <string>

#include <opencv2/core.hpp>
#include <ssiglib/core/util.hpp>
#include <ssiglib/core/firefly.hpp>

ssig::Firefly::Firefly(cv::Ptr<UtilityFunctor>& utilityFunction,
  cv::Ptr<DistanceFunctor>& distanceFunction) :
  : utility(utilityFunction),
    distance(distanceFunction) {}

ssig::Firefly::Firefly(const Firefly& rhs) {
  setAbsorption(rhs.getAbsorption());
  setAnnealling(rhs.getAnnealling());
  setStep(rhs.getStep());
  setEps(rhs.getEps());
  setMaxIterations(rhs.getMaxIterations());
}

cv::Ptr<ssig::Firefly> ssig::Firefly::create(
  cv::Ptr<UtilityFunctor>& utilityFunction,
  cv::Ptr<DistanceFunctor>& distanceFunction) {
  struct _Firefly : Firefly {
    _Firefly(cv::Ptr<UtilityFunctor> utilityFunction,
      cv::Ptr<DistanceFunctor> distanceFunction) :
      Firefly(utilityFunction,
              distanceFunction) {}
  };

  return cv::makePtr<_Firefly>(utilityFunction, distanceFunction);
}

void ssig::Firefly::setup(cv::Mat_<float>& input) {
  mIterations = 0;
  mPopulation = input;
  mUtilities = cv::Mat::zeros(mPopulation.rows, 1, CV_32F);

#ifdef _OPENMP
  #pragma omp parallel for
#endif
  for (int i = 0; i < mPopulation.rows; ++i) {
    mUtilities[0][i] = (*utility)(mPopulation.row(i));
  }

  mRng = cv::theRNG();

  cv::Mat_<int> order;
  cv::sortIdx(mUtilities, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  cv::Mat_<float> npop;
  cv::Mat_<float> nuti;
  ssig::Util::reorder(mPopulation, order, npop);
  ssig::Util::reorder(mUtilities, order, nuti);
  mPopulation = npop;
  mUtilities = nuti;
}


bool ssig::Firefly::iterate() {
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < mPopulation.rows; ++i) {
    for (int j = 0; j < mPopulation.rows; ++j) {
      if (mUtilities[0][j] > mUtilities[0][i]) {
        auto xj = mPopulation.row(j);
        auto xi = mPopulation.row(i);
        auto dist = (*distance)(xi, xj);
        auto expX = (mAbsorption * dist * dist);
        auto attractiveness = mUtilities[0][j] / (1 + expX + expX * expX / 2);
        mPopulation.row(i) = xi * (1 - attractiveness) +
            attractiveness * (xj) + mStep * randomVector(mPopulation.cols);
      }
    }
  }

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < mPopulation.rows; ++i) {
    mUtilities[0][i] = (*utility)(mPopulation.row(i));
  }

  mStep = mStep * mAnnealling;

  cv::Mat_<int> order;
  cv::sortIdx(mUtilities, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  cv::Mat_<float> npop;
  cv::Mat_<float> nuti;
  ssig::Util::reorder(mPopulation, order, npop);
  ssig::Util::reorder(mUtilities, order, nuti);
  mPopulation = npop;
  mUtilities = nuti;

  if (++mIterations > mMaxIterations)
    return true;
  if (mStep < 0.001f)
    return true;
  return false;
}


void ssig::Firefly::learn(cv::Mat_<float>& input) {
  setup(input);
  while (!iterate()) { }
}

void ssig::Firefly::save(const std::string& filename,
                         const std::string& nodename) const {
  std::runtime_error("Unimplemented Method");
}


void ssig::Firefly::load(const std::string& filename,
                         const std::string& nodename) {
  std::runtime_error("Unimplemented Method");
}

void ssig::Firefly::read(const cv::FileNode& fn) {
  std::runtime_error("Unimplemented Method");
}

void ssig::Firefly::write(cv::FileStorage& fs) const {
  std::runtime_error("Unimplemented Method");
}

float ssig::Firefly::getAbsorption() const {
  return mAbsorption;
}

void ssig::Firefly::setAbsorption(float absorption) {
  mAbsorption = absorption;
}

float ssig::Firefly::getAnnealling() const {
  return mAnnealling;
}

void ssig::Firefly::setAnnealling(float annealling) {
  mAnnealling = annealling;
}

float ssig::Firefly::getStep() const {
  return mStep;
}

void ssig::Firefly::setStep(float step) {
  mStep = step;
}
