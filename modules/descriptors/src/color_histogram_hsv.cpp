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

#include "descriptors/color_histogram_hsv.hpp"

#include <opencv2/imgproc.hpp>

namespace ssig {

ColorHistogramHSV::ColorHistogramHSV(const cv::Mat& input):
  Descriptor2D(input) {}

ColorHistogramHSV::ColorHistogramHSV(const cv::Mat& input,
                                     const Descriptor2D& descriptor) :
  Descriptor2D(input, descriptor) {}

ColorHistogramHSV::ColorHistogramHSV(const Descriptor2D& descriptor) :
Descriptor2D(descriptor) {}

ColorHistogramHSV::ColorHistogramHSV(const ColorHistogramHSV& rhs) :
  Descriptor2D(rhs) {
  // Constructor Copy
}

int ColorHistogramHSV::getNumberHueBins() const {
  return mNumberHueBins;
}

void ColorHistogramHSV::setNumberHueBins(const int numberHueBins) {
  mNumberHueBins = numberHueBins;
}

int ColorHistogramHSV::getNumberSaturationBins() const {
  return mNumberSaturationBins;
}

void ColorHistogramHSV::setNumberSaturationBins(
  const int numberSaturationBins) {
  mNumberSaturationBins = numberSaturationBins;
}

int ColorHistogramHSV::getNumberValueBins() const {
  return mNumberValueBins;
}

void ColorHistogramHSV::setNumberValueBins(const int numberValueBins) {
  mNumberValueBins = numberValueBins;
}

void ColorHistogramHSV::read(const cv::FileNode& fn) {
  std::runtime_error("Unimplemented");
}

void ColorHistogramHSV::write(cv::FileStorage& fs) const {
  std::runtime_error("Unimplemented");
}

void ColorHistogramHSV::beforeProcess() {
  if (mImage.channels() != 3)
    std::invalid_argument("Mat needs to have 3 channels");
  cv::Mat temp;
  cv::cvtColor(mImage, temp, CV_BGR2HSV);
  mImage = temp;
}

void ColorHistogramHSV::extractFeatures(const cv::Rect& patch,
                                        cv::Mat& output) {
  auto roi = mImage(patch);

  const int bins = mNumberHueBins * mNumberValueBins * mNumberSaturationBins;
  int channels[] = {0, 1, 2};
  int histSize[] = {mNumberHueBins, mNumberSaturationBins, mNumberValueBins};
  float hrange[] = {0, 180};
  float srange[] = {0, 256};
  float vrange[] = {0, 256};
  const float* ranges[] = {hrange, srange, vrange};
  cv::calcHist(&roi, 1, channels, cv::Mat(), output, 3, histSize,
               ranges);

  cv::Mat_<float> linearHist(1, bins, 0.0f);
  int idx = 0;
  for (int j = 0; j < mNumberSaturationBins; ++j) {
    for (int k = 0; k < mNumberValueBins; ++k) {
      for (int i = 0; i < mNumberHueBins; ++i) {
        linearHist.at<float>(idx++) = output.at<float>(i, j, k);
      }
    }
  }
  cv::normalize(linearHist, linearHist, 1, 0, cv::NORM_L1);
  output = linearHist;
}
}  // namespace ssig


