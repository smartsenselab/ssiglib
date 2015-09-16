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

#ifndef _SSF_ALGORITHMS_OAACLASSIFIER_HPP_
#define _SSF_ALGORITHMS_OAACLASSIFIER_HPP_
#include "classification.hpp"
#include <unordered_map>
#include <set>

namespace ssf{


template<class UnderlyingClassifier>
class OAAClassifier : Classification{
  virtual void addLabels(cv::Mat_<int>& labels);
public:
  OAAClassifier(void) = default;
  virtual ~OAAClassifier(void) = default;

  virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp) const override;

  virtual void learn(cv::Mat_<float>& input, cv::Mat_<int>& labels, ClassificationParams* parameters) override;
  virtual cv::Mat_<int> getLabels() const override;
  virtual std::unordered_map<int, int> getLabelsOrdering() const override;
  virtual void setClassWeights(const int classLabel, const float weight) override;
  virtual bool empty() const override;
  virtual bool isTrained() const override;
  virtual bool isClassifier() const override;
  virtual void load(const std::string& filename, const std::string& nodename) override;
  virtual void save(const std::string& filename, const std::string& nodename) const override;

private:
  //private members
  std::unordered_map<int, int> labelOrderings_;
  std::vector<UnderlyingClassifier> classifiers_;
  cv::Mat_<int> labels_;

  bool trained_ = false;
};


template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::learn(cv::Mat_<float>& input,
                                                cv::Mat_<int>& labels,
                                                ClassificationParams* parameters){
  if(!classifiers_.empty()){
    classifiers_.clear();
  }
  samples_.release();
  labels_.release();
  labelOrderings_.clear();

  samples_ = input;
  addLabels(labels);
  int c = -1;
  for(int i = 0; i < labels.rows; ++i){
    auto label = labels[0][i];
    if(labelOrderings_.find(label)
      ==
      labelOrderings_.end()){
      labelOrderings_[label] = ++c;
    }
  }

  classifiers_.resize(labelOrderings_.size());
  c = -1;
  for(auto& labelIdx: labelOrderings_){
    cv::Mat_<int> localLabels = cv::Mat_<int>::zeros(samples_.rows, 1);
    for(int i = 0; i < labels.rows; ++i){
      if(labels[i][0] == labelIdx.first){
        localLabels[i][0] = 1;
      } else{
        localLabels[i][0] = -1;
      }
    }
    classifiers_[++c].learn(samples_, localLabels, parameters);
  }
  trained_ = true;
}

template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::predict(cv::Mat_<float>& inp,
                                                  cv::Mat_<float>& resp) const{
  resp = cv::Mat_<float>::zeros(inp.rows, static_cast<int>(classifiers_.size()));

  for(int r = 0; r < inp.rows; ++r){
    int c = -1;
    for(auto& classifier : classifiers_){
      cv::Mat_<float> auxResp;
      classifier.predict(inp, auxResp);
      auto ordering = classifier.getLabelsOrdering();
      const int idx = ordering[1];
      resp[r][++c] = auxResp[0][idx];
    }
  }
}

template<class UnderlyingClassifier>
cv::Mat_<int> OAAClassifier<UnderlyingClassifier>::getLabels() const{
  return labels_;
}

template<class UnderlyingClassifier>
std::unordered_map<int, int> OAAClassifier<UnderlyingClassifier>::getLabelsOrdering() const{
  return labelOrderings_;
}

template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::setClassWeights(const int classLabel,
                                                          const float weight){
  //TODO:
}

template<class UnderlyingClassifier>
bool OAAClassifier<UnderlyingClassifier>::empty() const{
  return classifiers_.empty();
}

template<class UnderlyingClassifier>
bool OAAClassifier<UnderlyingClassifier>::isTrained() const{
  return trained_;
}

template<class UnderlyingClassifier>
bool OAAClassifier<UnderlyingClassifier>::isClassifier() const{
  return true;
}

template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::load(const std::string& filename, const std::string& nodename){
  //TODO:
}

template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::save(const std::string& filename, const std::string& nodename) const{
  //TODO:
}

template<class UnderlyingClassifier>
void OAAClassifier<UnderlyingClassifier>::addLabels(cv::Mat_<int>& labels){
  labels_.release();
  labels_ = labels;
}

}

#endif // !_SSF_ALGORITHMS_OAACLASSIFIER_HPP_

