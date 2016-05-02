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

#ifndef _SSIG_ML_SPATIAL_PYRAMID_HPP_
#define _SSIG_ML_SPATIAL_PYRAMID_HPP_

#include <memory>
#include <vector>

#include <ssiglib/core/algorithm.hpp>

#include "ml_defs.hpp"
#include "clustering.hpp"


namespace ssig {
class SpatialPyramid : public ssig::Algorithm {
 public:
  SpatialPyramid(void);
  virtual ~SpatialPyramid(void);
  SpatialPyramid(const SpatialPyramid& rhs);
  SpatialPyramid& operator=(const SpatialPyramid& rhs);

  ML_EXPORT static void pool(
    const cv::Size& imageSize,
    const std::vector<ssig::Clustering*>& clusteringMethods,
    const std::vector<cv::Vec2i>& pyramidConfigurations,
    const std::vector<float>& poolingWeights,
    const std::vector<cv::Mat_<float>>& partFeatures,
    const std::vector<cv::Rect>& partWindows,
    const std::vector<int>& scaledHeights,
    cv::Mat_<float>& output);

 protected:
  void read(const cv::FileNode& fn) override;
  void write(cv::FileStorage& fs) const override;
};
}  // namespace ssig
#endif  // !_SSF_ML_SPATIAL_PYRAMID_HPP_


