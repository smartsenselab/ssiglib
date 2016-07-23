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

// opencv
#include <opencv2/core.hpp>
// ssiglib
#include "ssiglib/ml/pls_embedding.hpp"

namespace ssig {

cv::Ptr<PLSEmbedding> PLSEmbedding::create(
  const int dimensions,
  cv::InputArray labels) {
  auto ans = cv::Ptr<PLSEmbedding>(new PLSEmbedding());
  ans->setDimensions(dimensions);
  ans->setLabels(labels);

  return ans;
}

PLSEmbedding::PLSEmbedding(const PLSEmbedding& rhs) {
  // Constructor Copy
  mDimensions = rhs.getDimensions();
  mLabels = rhs.getLabels().clone();
}

PLSEmbedding& PLSEmbedding::operator=(const PLSEmbedding& rhs) {
  if (this != &rhs) {
    this->mDimensions = rhs.getDimensions();
    this->mLabels = rhs.getLabels().clone();
  }
  return *this;
}

void PLSEmbedding::learn(
  cv::InputArray input) {
#ifdef _WIN32
  mPLS = std::make_unique<ssig::PLS>();
#else
  mPLS = std::unique_ptr<ssig::PLS>(new ssig::PLS());
#endif
  cv::Mat_<float> X = input.getMat();
  cv::Mat_<float> Xcopy = X.clone();
  mPLS->learn(Xcopy, mLabels, mDimensions);
  mWstarmat = mPLS->getWstar();
}

void PLSEmbedding::project(
  cv::InputArray sample,
  cv::OutputArray output) {
  cv::Mat_<float> X, proj;
  X = sample.getMat();
  output.create(X.rows, mDimensions, CV_32F);
  proj = output.getMat();
  cv::Mat_<float> Xcopy = X.clone();
  mPLS->predict(Xcopy, proj, mDimensions);
}

int PLSEmbedding::getDimensions() const {
  return mDimensions;
}

void PLSEmbedding::setDimensions(const int dimensions) {
  mDimensions = dimensions;
}

cv::Mat_<float> PLSEmbedding::getLabels() const {
  return mLabels;
}

void PLSEmbedding::setLabels(cv::InputArray labels) {
  cv::Mat localLabels = labels.getMat();
  localLabels.convertTo(mLabels, CV_32F);
}

cv::Mat_<float> PLSEmbedding::getWstarmat() const {
  return mWstarmat;
}

void PLSEmbedding::read(const cv::FileNode& fn) {}

void PLSEmbedding::write(cv::FileStorage& fs) const {}
}  // namespace ssig
