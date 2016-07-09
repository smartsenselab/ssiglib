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


#ifndef _SSIG_ML_PLSCLASSIFIER_HPP_
#define _SSIG_ML_PLSCLASSIFIER_HPP_
// c++
#include <memory>
// ssiglib
#include "pls.hpp"
#include "classification.hpp"
#include "multiclass.hpp"

namespace ssig {

class PLSClassifier : public Multiclass {
  virtual void addLabels(const cv::Mat_<int>& labels);

 public:
 ML_EXPORT static cv::Ptr<PLSClassifier> create();
  ML_EXPORT virtual ~PLSClassifier(void);
  ML_EXPORT PLSClassifier(const PLSClassifier& rhs);

  ML_EXPORT int predict(
    const cv::Mat_<float>& inp,
              cv::Mat_<float>& resp) const override;
  ML_EXPORT void learn(
    const cv::Mat_<float>& input,
    const cv::Mat_<int>& labels) override;
  ML_EXPORT cv::Mat_<int> getLabels() const override;
  ML_EXPORT std::unordered_map<int, int> getLabelsOrdering() const override;
  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT Classifier* clone() const override;

  ML_EXPORT int getNumberOfFactors() const;

  ML_EXPORT void setNumberOfFactors(int numberOfFactors);

 protected:
  ML_EXPORT PLSClassifier(void);
 private:
  // private members
  std::unique_ptr<PLS> mPls;
  int mNumberOfFactors = 3;

  bool mTrained = false;

  void setClassWeights(const int classLabel, const float weight) override;
};

}  // namespace ssig

#endif  // !_SSIG_ML_PLSCLASSIFIER_HPP_


