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

#ifndef _SSIG_CORE_PSO_HPP_
#define _SSIG_CORE_PSO_HPP_

// c++
#include <cfloat>
#include <memory>
#include <utility>
#include <vector>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include <ssiglib/core/algorithm.hpp>
#include "core_defs.hpp"
#include "optimization.hpp"

namespace ssig {
class DistanceFunctor;
class UtilityFunctor;

class PSO : public Optimization {
 public:
  CORE_EXPORT virtual ~PSO(void) = default;

  CORE_EXPORT static cv::Ptr<PSO> create(
    cv::Ptr<UtilityFunctor>& utilityFunction,
    cv::Ptr<DistanceFunctor>& distanceFunction);


  CORE_EXPORT void learn(const cv::Mat_<float>& input) override;


  CORE_EXPORT cv::Vec3f getInertia() const;
  // a 1x3 matrix of floating point numbers
  CORE_EXPORT void setInertia(const cv::Vec3f& inertia);


  CORE_EXPORT int getPopulationLength() const;
  CORE_EXPORT void setPopulationLength(const int populationLength);

  CORE_EXPORT void setDimensionality(int d);


  CORE_EXPORT void getPopulationConstraint(
    cv::Mat_<float>& min,
    cv::Mat_<float>& max) const;
  CORE_EXPORT void setPopulationConstraint(
    const cv::Mat_<float>& minRange,
    const cv::Mat_<float>& maxRange);


  CORE_EXPORT cv::Mat getBestPosition() const;

  CORE_EXPORT float getBestUtil() const;

 protected:
  CORE_EXPORT PSO(
    cv::Ptr<UtilityFunctor>& utility,
    cv::Ptr<DistanceFunctor>& distance);
  CORE_EXPORT PSO(const PSO& rhs);

  CORE_EXPORT void setup(const cv::Mat_<float>& input) override;


  CORE_EXPORT void iterate();
  CORE_EXPORT static void update(const cv::Mat& globalBest,
    const cv::Mat& localBest,
    const cv::Vec3f& inertia,
    cv::Mat& velocity,
    cv::Mat& position);

 private:
  // private members
  cv::Mat mBestPosition;
  cv::Mat mLocalBests;
  cv::Mat mVelocities;
  cv::Vec3f mInertia;
  cv::Mat_<float> mMinRange;
  cv::Mat_<float> mMaxRange;

  int mPopulationLength = 100;
  int mDimensions = 1;

  float mBestUtil = -FLT_MAX;
  std::vector<float> mLocalUtils;
};
}  // namespace ssig
#endif  // !_SSIG_CORE_PSO_HPP_

