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

#include "ssiglib/ml/hard_mining_classifier.hpp"

namespace ssig {

HardMiningClassifier::HardMiningClassifier(Classifier& c) {
  mClassifier = std::unique_ptr<Classifier>(c.clone());
}

cv::Ptr<HardMiningClassifier> HardMiningClassifier::create(Classifier& c) {
  return cv::Ptr<HardMiningClassifier>(new HardMiningClassifier(c));
}

HardMiningClassifier::HardMiningClassifier(const HardMiningClassifier& rhs) {
  // Constructor Copy
}

HardMiningClassifier& HardMiningClassifier::operator=(
  const HardMiningClassifier& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

int HardMiningClassifier::predict(
  const cv::Mat_<float>& inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) const {
  return mClassifier->predict(inp, resp, labels);
}

void HardMiningClassifier::learn(
  const cv::Mat_<float>& input,
  const cv::Mat& labels) {
  cv::Mat_<float> inp = input.clone();
  mLabels = labels.clone();

  mClassifier->learn(inp, mLabels);
  cv::Mat_<float> resp;

  for (int it = 0; it < mMaxIterations; ++it) {
    auto labelOrdering = mClassifier->getLabelsOrdering();
    mClassifier->predict(mSamples, resp);
    for (int r = 0; r < resp.rows; ++r) {
      auto col = labelOrdering[1];
      if (resp[r][col] > 0) {
        inp.push_back(mSamples.row(r));
        mLabels.push_back(-1);
      }
    }
    mClassifier->learn(inp, mLabels);
  }
}

cv::Mat HardMiningClassifier::getLabels() const {
  return mLabels;
}

void HardMiningClassifier::setNegatives(const cv::Mat_<float>& negatives) {
  mSamples = negatives.clone();
}

std::unordered_map<int, int> HardMiningClassifier::getLabelsOrdering() const {
  return mClassifier->getLabelsOrdering();
}

bool HardMiningClassifier::empty() const {
  return mClassifier->empty();
}

bool HardMiningClassifier::isTrained() const {
  return !mClassifier->empty();
}

bool HardMiningClassifier::isClassifier() const {
  return true;
}

void HardMiningClassifier::read(const cv::FileNode& fn) {
  if (!mClassifier)
    std::runtime_error("The classifier must be set before calling this method");

  mClassifier->read(fn);
}

void HardMiningClassifier::write(cv::FileStorage& fs) const {
  mClassifier->write(fs);
}

Classifier* HardMiningClassifier::clone() const {
  auto ans = new HardMiningClassifier(*mClassifier);
  ans->setNegatives(mSamples);

  return ans;
}

}  // namespace ssig


