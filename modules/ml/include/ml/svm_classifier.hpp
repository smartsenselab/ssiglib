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

#include <opencv2/core.hpp>

#include <libsvm.hpp>

#include <unordered_map>
#include <string>

#include "classification.hpp"

namespace ssig {
class SVMClassifier : public Classifier {
  svm_problem* convertToLibSVM(
    const cv::Mat_<int>& labels,
    const cv::Mat_<float>& features) const;
  svm_node** convertToLibSVM(
    const cv::Mat_<float>& features) const;

 public:
  enum ModelType {
    C_SVC,
    NU_SVC,
    ONE_CLASS,
    EPSILON_SVR,
    NU_SVR
  };

  enum KernelType {
    LINEAR,
    POLY,
    RBF,
    SIGMOID,
    PRECOMPUTED
  };

  ML_EXPORT SVMClassifier(void);
  ML_EXPORT virtual ~SVMClassifier(void);

  ML_EXPORT void learn(
    const cv::Mat_<float>& input,
    const cv::Mat_<int>& labels) override;

  ML_EXPORT int predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const override;

  ML_EXPORT cv::Mat_<int> getLabels() const override;
  ML_EXPORT std::unordered_map<int, int> getLabelsOrdering() const override;

  ML_EXPORT void setClassWeights(const int classLabel,
    const float weight) override;

  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT Classifier* clone() const override;

  ML_EXPORT float getEpsilon() const override;

  ML_EXPORT void setEpsilon(float epsilon) override;

  ML_EXPORT int getKernelType() const;

  ML_EXPORT void setKernelType(KernelType kernelType);

  ML_EXPORT int getModelType() const;

  ML_EXPORT void setModelType(ModelType modelType);

  ML_EXPORT double getC() const;

  ML_EXPORT void setC(double c);

  ML_EXPORT double getGamma() const;

  ML_EXPORT void setGamma(double gamma);

  ML_EXPORT double getP() const;

  ML_EXPORT void setP(double p);

  ML_EXPORT double getNu() const;

  ML_EXPORT void setNu(double nu);

  ML_EXPORT double getCoef() const;

  ML_EXPORT void setCoef(double coef);

  ML_EXPORT int getDegree() const;

  ML_EXPORT void setDegree(int degree);

  // Only use probabilistical predict with data big enough
  ML_EXPORT void setProbabilisticModel(bool b);
  ML_EXPORT bool getProbabilisticModel() const;

  //ML_EXPORT size_t getCrossValidationState() const;

  //ML_EXPORT void setCrossValidationState(int kfolds);

 private:
  // private members
  svm_model* mModel = nullptr;

  svm_parameter mParams;

};

} // namespace ssig

#endif // !_SSIG_ML_SVMCLASSIFIER_HPP_


