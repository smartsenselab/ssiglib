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

#include "iterableMethod.hpp"
#include "core/util.hpp"

namespace ssf{

struct FireflyParameters{
  float epsilon_;
  int maxIterations_;
  float absorption_;
  float step_;
  float annealling_;
};

template<class UtilityFunction, class DistanceFunction>
class Firefly : public IterableMethod{
  cv::Mat_<float> randomVector();
public:
  Firefly() = default;

  void setup(cv::Mat_<float>& input, const FireflyParameters& parameters);

  bool iterate() override;

  cv::Mat_<float> learn
  (cv::Mat_<float>& input, const FireflyParameters& parameters);

  cv::Mat_<float> getResults();

  cv::Mat_<float> getState();

private:

  cv::Mat_<float> population_;
  cv::Mat_<float> utilities_;
  float absorption_ = 0.01f;
  int iterations_ = 0;
  int maxIterations_ = 10;
  float annealling_ = 0.97f;
  float step_ = 0.01f;
  cv::RNG rng_;
public:
  float getAbsorption() const{
    return absorption_;
  }

  void setAbsorption(float absorption){
    absorption_ = absorption;
  }

  int getMaxIterations() const{
    return maxIterations_;
  }

  void setMaxIterations(int maxIterations){
    maxIterations_ = maxIterations;
  }

  float getAnnealling() const{
    return annealling_;
  }

  void setAnnealling(float annealling){
    annealling_ = annealling;
  }

  float getStep() const{
    return step_;
  }

  void setStep(float step){
    step_ = step;
  }

};

template<class UtilityFunction, class DistanceFunction>
cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::
randomVector(){
  const int d = population_.cols;
  cv::Mat_<float> vec(1, d);
  cv::randu(vec, cv::Scalar::all(-0.5), cv::Scalar::all(0.5));
  return vec;
}

template<class UtilityFunction, class DistanceFunction>
void Firefly<UtilityFunction, DistanceFunction>::
setup(cv::Mat_<float>& input,
      const FireflyParameters& parameters){
  UtilityFunction evaluateUtility;
  step_ = parameters.step_;
  absorption_ = parameters.absorption_;
  // parameters.epsilon_;
  maxIterations_ = parameters.maxIterations_;

  iterations_ = 0;
  population_ = input;
  utilities_ = cv::Mat::zeros(population_.rows, 1, CV_32F);

  for(int i = 0; i < population_.rows; ++i){
    utilities_[0][i] = evaluateUtility(population_.row(i));
  }

  rng_ = cv::theRNG();

  cv::Mat_<int> order;
  cv::sortIdx(utilities_, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  cv::Mat_<float> npop;
  cv::Mat_<float> nuti;
  ssf::Util::reorder(population_, order, npop);
  ssf::Util::reorder(utilities_, order, nuti);
  population_ = npop;
  utilities_ = nuti;
}

template<class UtilityFunction, class DistanceFunction>
bool Firefly<UtilityFunction, DistanceFunction>::iterate(){
  DistanceFunction evaluateDistance;
  for(int i = 0; i < population_.rows; ++i){
    for(int j = 0; j < population_.rows; ++j){
      if(utilities_[0][j] > utilities_[0][i]){
        auto xj = population_.row(j);
        auto xi = population_.row(i);
        auto dist = evaluateDistance(xi, xj);
        auto attractiveness = utilities_[0][j] / cv::exp(absorption_ * dist * dist);
        population_.row(i) = xi * (1 - attractiveness) +
          attractiveness * (xj) + step_ * randomVector();
      }
    }
  }
  UtilityFunction evaluateUtility;

  for(int i = 0; i < population_.rows; ++i){
    utilities_[0][i] = evaluateUtility(population_.row(i));
  }

  step_ = step_ * annealling_;

  cv::Mat_<int> order;
  cv::sortIdx(utilities_, order, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  cv::Mat_<float> npop;
  cv::Mat_<float> nuti;
  ssf::Util::reorder(population_, order, npop);
  ssf::Util::reorder(utilities_, order, nuti);
  population_ = npop;
  utilities_ = nuti;

  if(++iterations_ > maxIterations_) return true;
  return false;
}

template<class UtilityFunction, class DistanceFunction>
cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::learn
(cv::Mat_<float>& input, const FireflyParameters& parameters){
  setup(input, parameters);
  while(!iterate()){ }


  return getResults();
}

template<class UtilityFunction, class DistanceFunction>
cv::Mat_<float>
Firefly<UtilityFunction, DistanceFunction>::getResults(){
  return utilities_;
}

template<class UtilityFunction, class DistanceFunction>
cv::Mat_<float> Firefly<UtilityFunction, DistanceFunction>::getState(){
  return population_;
}

}

#endif // !_SSF_ALGORITHMS_FIREFLY_METHOD_HPP_

