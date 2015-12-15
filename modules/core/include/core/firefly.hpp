/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#ifndef _SSF_ALGORITHMS_FIREFLY_METHOD_HPP_
#define _SSF_ALGORITHMS_FIREFLY_METHOD_HPP_
#include <opencv2/core.hpp>

#include <core/math.hpp>
#include <core/algorithm.hpp>
#include "core_defs.hpp"

namespace ssig {
class Firefly : public Algorithm {
  cv::Mat_<float> randomVector() const;
 public:
  CORE_EXPORT Firefly(UtilityFunctor& utilityFunction,
                      DistanceFunctor& distanceFunction);
  CORE_EXPORT Firefly(DistanceFunctor& distanceFunction,
                      UtilityFunctor& utilityFunction);

  CORE_EXPORT void setup(cv::Mat_<float>& input);

  CORE_EXPORT bool iterate();

  CORE_EXPORT cv::Mat_<float> learn
  (cv::Mat_<float>& input);

  CORE_EXPORT cv::Mat_<float> getResults() const;

  CORE_EXPORT cv::Mat_<float> getState() const;

  CORE_EXPORT virtual void save(const std::string& filename,
                                const std::string& nodename) const override;
  CORE_EXPORT virtual void load(const std::string& filename,
                                const std::string& nodename) override;

  CORE_EXPORT float getAbsorption() const;

  CORE_EXPORT void setAbsorption(float absorption);

  CORE_EXPORT int getMaxIterations() const;

  CORE_EXPORT void setMaxIterations(int maxIterations);

  CORE_EXPORT float getAnnealling() const;

  CORE_EXPORT void setAnnealling(float annealling);

  CORE_EXPORT float getStep() const;

  CORE_EXPORT void setStep(float step);

 protected:
  CORE_EXPORT void read(const cv::FileNode& fn) override;
  CORE_EXPORT void write(cv::FileStorage& fs) const override;

 private:
  UtilityFunctor& utility;
  DistanceFunctor& distance;
  cv::Mat_<float> mPopulation;
  cv::Mat_<float> mUtilities;
  float mAbsorption = 0.01f;
  int mIterations = 0;
  int mMaxIterations = 10;
  float mAnnealling = 0.97f;
  float mStep = 0.01f;
  cv::RNG mRng;
};
}  // namespace ssig
#endif  // !_SSF_ALGORITHMS_FIREFLY_METHOD_HPP_


