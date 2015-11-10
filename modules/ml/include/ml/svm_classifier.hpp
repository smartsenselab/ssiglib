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


#ifndef _SSIG_ML_SVMCLASSIFIER_HPP_
#define _SSIG_ML_SVMCLASSIFIER_HPP_

#include <opencv2/ml/ml.hpp>

#include <unordered_map>
#include <string>

#include "classification.hpp"

namespace ssig {

class SVMClassifier : public Classification {
  ML_EXPORT virtual void setup(cv::Mat_<float>& input);
  ML_EXPORT virtual void addLabels(cv::Mat_<int>& labels);

 public:
  ML_EXPORT SVMClassifier(void);
  ML_EXPORT virtual ~SVMClassifier(void);

  ML_EXPORT void learn(cv::Mat_<float>& input, cv::Mat_<int>& labels) override;

  ML_EXPORT void predict(cv::Mat_<float>& inp,
                         cv::Mat_<float>& resp) const override;

  ML_EXPORT cv::Mat_<int> getLabels() const override;
  ML_EXPORT std::unordered_map<int, int> getLabelsOrdering() const override;

  ML_EXPORT void setClassWeights(const int classLabel,
                                 const float weight) override;

  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;
  ML_EXPORT void load(const std::string& filename,
                      const std::string& nodename) override;
  ML_EXPORT void save(const std::string& filename,
                      const std::string& nodename) const override;

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT Classification* clone() const override;

  ML_EXPORT int getKernelType() const;

  ML_EXPORT void setKernelType(int kernelType);

  ML_EXPORT int getModelType() const;

  ML_EXPORT void setModelType(int modelType);

  ML_EXPORT float getC() const;

  ML_EXPORT void setC(float c);

  ML_EXPORT float getGamma() const;

  ML_EXPORT void setGamma(float gamma);

  ML_EXPORT float getP() const;

  ML_EXPORT void setP(float p);

  ML_EXPORT float getNu() const;

  ML_EXPORT void setNu(float nu);

  ML_EXPORT float getCoef() const;

  ML_EXPORT void setCoef(float coef);

  ML_EXPORT float getDegree() const;

  ML_EXPORT void setDegree(float degree);

 private:
  // private members
  cv::Ptr<cv::ml::SVM> mSvm;

  int mKernelType = cv::ml::SVM::LINEAR;
  int mModelType = cv::ml::SVM::C_SVC;
  float mC = 0.1f;
  float mGamma = 0.1f;
  float mP = 0.1f;
  float mNu = 0.1f;
  float mCoef = 0.1f;
  float mDegree = 0.1f;

  cv::Mat mClassWeights;

  std::unordered_map<int, float> mWeights;
};

}  // namespace ssig

#endif  // !_SSIG_ML_SVMCLASSIFIER_HPP_
