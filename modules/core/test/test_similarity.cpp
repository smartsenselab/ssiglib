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
#include <opencv2/core.hpp>

#include <core/math.hpp>

TEST(Cosine, PerpendicularitySimilarityTest) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 2) << 0 , 1 , 1 , 0);

  ssig::CosineSimilarity cosine;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, cosine);

  EXPECT_FLOAT_EQ(0, simMat[0][1]);
}

TEST(Cosine, OposityTest) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 2) << 0 , 1 , 0 , -1);

  ssig::CosineSimilarity cosine;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, cosine);

  EXPECT_FLOAT_EQ(-1, simMat[0][1]);
}

TEST(Cosine, SimpleTest) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 2) << 3 , 4 , 1 , 2);

  ssig::CosineSimilarity cosine;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, cosine);

  EXPECT_FLOAT_EQ(0.9838699101f, simMat[0][1]);
}

TEST(Cosine, OddDimensionalityTest) {
  cv::Mat_<float> samples =
    (cv::Mat_<float>(3, 3) << 0 , 0 , 1 , 0 , 1 , 0 , 0 , -1 , 0);

  ssig::CosineSimilarity cosine;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, cosine);

  ASSERT_FLOAT_EQ(0, simMat[0][1]);
  ASSERT_FLOAT_EQ(0, simMat[0][2]);
  ASSERT_FLOAT_EQ(-1, simMat[1][2]);
}

TEST(Correlation, CorrelatedCheck) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 2) << 1 , 2 , 3 , 4);

  ssig::CorrelationSimilarity correlation;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, correlation);

  EXPECT_GT(simMat[0][1], 0.5);
}

TEST(Correlation, InverseCorrelatedCheck) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 2) << 1 , 2 , -1 , -2);

  ssig::CorrelationSimilarity correlation;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, correlation);

  EXPECT_LT(simMat[0][1], -0.5);
}

TEST(Correlation, CorrelatedOddSized) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 3) << 3 , 5 , 7 , 6 , 18 , 14);

  ssig::CorrelationSimilarity correlation;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, correlation);

  EXPECT_GT(simMat[0][1], 0.5);
}

TEST(Correlation, InverseCorrelatedOddSized) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 3) << 3 , 5 , 7 , -6 , -18 , -14);

  ssig::CorrelationSimilarity correlation;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, correlation);

  EXPECT_LT(simMat[0][1], -0.5);
}

TEST(Correlation, UncorrelatedOddSized) {
  cv::Mat_<float> samples = (cv::Mat_<float>(2, 3) << 3 , 5 , 7 , 1 , -5 , 2);

  ssig::CorrelationSimilarity correlation;
  cv::Mat_<float> simMat = ssig::Math::buildSimilarity(
    samples, correlation);

  EXPECT_LT(abs(simMat[0][1]), 0.5);
}

