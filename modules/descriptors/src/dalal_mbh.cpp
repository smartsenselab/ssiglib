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

#include "ssiglib/descriptors/dalal_mbh.hpp"

#include <vector>
#include <algorithm>

#include <ssiglib/descriptors/hog_uoccti_features.hpp>
#include <opencv2/video.hpp>
#include <ssiglib/core/util.hpp>

namespace ssig {

DalalMBH::DalalMBH(const std::vector<cv::Mat>& data) :
  TemporalDescriptors(data) {
  of = cv::createOptFlow_DualTVL1();
}

DalalMBH::DalalMBH(const DalalMBH& rhs) : TemporalDescriptors(rhs) {
  // Constructor Copy
}

void DalalMBH::setFrameCombination(const FrameCombination comb) {
  mFrameComb = comb;
}

FrameCombination DalalMBH::getFrameCombination() const {
  return mFrameComb;
}

void DalalMBH::setOpticalFlowMethod(
  const cv::Ptr<cv::DenseOpticalFlow>& method) {
  of = method;
}


void DalalMBH::read(const cv::FileNode& fn) {}

void DalalMBH::write(cv::FileStorage& fs) const {}

void DalalMBH::beforeProcess() {
  auto data = getData();
  mFlows.resize(static_cast<int>(data.size()) - 1);

#pragma omp parallel for
  for (int i = 0; i < static_cast<int>(data.size()) - 1; ++i) {
    cv::Mat& frame0 = data[i];
    cv::Mat& framef = data[i + 1];
    cv::Mat flow;
    if (!(frame0.empty() && framef.empty()))
      of->calc(frame0, framef, flow);
    mFlows[i] = flow;
  }
}

void DalalMBH::extractFeatures(const cv::Rect& patch,
  const cv::Point2i depth,
  cv::Mat& output) {
  int len = static_cast<int>(getNFrames());
  assert(depth.x >= 0 &&
    depth.y < len &&
    depth.y > depth.x);
  auto data = getData();
  len = depth.y - depth.x;
  std::vector<cv::Mat> flowFeatsX(len),
      flowFeatsY(len);

#pragma omp parallel for
  for (int i = depth.x; i < depth.y; ++i) {
    cv::Mat roi;
    roi = mFlows[i](patch);
    extractStatistics(roi, flowFeatsX[i], flowFeatsY[i]);
  }
  frameCombination(flowFeatsX, flowFeatsY, output);
  output = output.reshape(0, 1);
}

void DalalMBH::extractStatistics(const cv::Mat& roi,
  cv::Mat& outX,
  cv::Mat& outY) const {
  std::vector<cv::Mat> flows;
  std::vector<cv::Mat> outs(2);
  cv::split(roi, flows);
  for (int j = 0; j < 2; ++j) {
    cv::Mat flowImg = ssig::Util::convertToImg(flows[j]);
    ssig::HOGUOCCTI hog(flowImg);
    hog.setNumberOfBins(9);
    hog.setBlockConfiguration(cv::Size(32, 32));
    hog.setBlockStride(cv::Size(16, 16));
    hog.setCellConfiguration(cv::Size(2, 2));
    hog.extract(outs[j]);
  }
  outX = outs[0];
  outY = outs[1];
}

void DalalMBH::frameCombination(const std::vector<cv::Mat>& flowX,
  const std::vector<cv::Mat>& flowY,
  cv::Mat& out) const {
  switch (getFrameCombination()) {
  case MAX_POOL: {
    cv::Mat x, y;
    for (int i = 0; i < static_cast<int>(flowX.size()); ++i) {
      if (x.empty())
        x = flowX[i];
      else
        x = cv::max(x, flowX[i]);
    }
    for (int i = 0; i < static_cast<int>(flowY.size()); ++i) {
      if (y.empty())
        y = flowY[i];
      else
        y = cv::max(y, flowY[i]);
    }
    cv::hconcat(x, y, out);
  }
    break;
  case CONCATENATION: {
    cv::Mat x, y;
    for (int i = 0; i < static_cast<int>(flowX.size()); ++i) {
      x.push_back(flowX[i]);
    }
    for (int i = 0; i < static_cast<int>(flowY.size()); ++i) {
      y.push_back(flowY[i]);
    }
    out.push_back(x);
    out.push_back(y);
    out.reshape(1, 1);
  }
    break;
  case SUM: {
    cv::Mat x, y;
    for (int i = 0; i < static_cast<int>(flowX.size()); ++i) {
      if (x.empty())
        x = flowX[i];
      else
        x += flowX[i];
    }
    for (int i = 0; i < static_cast<int>(flowY.size()); ++i) {
      if (y.empty())
        y = flowY[i];
      else
        y = y + flowY[i];
    }
    cv::hconcat(x, y, out);
  }
    break;
  case AVERAGE: {
    cv::Mat x, y;
    for (int i = 0; i < static_cast<int>(flowX.size()); ++i) {
      if (x.empty())
        x = flowX[i];
      else
        x += flowX[i];
    }
    x = x / static_cast<int>(flowX.size());
    for (int i = 0; i < static_cast<int>(flowY.size()); ++i) {
      if (y.empty())
        y = flowY[i];
      else
        y = y + flowY[i];
    }
    y = y / static_cast<int>(flowY.size());
    cv::hconcat(x, y, out);
  }
    break;
  default: {}
    break;
  }
}

}  // namespace ssig


