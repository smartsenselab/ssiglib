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


#ifndef _SSIG_ML_OAACLASSIFIER_HPP_
#define _SSIG_ML_OAACLASSIFIER_HPP_

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "classification.hpp"
#include "multiclass.hpp"

namespace ssig {

class OAAClassifier : public Multiclass {
  ML_EXPORT virtual void addLabels(const cv::Mat_<int>& labels);

 public:
  ML_EXPORT static cv::Ptr<OAAClassifier> create(const Classifier& underlying);
  virtual ~OAAClassifier(void) = default;

  using Classifier::predict;
  ML_EXPORT int predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp,
    cv::Mat_<int>& labels) const override;

  ML_EXPORT void learn(
    const cv::Mat_<float>& input,
    const cv::Mat& labels) override;

  ML_EXPORT cv::Mat getLabels() const override;
  ML_EXPORT std::unordered_map<int, int> getLabelsOrdering() const override;

  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;

  ML_EXPORT void load(const std::string& filename,
                      const std::string& nodename) override;
  ML_EXPORT void save(const std::string& filename,
                      const std::string& nodename) const override;

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT Classifier* clone() const override;

  ML_EXPORT std::shared_ptr<Classifier> getUnderlyingClassifier() const;
  ML_EXPORT void setUnderlyingClassifier(
    const Classifier& underlyingClassifier);

 protected:
  ML_EXPORT OAAClassifier(const Classifier& prototypeClassifier);
  OAAClassifier() = default;

 private:
  // private members
  std::unordered_map<int, int> mLabel2Index;
  std::vector<int> mIndex2Label;

  std::vector<std::unique_ptr<Classifier>> mClassifiers;
  std::unique_ptr<Classifier> mUnderlyingClassifier;
  cv::Mat_<int> mLabels;

  bool mTrained = false;
};

}  // namespace ssig

#endif  // !_SSIG_ML_OAACLASSIFIER_HPP_


