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

#include "Algorithms/plsClassifier.hpp"

namespace ssf{

PLSClassifier::PLSClassifier(){
  //Constructor
}

PLSClassifier::~PLSClassifier(){
  //Destructor
}

PLSClassifier::PLSClassifier(const PLSClassifier& rhs){
  //Constructor Copy
}

PLSClassifier& PLSClassifier::operator=(const PLSClassifier& rhs){
  if(this != &rhs){
    //code here
  }
  return *this;
}

void PLSClassifier::predict(cv::Mat_<float>& inp,
                            cv::Mat_<float>& resp) const{
  pls_->ProjectionBstar(inp, resp);
}

void PLSClassifier::addLabels(cv::Mat_<int>& labels){
  labels_ = labels;
}

void PLSClassifier::learn(cv::Mat_<float>& input,
                          cv::Mat_<int>& labels,
                          ClassificationParams* parameters){
  if(!labels.empty())addLabels(labels);
  pls_ = std::make_unique<PLS>();
  cv::Mat_<float> l;
  nfactors_ = static_cast<PLSParameters*>(parameters)->factors;
  labels_.convertTo(l, CV_32F);
  auto X = input.clone();
  pls_->runpls(X, l, nfactors_);

  trained_ = true;
}

cv::Mat_<int> PLSClassifier::getLabels() const{
  return labels_;
}

bool PLSClassifier::empty() const{
  return bool(pls_);
}

bool PLSClassifier::isTrained() const{
  return trained_;
}

bool PLSClassifier::isClassifier() const{
  return true;
}

void PLSClassifier::setClassWeights(const int classLabel, const float weight){ }


void PLSClassifier::load(const std::string& filename, const std::string& nodename){}

void PLSClassifier::save(const std::string& filename, const std::string& nodename) const{}


}
