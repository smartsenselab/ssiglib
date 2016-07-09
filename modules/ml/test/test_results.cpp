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
#include <string>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include <ssiglib/ml/results.hpp>
#include <ssiglib/ml/svm_classifier.hpp>

TEST(Results, binaryConfMat) {
  cv::Mat_<int> gt = (cv::Mat_<int>(4, 1) << 0 , 1 , 0 , 1);
  cv::Mat_<int> labels = (cv::Mat_<int>(4, 1) << 0 , 1 , 1 , 1);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(2, 2) <<
    1 , 1 ,
        0 , 2);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  ASSERT_EQ(zeroes, 4);

  ASSERT_FLOAT_EQ(0.75f, results.getAccuracy());
}

TEST(Results, randomConfusion) {
  cv::Mat_<int> gt = (cv::Mat_<int>(4, 1) << 0 , 1 , 0 , 1);
  cv::Mat_<int> labels = (cv::Mat_<int>(4, 1) << 0 , 1 , 1 , 1);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat avgRandConf;
  const int N = 50000;
  for (int c = 0; c < N; ++c) {
    cv::Mat randConf = results.getRandomConfusion();
    if (avgRandConf.empty())
      avgRandConf = randConf;
    else
      avgRandConf += randConf;
  }
  avgRandConf.convertTo(avgRandConf, CV_32F);
  auto randPrec = static_cast<float>(
    (cv::trace(avgRandConf) / cv::sum(avgRandConf))[0]);
  avgRandConf /= N;

  ASSERT_LT(std::abs(0.5f - randPrec), 0.75f);
}

TEST(Results, simpleConfMat) {
  cv::Mat_<int> gt = (cv::Mat_<int>(4, 1) << 0 , 1 , 2 , 1);
  cv::Mat_<int> labels = (cv::Mat_<int>(4, 1) << 0 , 1 , 1 , 2);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(3, 3) <<
    1 , 0 , 0 ,
        0 , 1 , 1 ,
        0 , 1 , 0);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  // cv::Mat vis;
  // ssig::Results::makeConfusionMatrixVisualization(10, confMat, vis);

  ASSERT_EQ(zeroes, 9);

  ASSERT_FLOAT_EQ(0.5f, results.getAccuracy());
}

TEST(Results, MissingLabel_gt) {
  cv::Mat_<int> gt = (cv::Mat_<int>(5, 1) << 0 , 1 , 2 , 1 , 3);
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 0 , 1 , 1 , 2 , 0);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(4, 4) <<
    1 , 0 , 0 , 0 ,
        0 , 1 , 1 , 0 ,
        0 , 1 , 0 , 0 ,
        1 , 0 , 0 , 0);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  cv::Mat vis;
  std::unordered_map<int, std::string> stringLabels = {
    {0, "abb"},
    {1, "bbc"},
    {2, "cbd"},
    {3, "brad"}
  };
  results.setStringLabels(stringLabels);
  results.makeConfusionMatrixVisualization(false, 50, vis);

  EXPECT_EQ(zeroes, 16);

  ASSERT_FLOAT_EQ(0.4f, results.getAccuracy());
}

TEST(Results, MissingLabel2_gt) {
  cv::Mat_<int> gt = (cv::Mat_<int>(5, 1) << 0 , 1 , 2 , 1 , 3);
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 0 , 1 , 1 , 3 , 0);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(4, 4) <<
    1 , 0 , 0 , 0 ,
        0 , 1 , 0 , 1 ,
        0 , 1 , 0 , 0 ,
        1 , 0 , 0 , 0);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  cv::Mat vis;
  std::unordered_map<int, std::string> stringLabels = {
    {0, "abb"},
    {1, "bbc"},
    {2, "cbd"},
    {3, "brad"}
  };
  results.setStringLabels(stringLabels);
  results.makeConfusionMatrixVisualization(false, 50, vis);

  EXPECT_EQ(zeroes, 16);

  ASSERT_FLOAT_EQ(0.4f, results.getAccuracy());
}

TEST(Results, MissingLabel) {
  cv::Mat_<int> gt = (cv::Mat_<int>(5, 1) << 0 , 1 , 2 , 1 , 2);
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 0 , 1 , 1 , 2 , 3);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(4, 4) <<
    1 , 0 , 0 , 0 ,
        0 , 1 , 1 , 0 ,
        0 , 1 , 0 , 1 ,
        0 , 0 , 0 , 0);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  EXPECT_EQ(zeroes, 16);

  ASSERT_FLOAT_EQ(0.4f, results.getAccuracy());

  float meanAccuracy = results.getMeanAccuracy();

  ASSERT_FLOAT_EQ((1.5f)/4.f, meanAccuracy);
}

TEST(Results, MissingLabel2) {
  cv::Mat_<int> gt = (cv::Mat_<int>(5, 1) << 0 , 1 , 2 , 1 , 2);
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 0 , 1 , 1 , 2 , 4);

  ssig::Results results(labels, gt);

  auto confMat = results.getConfusionMatrix();

  cv::Mat_<int> EXPECTED = (cv::Mat_<int>(4, 4) <<
    1 , 0 , 0 , 0 ,
        0 , 1 , 1 , 0 ,
        0 , 1 , 0 , 1 ,
        0 , 0 , 0 , 0);
  cv::Mat out;
  cv::compare(confMat, EXPECTED, out, cv::CMP_EQ);
  auto zeroes = cv::countNonZero(out);

  EXPECT_EQ(zeroes, 16);

  ASSERT_FLOAT_EQ(0.4f, results.getAccuracy());

  float meanAccuracy = results.getMeanAccuracy();

  ASSERT_FLOAT_EQ((1 + .5f) / 4.f, meanAccuracy);
}

TEST(Results, LeaveOneOut) {
  cv::Mat_<float> inp = (cv::Mat_<float>(6, 2) <<
    3., 4., 0., 0., 2., 1.,
    10000., 10002., 10003., 10000., 10000., 10000.);

  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << -1, -1, -1,
    1, 1, 1);

  auto classifier = ssig::SVMClassifier::create();
  classifier->setC(0.1);
  classifier->setKernelType(ssig::SVMClassifier::LINEAR);
  classifier->setModelType(ssig::SVMClassifier::C_SVC);

  ssig::Results results;
  auto p = ssig::Results::leaveOneOut(inp, labels, *classifier, false, results);

  ASSERT_FLOAT_EQ(1.f, p);
}

