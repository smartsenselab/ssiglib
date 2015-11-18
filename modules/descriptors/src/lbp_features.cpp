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


#include "descriptors/lbp_features.hpp"

namespace ssig {

LBP::LBP(const cv::Mat& img): Descriptor(img) {}

LBP::LBP(const cv::Mat& img, const LBP& descriptor) :
  Descriptor(img, descriptor) {}

LBP::LBP(const LBP& rhs): Descriptor(rhs) {}

void LBP::read(const cv::FileNode& fn) {}

void LBP::write(cv::FileStorage& fs) const {}

void LBP::beforeProcess() {
  const int width = mImage.cols, height = mImage.rows;
  mBinaryPattern.create(height, width);
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      uchar value = 0;
      const int kernelLen = mKernel.rows;
      for (int ki = 0; ki < kernelLen; ++ki) {
        for (int kj = 0; kj < kernelLen; ++kj) {
          const int offset = kernelLen / 2;
          if (!inValidRange(ki - offset, kj - offset)) continue;
          if (mImage.at<uchar>(ki - offset, kj - offset) >=
            mImage.at<uchar>(i, j)) {
            value = (1 << mKernel[ki][kj]) | value;
          }
        }
      }
      mBinaryPattern[i][j] = value;
    }
  }
}

void LBP::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
  output.create(1, 256, CV_32F);
  output = 0;
  cv::Mat_<float> feat = output;

  // TODO(Ricardo): can be parallel
  for (int i = patch.y; i < patch.width; ++i) {
    for (int j = patch.x; j < patch.height; ++j) {
      feat[0][mBinaryPattern[i][j]] += 1;
    }
  }
}

bool LBP::inValidRange(const int i, const int j) const {
  bool ans = true;
  if (i < 0 || j < 0)
    ans = false;
  if (i > mImage.rows || j > mImage.cols)
    ans = false;

  return ans;
}

void LBP::setDefaultKernel() {
  mKernel = (cv::Mat_<int>(3, 3) << 0 , 1 , 2 , 3 , -1 , 4 , 5 , 6 , 7);
}
}  // namespace ssig


