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

#include "ssiglib/descriptors/co_occurrence.hpp"

#include <opencv2/core.hpp>

namespace ssig {

void CoOccurrence::extractCoOccurrence(
  const cv::Mat& mat,
  const cv::Rect& patch,
  const int dx, const int dy,
  const int nbins, const int levels,
  cv::Mat& output) {
  output = cv::Mat::zeros(nbins, nbins, CV_32FC1);
  int binWidth = levels / nbins;

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = patch.y; i < patch.height; i++) {
    for (int j = patch.x; j < patch.width; j++) {
      if (isValidPixel(i + dy, j + dx, mat.rows, mat.cols)) {
        auto val1 = static_cast<int>(mat.at<float>(i, j) / binWidth);
        auto val2 = static_cast<int>(
          mat.at<float>(i + dy, j + dx) / binWidth);

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

void CoOccurrence::extractPairCoOccurrence(
  const cv::Mat& m1,
  const cv::Mat& m2,
  const cv::Rect window,
  const int dx, const int dy,
  const int levels1,
  const int bins1,
  const int levels2,
  const int bins2,
  cv::Mat& out) {
  out = cv::Mat::zeros(bins1, bins2, CV_32FC1);
  int binWidth1 = levels1 / bins1;
  int binWidth2 = levels2 / bins2;

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = window.y; i < window.height; i++) {
    for (int j = window.x; j < window.width; j++) {
      if (isValidPixel(i + dy, j + dx, m2.rows, m2.cols)) {
        auto val1 = static_cast<int>(m1.at<float>(i, j) / binWidth1);
        auto val2 = static_cast<int>(m2.at<float>(i, j + 1) / binWidth2);

#ifdef _OPENMP
#pragma omp critical
#endif
        {
          out.at<float>(val1, val2)++;
        }
      }
    }
  }
  out = out.reshape(1, 1);
}

int CoOccurrence::isValidPixel(int i, int j, int rows, int cols) {
  return ((i >= 0 && i < rows) && (j >= 0 && j < cols)) ? 1 : 0;
}
} // namespace ssig
