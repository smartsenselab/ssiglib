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

#ifndef _SSIG_CORE_OPTIMIZATION_HPP_
#define _SSIG_CORE_OPTIMIZATION_HPP_

#include <ssiglib/core/algorithm.hpp>

#include "core_defs.hpp"


namespace ssig {
class UtilityFunctor;
class DistanceFunctor;

class Optimization : public Algorithm {
 public:
  virtual ~Optimization(void) = default;

  CORE_EXPORT virtual void setup(const cv::Mat_<float>& input) = 0;

  CORE_EXPORT virtual void learn(const cv::Mat_<float>& input) = 0;

  CORE_EXPORT cv::Mat_<float> getResults() const;

  CORE_EXPORT cv::Mat_<float> getState() const;

  // sets the initial "population" of the method
  CORE_EXPORT void setState(const cv::Mat_<float>& state);

  CORE_EXPORT int getMaxIterations() const;
  CORE_EXPORT void setMaxIterations(const int maxIterations);

  CORE_EXPORT cv::Ptr<UtilityFunctor> getUtility() const;
  CORE_EXPORT cv::Ptr<DistanceFunctor> getDistance() const;
  CORE_EXPORT void setUtilityFunctor(cv::Ptr<UtilityFunctor>& utilityFunctor);
  CORE_EXPORT void setDistanceFunctor(cv::Ptr<DistanceFunctor>& distanceFunctor);

  CORE_EXPORT double getEps() const;
  CORE_EXPORT void setEps(const double eps);

 protected:
  CORE_EXPORT Optimization() = default;

  CORE_EXPORT Optimization(
    cv::Ptr<UtilityFunctor>& utilityFunction,
    cv::Ptr<DistanceFunctor>& distanceFunction);
  CORE_EXPORT static cv::Mat_<float> randomVector(
    const int dimensionality,
    const double minRange = 0.5,
    const double maxRange = 0.5);

  CORE_EXPORT void read(const cv::FileNode& fn) override {};

  CORE_EXPORT void write(cv::FileStorage& fs) const override {};

  cv::Ptr<UtilityFunctor> utility;
  cv::Ptr<DistanceFunctor> distance;
  cv::Mat_<float> mPopulation;
  cv::Mat_<float> mUtilities;

  int mMaxIterations = 100;
  double mEps = 0.0001;

 private:
  // private members
};
}  // namespace ssig
#endif  // !_SSIG_CORE_OPTIMIZATION_HPP_


