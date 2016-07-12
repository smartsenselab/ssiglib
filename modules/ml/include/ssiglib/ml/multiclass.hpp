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

#ifndef _SSIG_ML_MULTICLASS_HPP_
#define _SSIG_ML_MULTICLASS_HPP_

// ssiglib
#include "ssiglib/core/algorithm.hpp"
#include "ssiglib/ml/ml_defs.hpp"
#include "ssiglib/ml/classification.hpp"


namespace ssig {
class Multiclass : public Classifier {
 public:
  virtual ~Multiclass() = default;

  int predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const override = 0;
  void learn(const cv::Mat_<float>& input, const cv::Mat& labels) override = 0;
  cv::Mat getLabels() const override = 0;
  std::unordered_map<int, int> getLabelsOrdering() const override = 0;
  bool empty() const override = 0;
  bool isTrained() const override = 0;
  bool isClassifier() const override;
  void read(const cv::FileNode& fn) override = 0;
  void write(cv::FileStorage& fs) const override = 0;
  Classifier* clone() const override = 0;


 protected:
  Multiclass() = default;
 private:
  // private members
};
}  // namespace ssig
#endif  // !_SSIG_ML_MULTICLASS_HPP_
