/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this license. If you do
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of
*       conditions and the following disclaimer in the documentation and/or other materials
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to
*       endorse or promote products derived from this software without specific prior written
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#include <gtest/gtest.h>
#include <opencv2/core.hpp>

#include <algorithms/oaaClassifier.hpp>
#include <algorithms/plsClassifier.hpp>
#include <algorithms/svmClassifier.hpp>

TEST(PLSOAAClassifier, BinaryClassification){
  cv::Mat_<float> inp;
  cv::Mat_<int> labels = cv::Mat_<int>::zeros(6, 1);
  inp = cv::Mat_<float>::zeros(6, 2);
  for(int i = 0; i < 3; ++i){
    inp[i][0] = static_cast<float>(rand() % 5);
    inp[i][1] = static_cast<float>(rand() % 5);
    labels[i][0] = 1;
    inp[3 + i][0] = static_cast<float>(100 + rand() % 5);
    inp[3 + i][1] = static_cast<float>(100 + rand() % 5);
    labels[3 + i][0] = -1;
  }

  auto p = new ssf::PLSParameters;
  p->factors = 2;

  ssf::OAAClassifier<ssf::PLSClassifier> classifier;
  classifier.learn(inp, labels, p);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);

  cv::Mat_<float> resp;
  classifier.predict(query1, resp);
  auto ordering = classifier.getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  idx = ordering[-1];
  classifier.predict(query2, resp);
  ASSERT_GE(resp[0][idx], 0);

  delete p;
}

TEST(PLSOAAClassifier, TernaryClassification){
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;
  cv::FileStorage stg("oaaData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["inp"] >> inp;
  stg["labels"] >> labels;

  auto p = new ssf::PLSParameters;
  p->factors = 2;

  ssf::OAAClassifier<ssf::PLSClassifier> classifier;
  classifier.learn(inp, labels, p);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 1000 , 1030);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << 10000 , 10000);

  cv::Mat_<float> resp;
  classifier.predict(query1, resp);
  auto ordering = classifier.getLabelsOrdering();
  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  classifier.predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier.predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);

  delete p;
}

TEST(SVMOAAClassifier, TernaryClassification){
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;

  cv::FileStorage stg("oaaData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["inp"] >> inp;
  stg["labels"] >> labels;

  ssf::SVMParameters* p = new ssf::SVMParameters;
  p->kernelType = cv::ml::SVM::LINEAR;
  p->modelType = cv::ml::SVM::C_SVC;
  p->c = 0.1f;
  p->termType = cv::TermCriteria::MAX_ITER;
  p->eps = 0.01f;

  ssf::OAAClassifier<ssf::SVMClassifier> classifier;
  classifier.learn(inp, labels, p);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 1000 , 1030);
  cv::Mat_<float> query3 = (cv::Mat_<float>(1, 2) << 10000 , 10000);

  cv::Mat_<float> resp;
  classifier.predict(query1, resp);
  auto ordering = classifier.getLabelsOrdering();

  int label1 = ordering[1];
  int label2 = ordering[2];
  int label3 = ordering[3];

  double maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(1) != ordering.end());
  EXPECT_GE(resp[0][label1], maxResp);


  classifier.predict(query2, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(2) != ordering.end());
  EXPECT_GE(resp[0][label2], maxResp);


  classifier.predict(query3, resp);
  maxResp = 0.0;
  cv::minMaxIdx(resp, nullptr, &maxResp);
  EXPECT_TRUE(ordering.find(3) != ordering.end());
  EXPECT_GE(resp[0][label3], maxResp);

  delete p;
}


TEST(OAAClassifier, Persistence){
  //TODO:
}
