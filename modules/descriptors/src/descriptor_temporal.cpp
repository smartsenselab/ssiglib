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

#include "ssiglib/descriptors/descriptor_temporal.hpp"

namespace ssig {
DescriptorTemporal::DescriptorTemporal() {
  // Constructor
}

DescriptorTemporal::DescriptorTemporal(const DescriptorTemporal& rhs) {
  // Constructor Copy
  for (auto &img : rhs.mImages)
    mImages.push_back(img);
}


void DescriptorTemporal::extract(cv::Mat& output) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }
  extractFeatures(ssig::Cube(0, 0, 0, mImages[0].cols, mImages[0].rows, static_cast<int>(mImages.size())), output);
}

void DescriptorTemporal::extract(const std::vector<ssig::Cube>& cuboids, cv::Mat& output) {
  if (!mIsPrepared) {
    beforeProcess();
    mIsPrepared = true;
  }

  output.create(static_cast<int>(cuboids.size()), getDescriptorLength(), getDescriptorDataType());

  int i = 0;
  for (auto& cuboid : cuboids) {
    cv::Mat feat;

    auto cuboidRoi = ssig::Cube(0, 0, 0, mImages[0].cols, mImages[0].rows, static_cast<int>(mImages.size()));
    auto intersection = cuboidRoi & cuboid;

    if (intersection != cuboid) {
      std::runtime_error(
        "Invalid cuboid, its intersection with the images are" +
        std::string("different than the cuboid itself"));
    }
    extractFeatures(cuboid, feat);
    if (feat.cols > 0)
      feat.row(0).copyTo(output.row(i++));
    //output.push_back(feat);
  }
  output.resize(i);
}

/*
void DescriptorTemporal::extract(const std::vector<cv::KeyPoint>& keypoints, cv::Mat& output) {
  //TODO
}
*/
void DescriptorTemporal::setData(const std::vector<cv::Mat>& imgs) {

  for (auto &img : imgs)
    mImages.push_back(img.clone());

  beforeProcess();
  mIsPrepared = true;
}

}  // namespace ssig
