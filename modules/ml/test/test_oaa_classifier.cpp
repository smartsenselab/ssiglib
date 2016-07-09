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

#include <ssiglib/ml/oaa_classifier.hpp>
#include <ssiglib/ml/pls_classifier.hpp>
#include <ssiglib/ml/svm_classifier.hpp>

TEST(OAAClassifier, PLSBinaryClassification) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) <<
    1 , 1 , 1 , -1 , -1 , -1);
  cv::Mat_<float> inp = (cv::Mat_<float>(6, 2) <<
    1 , 2 ,
    2 , 2 ,
    4 , 6 ,
    102 , 100 ,
    104 , 105 ,
    99 , 101);


  ssig::PLSClassifier underlying;
  underlying.setNumberOfFactors(2);
  auto classifier = ssig::OAAClassifier::create(underlying);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_EQ(0, idx);
  EXPECT_GE(resp[0][idx], 0);
  idx = ordering[-1];
  EXPECT_EQ(1, idx);
  classifier->predict(query2, resp);
  EXPECT_GE(resp[0][idx], 0);
}

TEST(OAAClassifier, PLSTernaryClassification) {
  cv::Mat_<float> inp = (cv::Mat_<float>(9, 2) <<
    3., 4., 0., 0., 2., 1.,
    1003., 1002., 1000., 1002., 1002., 1001.,
    10000., 10002., 10003., 10000., 10000., 10000.);

  cv::Mat_<int> labels = (cv::Mat_<int>(9, 1) << 1, 1, 1,
    2, 2, 2,
    3, 3, 3);

  ssig::PLSClassifier underlying;
  underlying.setNumberOfFactors(2);
  auto classifier = ssig::OAAClassifier::create(underlying);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 1000, 1030);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << 10000, 10000);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  classifier->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);
}

TEST(OAAClassifier, SVMTernaryClassification) {
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;

  cv::FileStorage stg("oaaData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["inp"] >> inp;
  stg["labels"] >> labels;


  ssig::SVMClassifier underlying;
  underlying.setKernelType(ssig::SVMClassifier::LINEAR);
  underlying.setModelType(ssig::SVMClassifier::C_SVC);
  underlying.setC(10.f);
  underlying.setEpsilon(1e-6f);

  auto classifier = ssig::OAAClassifier::create(underlying);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 0.3f , .3f);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << -.1f , -.1f);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << .8f , .7f);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();

  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  classifier->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);
}


TEST(OAAClassifier, SVMPersistence) {
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;

  cv::FileStorage stg("oaaData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["inp"] >> inp;
  stg["labels"] >> labels;

  ssig::SVMClassifier underlying;
  underlying.setKernelType(ssig::SVMClassifier::LINEAR);
  underlying.setModelType(ssig::SVMClassifier::C_SVC);
  underlying.setC(10.f);
  underlying.setEpsilon(1e-4f);

  auto classifier = ssig::OAAClassifier::create(underlying);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 0.3f , .3f);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << -.1f , -.1f);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << .8f , .7f);

  cv::Mat_<float> resp;
  auto ordering = classifier->getLabelsOrdering();

  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;

  classifier->predict(query1, resp);
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);

  classifier->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);

  classifier->save("oaa.yml", "root");

  auto loaded = ssig::OAAClassifier::create(underlying);
  loaded->load("oaa.yml", "root");

  loaded->predict(query1, resp);
  ordering = loaded->getLabelsOrdering();
  label1 = ordering[1];
  label2 = ordering[2];
  label3 = ordering[3];

  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  loaded->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  loaded->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);
}

TEST(OAAClassifier, PLSPersistence) {
  cv::Mat_<float> inp = (cv::Mat_<float>(9, 2) <<
    3., 4., 0., 0., 2., 1.,
    1003., 1002., 1000., 1002., 1002., 1001.,
    10000., 10002., 10003., 10000., 10000., 10000.);

  cv::Mat_<int> labels = (cv::Mat_<int>(9, 1) << 1, 1, 1,
    2, 2, 2,
    3, 3, 3);

  ssig::PLSClassifier underlying;
  underlying.setNumberOfFactors(2);
  auto classifier = ssig::OAAClassifier::create(underlying);
  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 1000, 1030);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << 10000, 10000);
  cv::Mat_<float> resp;
  auto ordering = classifier->getLabelsOrdering();

  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;

  classifier->predict(query1, resp);
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);

  classifier->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);

  classifier->save("oaa.yml", "root");

  auto loaded = ssig::OAAClassifier::create(underlying);
  loaded->load("oaa.yml", "root");
  remove("oaa.yml");

  loaded->predict(query1, resp);
  ordering = loaded->getLabelsOrdering();
  label1 = ordering[1];
  label2 = ordering[2];
  label3 = ordering[3];

  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  loaded->predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  loaded->predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);
}

