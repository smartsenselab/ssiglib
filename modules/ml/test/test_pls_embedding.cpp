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

#include <gtest/gtest.h>
// c++
#include <algorithm>
// ssiglib
#include "ssiglib/core/math.hpp"
#include "ssiglib/ml/pls_embedding.hpp"

TEST(PLSEmbedding, SamplePLSEmbedding) {
  cv::Mat_<float> labels, X,
    Xmean, Xstd, Xz,
    Ymean, Ystd, Yz;

  X = cv::Mat::zeros(30, 10, CV_32FC1);
  labels = cv::Mat::zeros(30, 1, CV_32FC1);

  cv::randn(X.rowRange(0, 15),
    cv::Mat::zeros(1, 1, CV_32F),
    cv::Mat::ones(1, 1, CV_32F));
  cv::randn(X.rowRange(15, 30),
    cv::Mat(1, 1, CV_32F, 10),
    cv::Mat::ones(1, 1, CV_32F));

  labels.rowRange(0, 15) = 1.0f;
  labels.rowRange(15, 30) = -1.0f;

  ssig::computeMeanStd(X, cv::ml::COL_SAMPLE, Xmean, Xstd);
  ssig::computeMeanStd(labels, cv::ml::COL_SAMPLE, Ymean, Ystd);

  Xz = X.clone();
  Yz = labels.clone();
  ssig::computeZScore(Xz, Xmean, Xstd);
  ssig::computeZScore(Yz, Ymean, Ystd);

  cv::Mat labelCovarMat = Xz.t()*Yz;
  labelCovarMat = cv::abs(labelCovarMat);
  cv::sort(labelCovarMat,
    labelCovarMat,
    cv::SORT_EVERY_COLUMN + cv::SORT_DESCENDING);

  float labelCovar = static_cast<float>(cv::sum(labelCovarMat)[0]);
  auto embedder = ssig::PLSEmbedding::create(10, labels);

  embedder->learn(X);
  cv::Mat_<float> projection;
  embedder->project(X, projection);

  cv::Mat_<float> mean, std;
  ssig::computeMeanStd(projection, cv::ml::COL_SAMPLE, mean, std);
  ssig::computeZScore(projection, mean, std);

  cv::Mat new_labelCovarMat = projection.t()*Yz;
  float reducedSum = static_cast<float>(
    cv::sum(new_labelCovarMat)[0]);
  float trace = static_cast<float>(cv::trace(new_labelCovarMat)[0]);

  EXPECT_LT(reducedSum, labelCovar);
  EXPECT_GT(trace, (reducedSum - trace));
}

TEST(PLSEmbedding, 2DSamplePLSEmbedding) {
  cv::Mat_<float> labels, X,
    Xmean, Xstd, Xz,
    Ymean, Ystd, Yz;

  X = cv::Mat::zeros(30, 10, CV_32FC1);
  labels = cv::Mat(30, 2, CV_32FC1, -1.f);

  cv::randn(X.rowRange(0, 15),
    cv::Mat::zeros(1, 1, CV_32F),
    cv::Mat::ones(1, 1, CV_32F));
  cv::randn(X.rowRange(15, 30),
    cv::Mat(1, 1, CV_32F, 10),
    cv::Mat::ones(1, 1, CV_32F));

  labels.rowRange(0, 15).col(0) = 1.0f;
    labels.rowRange(15, 30).col(1) = 1.0f;

  ssig::computeMeanStd(X, cv::ml::COL_SAMPLE, Xmean, Xstd);
  ssig::computeMeanStd(labels, cv::ml::COL_SAMPLE, Ymean, Ystd);

  Xz = X.clone();
  Yz = labels.clone();
  ssig::computeZScore(Xz, Xmean, Xstd);
  ssig::computeZScore(Yz, Ymean, Ystd);


  cv::Mat labelCovarMat = Xz.t()*Yz;
  labelCovarMat = cv::abs(labelCovarMat);
  cv::sort(
    labelCovarMat,
    labelCovarMat,
    cv::SORT_EVERY_COLUMN + cv::SORT_DESCENDING);

  float labelCovar = static_cast<float>(cv::sum(labelCovarMat)[0]);
  auto embedder = ssig::PLSEmbedding::create(10, labels);

  embedder->learn(X);
  cv::Mat_<float> projection;
  embedder->project(X, projection);

  cv::Mat_<float> mean, std;
  ssig::computeMeanStd(projection, cv::ml::COL_SAMPLE, mean, std);
  ssig::computeZScore(projection, mean, std);

  cv::Mat new_labelCovarMat = projection.t()*Yz;
  float reducedSum = static_cast<float>(
    cv::sum(new_labelCovarMat)[0]);
  float trace = static_cast<float>(cv::trace(new_labelCovarMat)[0]);

  EXPECT_LT(reducedSum, labelCovar);
  EXPECT_GT(trace, (reducedSum - trace));
}
