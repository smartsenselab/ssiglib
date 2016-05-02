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

#include "descriptors/dalal_mbh.hpp"

#include <descriptors/hog_uoccti_features.hpp>
#include <opencv2/video.hpp>

//#include <opencv2/video/tracking.hpp>

namespace ssig {

DalalMBH::DalalMBH(const std::vector<cv::Mat>& data) :
  TemporalDescriptors(data) { }

DalalMBH::DalalMBH(const DalalMBH& rhs) : TemporalDescriptors(rhs) {
  // Constructor Copy
}

void DalalMBH::read(const cv::FileNode& fn) {}

void DalalMBH::write(cv::FileStorage& fs) const {}

void DalalMBH::beforeProcess() {
  auto data = getData();
  mFlows.resize(static_cast<int>(data.size()) - 1);
  double pyrscale = 0.5,
      poly_sigma = 1.1;
  int levels = 4,
      winsize = 5,
      iterations = 20,
      poly_n = 5;
  for (int i = 0; i < static_cast<int>(data.size()) - 1; ++i) {
    cv::Mat& frame0 = data[i];
    cv::Mat& framef = data[i + 1];

    cv::calcOpticalFlowFarneback(frame0, framef,
                                 mFlows[i],
                                 pyrscale,
                                 levels,
                                 winsize,
                                 iterations,
                                 poly_n,
                                 poly_sigma,
                                 cv::OPTFLOW_FARNEBACK_GAUSSIAN);
  }

}

void DalalMBH::extractFeatures(const cv::Rect& patch,
  const cv::Point2i depth,
  cv::Mat& output) {
  cv::Mat roi;
  assert(depth.x >= 0 &&
    depth.y < static_cast<int>(getNFrames()) &&
    depth.y > depth.x);
  auto data = getData();
  std::vector<cv::Mat> flowFeats(depth.y - depth.x);
  for (int i = depth.x; i < depth.y; ++i) {
    roi = data[i](patch);
    extractStatistics(roi, flowFeats[i]);
  }
}

void DalalMBH::extractStatistics(const cv::Mat& roi,
  cv::Mat& out) const {
  
}

//DalalMBH& DalalMBH::operator=(const DalalMBH& rhs) {
//  if (this != &rhs) {
//    // code here
//  }
//  return *this;
//}
} // namespace ssig


