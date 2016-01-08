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

#include "core/math.hpp"
#include <opencv2/core.hpp>

namespace ssig {

Math::Math() {
  // Constructor
}

Math::~Math() {
  // Destructor
}

Math::Math(const Math& rhs) {
  // Constructor Copy
}

Math& Math::operator=(const Math& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

float CosineSimilarity::operator()(const cv::Mat& x,
                                   const cv::Mat& y) const {
  return static_cast<float>(
    x.dot(y) / (cv::norm(x, cv::NORM_L2)
      * cv::norm(y, cv::NORM_L2)));
}

float CorrelationSimilarity::operator()(const cv::Mat& x,
                                        const cv::Mat& y) const {
  float correlation;
  float mX = static_cast<float>(cv::mean(x)[0]);
  float mY = static_cast<float>(cv::mean(y)[0]);
  auto centeredX = x - mX;
  auto centeredY = y - mY;
  correlation = static_cast<float>(centeredX.dot(centeredY) / (
    (cv::norm(centeredX, cv::NORM_L2) * cv::norm(centeredY, cv::NORM_L2))));

  /*
  cv::Mat_<float> floatX, floatY;
  x.convertTo(floatX, CV_32FC1);
  y.convertTo(floatY, CV_32FC1);
  const auto n = x.cols;
  float i = 0, j = 0, ij = 0, ii = 0, jj = 0;
  for (int s = 0; s < n; ++s) {
    i += floatX[0][s];
    ii += floatX[0][s] * floatX[0][s];

    j += floatY[0][s];
    jj += floatY[0][s] * floatY[0][s];

    ij += floatX[0][s] * floatY[0][s];
  }
  correlation =
    (n * ij - i * j) / (cv::sqrt(n * ii - i * i) * cv::sqrt(n * jj - j * j));*/
  return correlation;
}

cv::Mat_<float> Math::buildSimilarity(
  const cv::Mat_<float>& input,
  SimilarityFunctor
  & similarityFunction) {
  int len = input.rows;
  cv::Mat_<float> similarity(len, len);
  similarity = 0;

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len; ++j) {
      cv::Mat_<float> x = input.row(i);
      cv::Mat_<float> y = input.row(j);

      similarity[i][j] = similarityFunction(x, y);
    }
  }
  return similarity;
}
}  // namespace ssig


