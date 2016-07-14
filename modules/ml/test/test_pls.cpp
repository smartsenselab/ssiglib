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
// opencv
#include <opencv2/core/ocl.hpp>
#include <opencv2/core.hpp>
// ssiglib
#include <ssiglib/ml/pls_classifier.hpp>
#include <ssiglib/ml/opencl_pls.hpp>

TEST(PLSClassifier, BinaryClassification) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1 , 1 , 1 , -1 , -1 , -1);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) <<
      1 , 2 , 2 , 2 , 4 , 6,
      102 , 100 , 104 , 105 , 99 , 101);

  auto classifier = ssig::PLSClassifier::create();
  classifier->setNumberOfFactors(2);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  classifier->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}

TEST(PLSClassifier, Persistence) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1 , 1 , 1 , -1 , -1 , -1);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) <<
      1 , 2 , 2 , 2 , 4 , 6 ,
      102 , 100 , 104 , 105 , 99 , 101);

  auto classifier = ssig::PLSClassifier::create();
  classifier->setNumberOfFactors(2);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  classifier->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);

  classifier->save("pls.yml", "root");

  auto loaded = ssig::PLSClassifier::create();
  loaded->load("pls.yml", "root");
  remove("pls.yml");

  ordering = loaded->getLabelsOrdering();
  idx = ordering[1];
  resp.release();
  loaded->predict(query1, resp);
  EXPECT_GE(resp[0][idx], 0);
  loaded->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}

TEST(PLSClassifier, MultiClassification) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1, 1, 2, 2, 3, 3);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) <<
      1, 2,
      2, 2,
      1005, 1001,
      1000, 1000,
      100, 99,
      99, 101);

  auto classifier = ssig::PLSClassifier::create();
  classifier->setNumberOfFactors(2);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 1000, 1003);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << 100 , 103);
  cv::Mat_<float> queries;
  queries.push_back(query1);
  queries.push_back(query2);
  queries.push_back(query3);

  cv::Mat_<float> resp;
  cv::Mat_<int> actual;
  classifier->predict(queries, resp, actual);

  
  classifier->predict(query1, resp);
  int idx[2];
  cv::minMaxIdx(resp, 0, 0, 0, idx);
  EXPECT_EQ(0, idx[1]);
  EXPECT_EQ(actual.at<int>(0), 1);

  classifier->predict(query2, resp);
  cv::minMaxIdx(resp, 0, 0, 0, idx);
  EXPECT_EQ(1, idx[1]);
  EXPECT_EQ(actual.at<int>(1), 2);
  classifier->predict(query3, resp);
  cv::minMaxIdx(resp, 0, 0, 0, idx);
  EXPECT_EQ(2, idx[1]);
  EXPECT_EQ(actual.at<int>(2), 3);
}

TEST(OpenClPLSClassifier, BinaryClassification) {
  cv::Mat_<int> labelsInt = (cv::Mat_<int>(6, 1) << 1, 1, 1, -1, -1, -1);
  cv::Mat_<float> inp =
    (cv::Mat_<float>(6, 2) <<
    1, 2, 2, 2, 4, 6,
    102, 100, 104, 105, 99, 101);

  cv::Mat_<float> labels;
  labelsInt.convertTo(labels, CV_32F);

  auto classifier = ssig::OpenClPLS::create();
  classifier->learn(inp, labels, 2);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100, 103);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  EXPECT_GE(resp.at<float>(0), 0);
  classifier->predict(query2, resp);
  EXPECT_LE(resp.at<float>(0), 0);
}

TEST(OpenClPLSClassifier, Persistence) {
  cv::Mat_<int> labelsInt = (cv::Mat_<int>(6, 1) << 1, 1, 1, -1, -1, -1);
  cv::Mat_<float> inp =
    (cv::Mat_<float>(6, 2) <<
    1, 2, 2, 2, 4, 6,
    102, 100, 104, 105, 99, 101);

  cv::Mat_<float> labels;
  labelsInt.convertTo(labels, CV_32F);

  auto classifier = ssig::OpenClPLS::create();
  classifier->learn(inp, labels, 2);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100, 103);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  EXPECT_GE(resp.at<float>(0), 0);
  classifier->predict(query2, resp);
  EXPECT_LE(resp.at<float>(0), 0);

  classifier->save("pls.yml");

  auto loaded = ssig::PLSClassifier::create();
  loaded->load("pls.yml", "root");
  remove("pls.yml");

  resp.release();
  loaded->predict(query1, resp);
  EXPECT_GE(resp.at<float>(0), 0);
  loaded->predict(query2, resp);
  EXPECT_LE(resp.at<float>(0), 0);
}

