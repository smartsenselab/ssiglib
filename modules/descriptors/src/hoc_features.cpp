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

#include "descriptors/hoc_features.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

namespace ssig {
HOC::HOC(const cv::Mat& input) : Descriptor2D(input) {}

HOC::HOC(const cv::Mat& input, const Descriptor& descriptor) :
  Descriptor2D(input, descriptor) {}

HOC::HOC(const HOC& rhs) : Descriptor2D(rhs) {
  // Constructor Copy
}

void HOC::read(const cv::FileNode& fn) {}

void HOC::write(cv::FileStorage& fs) const {}

void HOC::beforeProcess() {
  cv::HOGDescriptor hogCalculator;
  cv::Mat grad, angleOfs;
  int rows = mImage.rows, cols = mImage.cols;
  hogCalculator.computeGradient(mImage, grad, angleOfs);
  mMasks.resize(mGradientBins + 1);
  for (int i = 0; i < mGradientBins + 1; ++i)
    mMasks[i] = cv::Mat::zeros(rows, cols, CV_8UC1);

  std::vector<cv::Mat> angles;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grad.at<cv::Vec2f>(i, j)[0] > 0.0f) {
        auto bin = static_cast<int>(angleOfs.at<cv::Vec2b>(i, j)[0]);
        mMasks[bin].at<uchar>(i, j) = 255;
      } else {
        mMasks[mGradientBins].at<uchar>(i, j) = 255;
      }
    }
  }

  cv::cvtColor(mImage, mImage, CV_BGR2HSV);
}

void HOC::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
  const int nbins = mHueBins * mSaturationBins * mValueBins;
  const int totalBins = nbins * (mGradientBins + 1);

  cv::Mat roi = mImage(patch);

  output.create(1, totalBins, CV_32F);
  output = 0;
  for (int i = 0; i < mGradientBins + 1; ++i) {
    cv::Mat roiMask = mMasks[i](patch);

    int channels[] = {0, 1, 2};
    int histSize[] = {mHueBins, mSaturationBins, mValueBins};
    float hrange[] = {0, 180};
    float srange[] = {0, 256};
    float vrange[] = {0, 256};
    const float* ranges[] = {hrange, srange, vrange};

    cv::Mat hist;
    cv::calcHist(&roi, 1, channels, roiMask, hist, 3, histSize, ranges);
    int j = -1;
    cv::Mat_<float> outputRoi = output(cv::Rect(i * nbins, 0, nbins, 1));
    for (int s = 0; s < mSaturationBins; ++s) {
      for (int v = 0; v < mValueBins; ++v) {
        for (int h = 0; h < mHueBins; ++h) {
          auto value = hist.at<float>(h, s, v);
          if(value > 0)
            outputRoi.at<float>(++j) = value;
        }
      }
    }
  }
  cv::normalize(output, output, 1, 0, cv::NORM_L1);
}


} // namespace ssig


