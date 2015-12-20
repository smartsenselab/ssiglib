/*L****************************************************************************
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
****************************************************************************L*/

#include "descriptors/bic_features.hpp"

#include <opencv2/imgproc.hpp>
#include <vector>

namespace ssig {


BIC::BIC(const cv::Mat& input) : Descriptor2D(input) {}

BIC::BIC(const cv::Mat& input,
         const BIC& descriptor) :
  Descriptor2D(input,
             descriptor) {}

BIC::BIC(const BIC& rhs) : Descriptor2D(rhs) {
  // Constructor Copy
}

void BIC::read(const cv::FileNode& fn) {
  throw std::runtime_error("unimplemented");
}

void BIC::write(cv::FileStorage& fs) const {
  throw std::runtime_error("unimplemented");
}

void BIC::beforeProcess() {
  std::vector<cv::Mat> channels;
  cv::Mat imageInt;
  mImage.convertTo(imageInt, CV_32SC3);
  cv::split(imageInt, channels);

  const int rows = mImage.rows, cols = mImage.cols;
  cv::Mat_<int> temp(rows, cols, 0);
  // BGR to RGB
  temp = channels[2] + 256 * channels[1] + 65536 * channels[0];
  const int MAX_VALUE = 1 << 24;
  const int bucketLen = MAX_VALUE / 63;
  temp = temp / bucketLen;
  temp.convertTo(mImage, CV_8U);

  cv::Mat_<int> filter = (cv::Mat_<int>(3, 3) << 0 , 1 , 0 ,
    1 , 1 , 1 ,
    0 , 1 , 0);
  cv::filter2D(mImage, mInteriorMask, CV_32F, filter);
  mInteriorMask = mInteriorMask / 5;
  mInteriorMask.convertTo(mInteriorMask, CV_8UC1);
  cv::compare(mImage, mInteriorMask, mInteriorMask, CV_CMP_EQ);
}

void BIC::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
  cv::Mat roi = mImage(patch);
  cv::Mat roiMask = mInteriorMask(patch);

  int channels[] = {0};
  int histSize[] = {64};
  float range[] = {0, 64};
  const float* ranges[] = {range};

  cv::Mat border, interior;

  cv::calcHist(&roi, 1, channels,
               roiMask, interior, 1, histSize, ranges);
  cv::calcHist(&roi, 1, channels,
               255 - roiMask, border, 1, histSize, ranges);

  cv::transpose(border, border);
  cv::normalize(border, border, 1, 0, cv::NORM_L1);

  cv::transpose(interior, interior);
  cv::normalize(interior, interior, 1, 0, cv::NORM_L1);

  cv::hconcat(border, interior, output);
}
}  // namespace ssig


