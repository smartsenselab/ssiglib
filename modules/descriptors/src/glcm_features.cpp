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

#include "descriptors/glcm_features.hpp"

#include <stdexcept>

#include <opencv2/imgproc.hpp>

namespace ssig {
  GrayLevelCoOccurrence::GrayLevelCoOccurrence(const cv::Mat& input) :
    Descriptor2D(input) {}

  GrayLevelCoOccurrence::GrayLevelCoOccurrence(const cv::Mat& input,
    const GrayLevelCoOccurrence& descriptor) :
    Descriptor2D(input, descriptor) {}

  GrayLevelCoOccurrence::GrayLevelCoOccurrence(
    const GrayLevelCoOccurrence& descriptor) : Descriptor2D(descriptor) {}

  int GrayLevelCoOccurrence::getLevels() const {
    return mLevels;
  }

  int GrayLevelCoOccurrence::getBins() const {
    return mBins;
  }

  void GrayLevelCoOccurrence::setLevels(const int levels) {
    mLevels = levels;
  }

  void GrayLevelCoOccurrence::setBins(const int bins) {
    mBins = bins;
  }

  void GrayLevelCoOccurrence::read(const cv::FileNode& fn) { }

  void GrayLevelCoOccurrence::write(cv::FileStorage& fs) const { }

  void GrayLevelCoOccurrence::beforeProcess() {
    if (mImage.channels() == 3 || mImage.channels() == 4)
      cv::cvtColor(mImage, mGreyImg, CV_BGR2GRAY);
    else
      mImage.copyTo(mGreyImg);

    mGreyImg.convertTo(mGreyImg, CV_32FC1);
  }

  void GrayLevelCoOccurrence::extractFeatures(const cv::Rect& patch,
    cv::Mat& output) {
    output = cv::Mat::zeros(mBins, mBins, CV_32FC1);
    int binWidth = mLevels / mBins;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = patch.y; i < patch.height; i++) {
      for (int j = patch.x; j < patch.width; j++) {
        if (isValidPixel(i + mDi, j + mDj, mGreyImg.rows, mGreyImg.cols)) {
          auto val1 = static_cast<int>(mGreyImg.at<float>(i, j) / binWidth);
          auto val2 = static_cast<int>(
            mGreyImg.at<float>(i + mDi, j + mDj) / binWidth);

#ifdef _OPENMP
#pragma omp critical
#endif
          {
            output.at<float>(val1, val2)++;
          }
        }
      }
    }
    output = output.reshape(1, 1);
  }

  int GrayLevelCoOccurrence::isValidPixel(int i, int j, int rows, int cols) {
    return ((i >= 0 && i < rows) && (j >= 0 && j < cols)) ? 1 : 0;
  }

}  // namespace ssig


