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

#include "descriptors/temporal_descriptor.hpp"

#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace ssig {

TemporalDescriptors::TemporalDescriptors(const std::vector<cv::Mat>& data)
  : Descriptor() {
  mData.resize(data.size());
  for (int i = 0; i < static_cast<int>(mData.size()); ++i)
    mData[i] = data[i].clone();
}

TemporalDescriptors::TemporalDescriptors(const std::vector<cv::Mat>& data,
  const Descriptor& descriptor) {
  mData.resize(data.size());
  for (int i = 0; i < static_cast<int>(mData.size()); ++i)
    mData[i] = data[i].clone();
}

TemporalDescriptors::TemporalDescriptors(const TemporalDescriptors& descriptor) {
  mData.resize(descriptor.mData.size());
  for (int i = 0; i < static_cast<int>(mData.size()); ++i)
    mData[i] = descriptor.mData[i].clone();
}

TemporalDescriptors& TemporalDescriptors::operator=(const TemporalDescriptors& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void TemporalDescriptors::readVideo(const std::string& videoname,
  std::vector<cv::Mat>& frames,
  const bool convert2BW) {
  cv::VideoCapture capture;

  capture.open(videoname);
  if (!capture.isOpened()) {
    std::cout << "Error opening video!" << std::endl;
    exit(1);
  }

  int totalFrames = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_COUNT));
  capture.set(cv::CAP_PROP_CONVERT_RGB, 1);

  frames.resize(totalFrames);
  cv::Mat frame;
  for (int i = 0; i < totalFrames; ++i) {
    int errorCode = capture.read(frame);
    if(convert2BW) {
      cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
    }
    frame.copyTo(frames[i]);
  }
}

void TemporalDescriptors::extract(cv::Mat& out) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }
  auto window = cv::Rect(0, 0, mWidth, mHeight);
  cv::Point2i depth(0, mData.size());
  extractFeatures(window, depth, out);
}

void TemporalDescriptors::extract(const std::vector<cv::Rect>& windows,
  cv::Mat& output) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }
  for (int i = 0; i < static_cast<int>(windows.size()); ++i) {
    auto window = cv::Rect(0, 0, mWidth, mHeight);
    cv::Point2i depth(0, mData.size());
    cv::Mat out;
    extractFeatures(window, depth, out);
    output.push_back(out);
  }
}

void TemporalDescriptors::extract(const std::vector<cv::Point2i>& depths,
  cv::Mat& output) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }
  for (int i = 0; i < static_cast<int>(depths.size()); ++i) {
    auto window = cv::Rect(0, 0, mWidth, mHeight);
    auto& depth = depths[i];
    cv::Mat out;
    extractFeatures(window, depth, out);
    output.push_back(out);
  }
}

void TemporalDescriptors::extract(
  const std::vector<cv::Rect>& windows,
  const std::vector<cv::Point2i>& depths,
  cv::Mat& output) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }
  for (int i = 0; i < static_cast<int>(windows.size()); ++i) {
    auto& window = windows[i];
    auto& depth = depths[i];
    cv::Mat out;
    extractFeatures(window, depth, out);
    output.push_back(out);
  }
}

void TemporalDescriptors::setData(const std::vector<cv::Mat>& data) {
  mData = data;
  mWidth = mData[0].cols;
  mHeight = mData[0].rows;
}

int TemporalDescriptors::getNFrames() const {
  return mData.size();
}

std::vector<cv::Mat> TemporalDescriptors::getData() const {
  return mData;
}
} // namespace ssig


