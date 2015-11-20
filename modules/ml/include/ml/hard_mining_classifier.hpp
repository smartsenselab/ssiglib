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

#ifndef _SSF_ML_HARD_MINING_HPP_
#define _SSF_ML_HARD_MINING_HPP_
#include "classification.hpp"

#include <memory>

#include "ml_defs.hpp"

namespace ssig {
class HardMiningClassifier : public ssig::Classifier {

 public:
  ML_EXPORT HardMiningClassifier(Classifier& c);
  ML_EXPORT virtual ~HardMiningClassifier(void) = default;
  ML_EXPORT HardMiningClassifier(const HardMiningClassifier& rhs);
  ML_EXPORT HardMiningClassifier& operator=(const HardMiningClassifier& rhs);


  ML_EXPORT void predict(cv::Mat_<float>& inp,
                         cv::Mat_<float>& resp) const override;
  ML_EXPORT void learn(cv::Mat_<float>& input,
                       cv::Mat_<int>& labels) override;
  ML_EXPORT cv::Mat_<int> getLabels() const override;
  ML_EXPORT void setNegatives(const cv::Mat_<float>& negatives);
  ML_EXPORT std::unordered_map<int, int> getLabelsOrdering() const override;
  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;
  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;
  ML_EXPORT Classifier* clone() const override;
 private:
  //private members
  std::unique_ptr<Classifier> mClassifier;
};

}  // namespace ssig

#endif  // !_SSF_ML_HARD_MINING_HPP_
