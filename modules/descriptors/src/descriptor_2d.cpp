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

#include "descriptors/descriptor_2d.hpp"

#include <vector>
#include <stdexcept>
#include <string>

namespace ssig {

  Descriptor2D::Descriptor2D(const cv::Mat& input) {
    mImage = input.clone();
  }

  Descriptor2D::Descriptor2D(const cv::Mat& input,
    const Descriptor& descriptor) {
    mImage = input.clone();
  }

  Descriptor2D::Descriptor2D(const Descriptor2D& descriptor) {
    mImage = descriptor.mImage;
  }

  void Descriptor2D::extract(cv::Mat& output) {
    if (!mIsPrepared) {
      beforeProcess();
      mIsPrepared = true;
    }
    extractFeatures(cv::Rect(0, 0, mImage.cols, mImage.rows), output);
  }

  void Descriptor2D::extract(const std::vector<cv::Rect>& windows,
    cv::Mat& output) {
    if (!mIsPrepared) {
      beforeProcess();
      mIsPrepared = true;
    }
    for (auto& window : windows) {
      cv::Mat feat;

      auto windowRoi = cv::Rect(0, 0, mImage.cols, mImage.rows);
      auto intersection = windowRoi & window;

      if (intersection != window) {
        std::runtime_error(
          "Invalid patch, its intersection with the image is" +
          std::string("different than the patch itself"));
      }
      extractFeatures(window, feat);
      output.push_back(feat);
    }
  }

  void Descriptor2D::extract(const std::vector<cv::KeyPoint>& keypoints,
    cv::Mat& output) {
    if (!mIsPrepared) {
      beforeProcess();
      mIsPrepared = true;
    }
    const float SQROOT_TWO = 1.4142136237f;
    for (auto& keypoint : keypoints) {
      cv::Mat feat;
      // diameter = l\|2
      int length = static_cast<int>(keypoint.size * SQROOT_TWO);
      const int x = static_cast<int>(keypoint.pt.x),
          y = static_cast<int>(keypoint.pt.y),
          width = length, height = length;
      auto window = cv::Rect(x, y, width, height);
      extractFeatures(window, feat);
      output.push_back(feat);
    }
  }

  void Descriptor2D::setData(const cv::Mat& img) {
    mImage = img.clone();
    beforeProcess();
    mIsPrepared = true;
  }
}  // namespace ssig

