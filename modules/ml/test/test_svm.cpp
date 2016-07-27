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
#include <random>
// ssiglib
#include <ssiglib/ml/svm_classifier.hpp>
#include <ssiglib/ml/results.hpp>
// opencv
#include <opencv2/core.hpp>


TEST(SVMClassifier, BinaryClassification) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1 , 1 , 1 , -1 , -1 , -1);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) << 0.8f , 0.8f , 0.7f , 0.7f , 0.9f , 0.8f ,
                                       -0.8f , -0.9f , -0.8f , -0.7f , -0.7f , -0.7f);

  auto classifier = ssig::SVMClassifier::create();

  classifier->setTermType(cv::TermCriteria::MAX_ITER);
  classifier->setEpsilon(0.01f);

  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 0.6f , 0.7f);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << -0.7f , -0.6f);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  idx = ordering[-1];
  classifier->predict(query2, resp);
  EXPECT_GE(resp[0][idx], 0);
}

TEST(SVMClassifier, Persistence) {
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1 , 1 , 1 , -1 , -1 , -1);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) << 0.8f , 0.8f , 0.7f , 0.7f , 0.9f , 0.8f ,
                                       -0.8f , -0.9f , -0.8f , -0.7f , -0.7f , -0.7f);

  auto classifier = ssig::SVMClassifier::create();
  classifier->setC(0.1f);
  classifier->setKernelType(ssig::SVMClassifier::LINEAR);
  classifier->setModelType(ssig::SVMClassifier::C_SVC);

  classifier->setTermType(cv::TermCriteria::MAX_ITER);
  classifier->setEpsilon(0.01f);

  classifier->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 0.6f , 0.7f);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << -0.7f , -0.6f);

  cv::Mat_<float> resp;
  classifier->predict(query1, resp);
  auto ordering = classifier->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  classifier->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);

  classifier->save("svm.yml", "root");
  auto loaded = ssig::SVMClassifier::create();;
  loaded->load("svm.yml", "root");
  remove("svm.yml");

  ordering = loaded->getLabelsOrdering();
  idx = ordering[1];
  loaded->predict(query1, resp);
  EXPECT_GE(resp[0][idx], 0);
  loaded->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}

TEST(SVMClassifier, SVMTernaryClassification) {
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;

  cv::FileStorage stg("oaaData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["inp"] >> inp;
  stg["labels"] >> labels;


  auto classifier = ssig::SVMClassifier::create();
  classifier->setKernelType(ssig::SVMClassifier::LINEAR);
  classifier->setModelType(ssig::SVMClassifier::C_SVC);
  classifier->setC(10.f);
  classifier->setEpsilon(1e-6f);
  classifier->setMulticlassState(true);

  classifier->learn(inp, labels);

  cv::Mat_<float> queries = (cv::Mat_<float>(3, 2) <<
    0.3f , .3f , -.1f , -.1f , .8f , .7f);

  cv::Mat_<float> resp;
  cv::Mat_<int> labelsResp;
  cv::Mat_<int> expected = (cv::Mat_<int>(3, 1) << 1, 2, 3);
  classifier->predict(queries, resp, labelsResp);
  
  ssig::Results res(labelsResp, expected);
  GTEST_ASSERT_GE(res.getAccuracy(), .9f);
}
