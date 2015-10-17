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

#ifndef _SSF_ALGORITHMS_CLASSIFICATION_HPP_
#define _SSF_ALGORITHMS_CLASSIFICATION_HPP_
#include <opencv2/core.hpp>
#include <unordered_map>
#include "algorithm.hpp"

namespace ssf{

class Classification : public ssf::Algorithm{
public:
  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp,
                                  cv::Mat_<float>& resp) const = 0;

  ALG_EXPORT Classification(void) = default;
  ALG_EXPORT virtual ~Classification(void) = default;

  ALG_EXPORT virtual void learn(cv::Mat_<float>& input, cv::Mat_<int>& labels) = 0;

  ALG_EXPORT virtual cv::Mat_<int> getLabels() const = 0;
  ALG_EXPORT virtual std::unordered_map<int, int> getLabelsOrdering() const = 0;

  ALG_EXPORT virtual void setClassWeights(const int classLabel, const float weight);
  ALG_EXPORT virtual void setClassWeights(const std::unordered_map<int, float>& weights);
  ALG_EXPORT virtual std::unordered_map<int, float> getClassWeights() const;

  ALG_EXPORT virtual bool empty() const = 0;
  ALG_EXPORT virtual bool isTrained() const = 0;
  ALG_EXPORT virtual bool isClassifier() const = 0;

  ALG_EXPORT virtual void load(const std::string& filename, const std::string& nodename) override = 0;
  ALG_EXPORT virtual void save(const std::string& filename, const std::string& nodename) const override = 0;
  ALG_EXPORT virtual void read(const cv::FileNode& fn) = 0;
  ALG_EXPORT virtual void write(cv::FileStorage& fs) const = 0;

  ALG_EXPORT virtual Classification* clone() const = 0;
  //TODO: ALG_EXPORT virtual void copyConfigurationTo(Algorithm& obj) const = 0;

  ALG_EXPORT int getTermType() const;

  ALG_EXPORT void setTermType(int termType);

  ALG_EXPORT float getEpsilon() const;

  ALG_EXPORT void setEpsilon(float epsilon);

  ALG_EXPORT int getMaxIterations() const;

  ALG_EXPORT void setMaxIterations(int maxIterations);

protected:
  virtual void precondition();
  cv::Mat_<float> mSamples;
  cv::Mat_<int> mLabels;

  std::unordered_map<int, float> mWeights;

  int mTermType = cv::TermCriteria::MAX_ITER;

  float mEpsilon = 0.001f;
  int mMaxIterations = static_cast<int>(1e4);

};

inline void Classification::setClassWeights(const int classLabel, const float weight){
  mWeights[classLabel] = weight;
}

inline void Classification::setClassWeights(const std::unordered_map<int, float>& weights){
  mWeights = weights;
}

inline std::unordered_map<int, float> Classification::getClassWeights() const{
  return mWeights;
}

inline int Classification::getTermType() const{
  return mTermType;
}

inline void Classification::setTermType(int termType){
  mTermType = termType;
}

inline float Classification::getEpsilon() const{
  return mEpsilon;
}

inline void Classification::setEpsilon(float epsilon){
  mEpsilon = epsilon;
}

inline int Classification::getMaxIterations() const{
  return mMaxIterations;
}

inline void Classification::setMaxIterations(int maxIterations){
  mMaxIterations = maxIterations;
}

inline void Classification::precondition(){
  //TODO: precondition
}
}

#endif // !_SSF_ALGORITHMS_CLASSIFICATION_HPP_

