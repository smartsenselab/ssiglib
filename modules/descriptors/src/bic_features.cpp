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

namespace ssig {


BIC::BIC(const cv::Mat& input) : Descriptor(input) {}

BIC::BIC(const cv::Mat& input,
         const BIC& descriptor) :
  Descriptor(input,
             descriptor) {}

BIC::BIC(const BIC& rhs) : Descriptor(rhs) {
  // Constructor Copy
}

void BIC::read(const cv::FileNode& fn) {
  throw std::runtime_error("unimplemented");
}

void BIC::write(cv::FileStorage& fs) const {
  throw std::runtime_error("unimplemented");
}

void BIC::beforeProcess() {
  int lowThreshold = 50;
  int ratio = 4;
  // convert to grayscale
  cv::cvtColor(mImage, mEdgeMask, CV_BGR2GRAY);
  // binaryze image
  cv::threshold(mEdgeMask, mEdgeMask, 128, 255, CV_THRESH_BINARY);
  // find edges
  cv::Canny(mEdgeMask, mEdgeMask, lowThreshold, ratio * lowThreshold, 5);

  // convert image to HSV color space
  cv::cvtColor(mImage, mImage, CV_BGR2HSV);
}

void BIC::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
  cv::Mat roi = mImage(patch);
  cv::Mat roiMask = mEdgeMask(patch);
  cv::calcHist(roi, {0}, roiMask, output, {1}, {0, 180});
}
} // namespace ssig


