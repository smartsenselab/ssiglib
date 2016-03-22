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

#include "core/sampling.hpp"

#include <stdexcept>
#include <vector>

#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>

namespace ssig {

Sampling::Sampling() {
  // Constructor
}

Sampling::~Sampling() {
  // Destructor
}

Sampling::Sampling(const Sampling& rhs) {
  // Constructor Copy
}

Sampling& Sampling::operator=(const Sampling& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

std::vector<cv::Rect> Sampling::sampleImage(const cv::Mat& img,
                                            const int maxPatches,
                                            const cv::Size& winSize) {
  // cv::RNG rng(12345);
  std::vector<cv::Rect> ans;
  std::vector<cv::Point2f> corners;
  auto h = winSize.height;
  auto w = winSize.width;
  auto H = img.rows;
  auto W = img.cols;
  double minDistance = cv::sqrt(h * h + w * w) / 1.5;
  cv::Mat bwImg;
  if (img.channels() > 1) {
    cv::cvtColor(img, bwImg, CV_BGR2GRAY);
  } else {
    bwImg = img;
  }

  cv::goodFeaturesToTrack(bwImg, corners, maxPatches, 0.01, minDistance);

  for (int r = 0; r < static_cast<int>(corners.size()); ++r) {
    auto corner = corners[r];
    int x = static_cast<int>(corner.x) - h / 2;
    int y = static_cast<int>(corner.y) - w / 2;

    // Try to adjust the keypoint position so there is a valid window
    if (x + w > W) {
      int offset = cv::abs(W - (x + w));
      x = x - offset;
    } else if (x < 0) {
      int offset = cv::abs(x);
      x = x + offset;
    }
    if (y + h > H) {
      int offset = cv::abs(H - (y + h));
      x = x - offset;
    } else if (y < 0) {
      int offset = cv::abs(y);
      y = y + offset;
    }

    if (x + w < W && x >= 0) {
      if (y + h < H && y >= 0) {
        cv::Rect rect{x, y, w, h};
        ans.push_back(rect);
      }
    }
  }
  // Visualization Intended for Debugging:
  // cv::Mat copy;
  // cv::cvtColor(img, copy, cv::COLOR_GRAY2BGR);
  // int r = 4;
  // for (int i = 0; i < corners.size(); i++) {
  //  circle(copy, corners[i], r, cv::Scalar(rng.uniform(0, 255), rng.uniform(0,
  //  255),
  //    rng.uniform(0, 255)), -1, 8, 0);
  //}

  return ans;
}

/**
  @param strideX a value in range (0,1]
  @param strideY a value in range (0,1]
*/
std::vector<cv::Rect> Sampling::sampleImage(const int width, const int height,
                                            const int winWidth,
                                            const int winHeight,
                                            const float strideX,
                                            const float strideY) {
  if (width <= 0) throw std::invalid_argument("Width must be greater than 0");
  if (height <= 0) throw std::invalid_argument("height must be greater than 0");
  if ((strideX <= 0 && strideX > 1.0f) || (strideY <= 0 && strideY > 1.0f))
    throw std::invalid_argument("stride must be in range (0,1]");

  std::vector<cv::Rect> rects;

  int h = static_cast<int>(winHeight), w = static_cast<int>(winWidth);
  for (int y = 0; y + h < height; y += static_cast<int>(strideY * h)) {
    for (int x = 0; x + w < width; x += static_cast<int>(strideX * w)) {
      cv::Rect rect(x, y, w, h);
      rects.push_back(rect);
    }
  }
  if (rects.size() <= 0)
    throw std::runtime_error("No Rect produced for the set scales");
  return rects;
}

std::vector<cv::Rect> Sampling::sampleImage(
  const int width, const int height, const int winWidth, const int winHeight,
  const float minScale, const float maxScale, const int nScales,
  const float strideX, const float strideY) {
  if (width <= 0) throw std::invalid_argument("Width must be greater than 0");
  if (height <= 0) throw std::invalid_argument("height must be greater than 0");
  if (minScale > maxScale)
    throw std::invalid_argument("minScale must be greater than maxScale");
  if ((strideX <= 0 && strideX > 1.0f) || (strideY <= 0 && strideY > 1.0f))
    throw std::invalid_argument("stride must be in range (0,1]");

  float deltaScale =
    pow((maxScale / minScale), 1 / static_cast<float>(nScales));
  // int samples = ((height / winHeight)*(width / winWidth)) / (80 *
  // 80)*nScales;
  std::vector<cv::Rect> rects;
  float scale = minScale;
  do {
    int h = static_cast<int>(winHeight * scale),
      w = static_cast<int>(winWidth * scale);
    for (int y = 0; y <= height - h; y += static_cast<int>(strideY * h)) {
      for (int x = 0; x <= width - w; x += static_cast<int>(strideX * w)) {
        cv::Rect rect(x, y, w, h);
        rects.push_back(rect);
      }
    }
    scale *= deltaScale;
  } while (scale < maxScale);
  if (rects.size() <= 0)
    throw std::runtime_error("No Rect produced for the set scales");
  return rects;
}

std::vector<cv::Rect> Sampling::sampleImage(
  const int width, const int height, const int winWidth, const int winHeight,
  const float minScale, const float maxScale, const float deltaScale,
  const float strideX, const float strideY) {
  if (width <= 0) throw std::invalid_argument("Width must be greater than 0");
  if (height <= 0) throw std::invalid_argument("height must be greater than 0");
  if (deltaScale <= 1) {
    throw std::invalid_argument(
      "delta Scale must be greater than 1 or it will enter infinite loop");
  }
  if (minScale > maxScale)
    throw std::invalid_argument("minScale must be greater than maxScale");

  std::vector<cv::Rect> rects;
  for (float scale = minScale; scale < maxScale; scale *= deltaScale) {
    int h = static_cast<int>(winHeight * scale),
      w = static_cast<int>(winWidth * scale);
    for (int y = 0; y < height - h; y += static_cast<int>(strideY * h)) {
      for (int x = 0; x < width - w; x += static_cast<int>(strideX * w)) {
        cv::Rect rect(x, y, w, h);
        rects.push_back(rect);
      }
    }
  }
  if (rects.size() <= 0)
    throw std::runtime_error("No Rect produced for the scales set");
  return rects;
}

}  // namespace ssig


