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


#ifndef _SSIG_ML_CLASSIFICATION_HPP_
#define _SSIG_ML_CLASSIFICATION_HPP_
// opencv
#include <opencv2/core.hpp>
// c++
#include <unordered_map>
#include <string>
// ssiglib
#include "ssiglib/ml/ml_defs.hpp"
#include "ssiglib/core/algorithm.hpp"

namespace ssig {

class Classifier : public Algorithm {
 public:
  ML_EXPORT virtual int predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const = 0;

  ML_EXPORT Classifier(void) = default;
  ML_EXPORT virtual ~Classifier(void) = default;

  ML_EXPORT virtual void learn(
    const cv::Mat_<float>& input,
    const cv::Mat& labels) = 0;

  ML_EXPORT virtual cv::Mat getLabels() const = 0;
  ML_EXPORT virtual std::unordered_map<int, int> getLabelsOrdering() const = 0;

  ML_EXPORT virtual void setClassWeights(const int classLabel,
                                         const float weight);
  ML_EXPORT virtual void setClassWeights(
    const std::unordered_map<int, float>& weights);
  ML_EXPORT virtual std::unordered_map<int, float> getClassWeights() const;

  ML_EXPORT virtual bool empty() const = 0;
  ML_EXPORT virtual bool isTrained() const = 0;
  ML_EXPORT virtual bool isClassifier() const = 0;

  ML_EXPORT void read(const cv::FileNode& fn) override = 0;
  ML_EXPORT void write(cv::FileStorage& fs) const override = 0;

  ML_EXPORT virtual Classifier* clone() const = 0;
  // TODO(Ricardo): ML_EXPORT virtual void copyConfigurationTo(Algorithm& obj)
  // const = 0;

  ML_EXPORT int getTermType() const;

  ML_EXPORT void setTermType(int termType);

  virtual
  ML_EXPORT float getEpsilon() const;

  virtual
  ML_EXPORT void setEpsilon(float epsilon);

  ML_EXPORT int getMaxIterations() const;

  ML_EXPORT void setMaxIterations(int maxIterations);

 protected:
  virtual void precondition();
  cv::Mat_<float> mSamples;
  cv::Mat_<int> mLabels;

  std::unordered_map<int, float> mWeights;

  int mTermType = cv::TermCriteria::MAX_ITER;

  float mEpsilon = 0.001f;
  int mMaxIterations = static_cast<int>(1e4);
};

inline void Classifier::setClassWeights(const int classLabel,
                                        const float weight) {
  mWeights[classLabel] = weight;
}

inline void Classifier::setClassWeights(
  const std::unordered_map<int, float>& weights) {
  mWeights = weights;
}

inline std::unordered_map<int, float> Classifier::getClassWeights() const {
  return mWeights;
}

inline int Classifier::getTermType() const {
  return mTermType;
}

inline void Classifier::setTermType(int termType) {
  mTermType = termType;
}

inline float Classifier::getEpsilon() const {
  return mEpsilon;
}

inline void Classifier::setEpsilon(float epsilon) {
  mEpsilon = epsilon;
}

inline int Classifier::getMaxIterations() const {
  return mMaxIterations;
}

inline void Classifier::setMaxIterations(int maxIterations) {
  mMaxIterations = maxIterations;
}

inline void Classifier::precondition() {
  // TODO(Ricardo): precondition
}

}  // namespace ssig

#endif  // !_SSIG_ML_CLASSIFICATION_HPP_


