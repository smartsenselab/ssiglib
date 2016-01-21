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

#include "ml/spatial_pyramid.hpp"

#include <vector>

namespace ssig {
SpatialPyramid::SpatialPyramid() {
  // Constructor
}

SpatialPyramid::~SpatialPyramid() {
  // Destructor
}

SpatialPyramid::SpatialPyramid(const SpatialPyramid& rhs) {
  // Constructor Copy
}

SpatialPyramid& SpatialPyramid::operator=(const SpatialPyramid& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void SpatialPyramid::pool(
  const cv::Size& imageSize,
  const std::vector<ssig::Clustering*>& clusteringMethods,
  const std::vector<cv::Vec2i>& pyramidConfigurations,
  const std::vector<float>& poolingWeights,
  const std::vector<cv::Mat_<float>>& partFeatures,
  const std::vector<cv::Rect>& partWindows,
  const std::vector<int>& scaledHeights,
  cv::Mat_<float>& output) {
  if (partFeatures.size() != partWindows.size()) {
    std::runtime_error("The number of windows and features must be the same!");
  }

  const int modelSize = static_cast<int>(clusteringMethods[0]->getSize());
  const int nbins =
    modelSize * static_cast<int>(clusteringMethods.size());


  std::vector<cv::Mat_<float>> configurationHistograms(
    pyramidConfigurations.size());

  for (int conf_it = 0; conf_it < pyramidConfigurations.size(); ++conf_it) {
    auto currConf = pyramidConfigurations[conf_it];
    const int configurationArea = currConf[0] * currConf[1];
    cv::Mat_<float> configurationHistogram(1, nbins * configurationArea);
    configurationHistogram = 0;

    for (int part_it = 0; part_it < partFeatures.size(); ++part_it) {
      auto partFeature = partFeatures[part_it];
      auto scaledHeight = static_cast<float>(scaledHeights[part_it]);
      float scale = scaledHeight / imageSize.height;

      const int horizontalBucketSize = static_cast<int>(imageSize.width * scale)
        / currConf[0];
      const int verticalBucketSize = static_cast<int>(imageSize.height * scale)
        / currConf[1];

      const int pyramidRow = partWindows[part_it].x / horizontalBucketSize;
      const int pyramidCol = partWindows[part_it].y / verticalBucketSize;
      cv::Mat_<float> response = cv::Mat_<float>::zeros(1, nbins);
      for (int model_it = 0; model_it < clusteringMethods.size(); ++model_it) {
        auto clusteringMethod = clusteringMethods[model_it];
        cv::Mat_<float> partResponse;
        clusteringMethod->predict(partFeature, partResponse);

        const int x = model_it * modelSize;
        const int width = modelSize;
        cv::Mat_<float> roi = response(cv::Rect(x, 0, width, 1));
        partResponse.copyTo(roi);
      }
      cv::Mat_<int> ordering;
      cv::sortIdx(response, ordering, cv::SORT_DESCENDING);
      for (int weight_it = 0; weight_it < poolingWeights.size(); ++weight_it) {
        int idx = ordering.at<int>(weight_it);
        idx = idx + pyramidRow * 2 + pyramidCol;
        configurationHistogram.at<float>(idx) += poolingWeights[weight_it];
      }
    }
    configurationHistograms[conf_it] = configurationHistogram;
  }

  for (const auto& hist : configurationHistograms) {
    if (output.empty())
      output = hist;
    else
      cv::hconcat(output.clone(), hist, output);
  }
  // TODO(Ricardo): implement a test for this method
}

void SpatialPyramid::read(const cv::FileNode& fn) {
  std::runtime_error("Unimplemented");
}

void SpatialPyramid::write(cv::FileStorage& fs) const {
  std::runtime_error("Unimplemented");
}
}  // namespace ssig


