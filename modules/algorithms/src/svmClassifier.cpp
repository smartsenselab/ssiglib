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
#include <cassert>
#include <algorithms/svmClassifier.hpp>
#include <opencv2/ml.hpp>

namespace ssf{

SVMClassifier::SVMClassifier(){
  //Constructor
}

SVMClassifier::~SVMClassifier(){
  //Destructor
}

std::unordered_map<int, int> SVMClassifier::getLabelsOrdering() const{
  //TODO:Create Test for this
  return{{1, 0},{-1, 1}};
}

void SVMClassifier::setup(cv::Mat_<float>& input, ClassificationParams* parameters){
  samples_ = input;
  cv::TermCriteria termCrit(parameters->termType, parameters->maxIt, parameters->eps);
  auto p = reinterpret_cast<SVMParameters*>(parameters);

  kernelType_ = p->kernelType;
  modelType_ = p->modelType;

  c_ = p->c;
  gamma_ = p->gamma;
  nu_ = p->nu;
  coef_ = p->coef;
  degree_ = p->degree;

  if(!weights_.empty()){
    classWeights_ = cv::Mat::ones(static_cast<int>(weights_.size()), 1, CV_32F);
    for(auto& it : weights_){
      classWeights_.at<float>(it.first) = it.second;
    }
    weights_.clear();
  }

  svm_ = cv::ml::SVM::create();
  svm_->setC(c_);
  svm_->setType(modelType_);
  svm_->setKernel(kernelType_);
  svm_->setDegree(degree_);
  svm_->setClassWeights(classWeights_);
  svm_->setTermCriteria(termCrit);
  svm_->setGamma(gamma_);
  svm_->setCoef0(coef_);
  svm_->setNu(nu_);
  svm_->setP(p_);
}

void SVMClassifier::addLabels(cv::Mat_<int>& labels){
  labels_ = labels;
}

void SVMClassifier::learn(cv::Mat_<float>& input,
                          cv::Mat_<int>& labels,
                          ClassificationParams* parameters){
  setup(input, parameters);
  assert(!labels.empty());
  addLabels(labels);

  svm_->train(samples_, cv::ml::ROW_SAMPLE, labels_);
}

void SVMClassifier::predict(cv::Mat_<float>& inp,
                            cv::Mat_<float>& resp) const{
  cv::Mat_<float> label;
  svm_->predict(inp, resp, cv::ml::StatModel::RAW_OUTPUT);
  svm_->predict(inp, label);
  cv::Mat_<float> ans;
  ans.create(resp.rows, 2);
  for(int r = 0; r < resp.rows; ++r){
    if(label[r][0] * resp[r][0] < 0){
      ans[r][0] = -1 * resp[r][0];
      ans[r][1] = resp[r][0];
    } else{
      ans[r][0] = resp[r][0];
      ans[r][1] = -1 * resp[r][0];
    }
  }
  resp = ans;
}

cv::Mat_<int> SVMClassifier::getLabels() const{
  return labels_;
}

void SVMClassifier::setClassWeights(const int classLabel, const float weight){
  weights_[classLabel] = weight;
}

bool SVMClassifier::empty() const{
  return svm_.empty();
}

bool SVMClassifier::isTrained() const{
  return svm_->isTrained();
}

bool SVMClassifier::isClassifier() const{
  return svm_->isClassifier();
}


void SVMClassifier::load(const std::string& filename, const std::string& nodename){ }

void SVMClassifier::save(const std::string& filename, const std::string& nodename) const{ }
}
