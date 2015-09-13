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

#ifndef _SSF_ALGORITHMS_SVMCLASSIFIER_HPP_
#define _SSF_ALGORITHMS_SVMCLASSIFIER_HPP_
#include "classification.hpp"
#include <opencv2/ml/ml.hpp>
#include <unordered_map>

namespace ssf{

struct SVMParameters : ClassificationParams{
  int kernelType = cv::ml::SVM::LINEAR;
  int modelType = cv::ml::SVM::C_SVC;
  float c = 0.1f;
  float gamma = 0.1f;
  float p = 0.1f;
  float nu = 0.1f;
  float coef = 0.1f;
  float degree = 0.1f;
};

class SVMClassifier : public Classification{
  virtual void setup(cv::Mat_<float>& input, ClassificationParams* parameters);
  virtual void addLabels(cv::Mat_<int>& labels);
public:
  ALG_EXPORT SVMClassifier(void);
  ALG_EXPORT virtual ~SVMClassifier(void);

  ALG_EXPORT virtual void learn(cv::Mat_<float>& input,
                                cv::Mat_<int>& labels,
                                ClassificationParams* parameters) override;

  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp,
                                  cv::Mat_<float>& resp) const override;

  ALG_EXPORT virtual cv::Mat_<int> getLabels() const override;
  ALG_EXPORT virtual std::unordered_map<int, int> getLabelsOrdering() const override;

  ALG_EXPORT virtual void setClassWeights(const int classLabel, const float weight) override;


  ALG_EXPORT virtual bool empty() const override;
  ALG_EXPORT virtual bool isTrained() const override;
  ALG_EXPORT virtual bool isClassifier() const override;
  ALG_EXPORT virtual void load(const std::string& filename, const std::string& nodename) override;
  ALG_EXPORT virtual void save(const std::string& filename, const std::string& nodename) const override;
private:
  //private members
  cv::Ptr<cv::ml::SVM> svm_;
  int kernelType_;
  int modelType_;
  float c_;
  float gamma_;
  float p_;
  float nu_;
  float coef_;
  float degree_;
  cv::Mat classWeights_;

  std::unordered_map<int, float> weights_;

};

}

#endif // !_SSF_ALGORITHMS_SVMCLASSIFIER_HPP_

