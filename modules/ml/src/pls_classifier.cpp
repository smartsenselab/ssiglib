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

#include <ssiglib/ml/pls_classifier.hpp>

#include <cassert>
#include <string>
#include <unordered_set>
#include <ssiglib/core/util.hpp>

namespace ssig {

PLSClassifier::PLSClassifier() {
  // Constructor
}

PLSClassifier::~PLSClassifier() {
  // Destructor
}

PLSClassifier::PLSClassifier(const PLSClassifier& rhs) {
  // Constructor Copy
}

int PLSClassifier::predict(
  const cv::Mat_<float>& inp,
  cv::Mat_<float>& resp,
  cv::Mat_<int>& labels) const {
  if (mOpenClEnabled) {
    mClPls->predict(inp, resp);
  } else {
    mPls->predict(inp, resp);
  }
  cv::Mat_<float> r;
  r.create(inp.rows, mYColumns);
  labels = cv::Mat_<int>::zeros(inp.rows, 1);

  int labelIdx = -1;
  if (!mIsMulticlass) {
    for (int row = 0; row < inp.rows; ++row) {
      r[row][0] = resp[row][0];
      r[row][1] = -1 * resp[row][0];
      if (r[row][0] > 0) {
        labels.at<int>(row) = 1;
      }
    }
    labelIdx = resp[0][0] > 0 ? 1 : -1;

    resp = r;
  } else {
    for (int row = 0; row < resp.rows; ++row) {
      int maxIdx[2];
      cv::minMaxIdx(resp.row(row), nullptr, nullptr, nullptr, maxIdx);
      labelIdx = maxIdx[1];
      auto it = mIdx2Labels.find(labelIdx);
      if (it != mIdx2Labels.end()) {
        labelIdx = it->second;
      } else {
        labelIdx = -1;
      }
      labels.at<int>(row) = labelIdx;
    }
  }

  return inp.rows > 1 || mIsMulticlass ? 0 : labelIdx;
}

void PLSClassifier::addLabels(const cv::Mat& labels) {
  std::unordered_map<int, int> labelOrdering;
  int labelIdx = -1;
  int nLabels = 0;
  int minLabel = INT_MAX, maxLabel = INT_MIN;
  for (int i = 0; i < labels.rows; ++i) {
    int label = labels.at<int>(i);
    if (labelOrdering.find(label) == labelOrdering.end()) {
      labelOrdering[label] = ++labelIdx;
      mIdx2Labels[labelIdx] = label;
      ++nLabels;
      if (label <= minLabel) {
        minLabel = label;
      }
      if (label >= maxLabel) {
        maxLabel = label;
      }
    }
  }

  if (nLabels == 2 && minLabel == -1 || maxLabel == 1) {
    mLabels = labels;

    mLabels2Idx[1] = 0;
    mLabels2Idx[-1] = 1;
    mIdx2Labels[0] = 1;
    mIdx2Labels[1] = -1;
  } else {
    // multiclass
    mLabels2Idx = labelOrdering;
    mLabels = cv::Mat_<int>::zeros(labels.rows, nLabels);
    mLabels = -1;
    for (int i = 0; i < labels.rows; ++i) {
      int label = labels.at<int>(i);
      mLabels.at<int>(i, mLabels2Idx[label]) = 1;
      mIsMulticlass = true;
    }
  }
}

cv::Ptr<PLSClassifier> PLSClassifier::create() {
  return cv::Ptr<PLSClassifier>(new PLSClassifier());
}

void PLSClassifier::learn(
  const cv::Mat_<float>& input,
  const cv::Mat& labels) {
  mIsMulticlass = false;
  mLabels.release();
  mSamples.release();

  addLabels(labels);
  assert(!mLabels.empty());

  cv::Mat_<float> l;
  mLabels.convertTo(l, CV_32F);
  auto X = input.clone();
  if (mOpenClEnabled) {
    mClPls = std::unique_ptr<OpenClPLS>(new OpenClPLS());
    mClPls->learn(X, l, mNumberOfFactors);
  } else {
    mPls = std::unique_ptr<PLS>(new PLS());
    mPls->learn(X, l, mNumberOfFactors);
  }

  X.release();
  l.release();
  mTrained = true;
}

cv::Mat PLSClassifier::getLabels() const {
  return mLabels;
}

std::unordered_map<int, int> PLSClassifier::getLabelsOrdering() const {
  return mLabels2Idx;
}

bool PLSClassifier::empty() const {
  return static_cast<bool>(mPls);
}

bool PLSClassifier::isTrained() const {
  return mTrained;
}

bool PLSClassifier::isClassifier() const {
  return true;
}

void PLSClassifier::setClassWeights(const int classLabel, const float weight) {}

void PLSClassifier::read(const cv::FileNode& fn) {
  mPls = std::unique_ptr<PLS>(new PLS());

  auto labelOrderingNode = fn["Labels2Idx"];
  ssig::Util::read<int, int>(mLabels2Idx, labelOrderingNode);
  labelOrderingNode = fn["Idx2Labels"];
  ssig::Util::read<int, int>(mIdx2Labels, labelOrderingNode);

  mPls->load(fn);
}

void PLSClassifier::write(cv::FileStorage& fs) const {
  if (mOpenClEnabled) {
    mClPls->save(fs);
  } else {
    mPls->save(fs);
  }
  fs << "Labels2Idx"
      << "{";
  ssig::Util::write<int, int>(mLabels2Idx, fs);
  fs << "}";
  fs << "Idx2Labels"
      << "{";
  ssig::Util::write<int, int>(mIdx2Labels, fs);
  fs << "}";
}

Classifier* PLSClassifier::clone() const {
  auto copy = new PLSClassifier;

  copy->setNumberOfFactors(getNumberOfFactors());

  return copy;
}

int PLSClassifier::getNumberOfFactors() const {
  return mNumberOfFactors;
}

void PLSClassifier::setNumberOfFactors(int numberOfFactors) {
  mNumberOfFactors = numberOfFactors;
}


}  // namespace ssig
