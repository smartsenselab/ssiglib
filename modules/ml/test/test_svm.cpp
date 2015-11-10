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

#include <ml/svm_classifier.hpp>

TEST(SVMClassifier, BinaryClassification) {
  /*cv::Mat_<float> inp;
  cv::Mat_<int> labels = cv::Mat_<int>::zeros(6, 1);
  inp = cv::Mat_<float>::zeros(6, 2);
  for (int i = 0; i < 3; ++i) {
    inp[i][0] = static_cast<float>(rand_r() % 5);
    inp[i][1] = static_cast<float>(rand_r() % 5);
    labels[i][0] = 1;
    inp[3 + i][0] = static_cast<float>(100 + rand_r() % 5);
    inp[3 + i][1] = static_cast<float>(100 + rand_r() % 5);
    labels[3 + i][0] = -1;
  }

  ssig::SVMClassifier classifier;
  classifier.setC(0.1f);
  classifier.setKernelType(cv::ml::SVM::LINEAR);
  classifier.setModelType(cv::ml::SVM::C_SVC);

  classifier.setTermType(cv::TermCriteria::MAX_ITER);
  classifier.setEpsilon(0.01f);

  classifier.learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100, 103);

  cv::Mat_<float> resp;
  classifier.predict(query1, resp);
  auto ordering = classifier.getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  idx = ordering[-1];
  classifier.predict(query2, resp);
  EXPECT_GE(resp[0][idx], 0);*/
}

TEST(SVMClassifier, Persistence) {
  // TODO(RICARDO):
  cv::Mat_<int> labels = (cv::Mat_<int>(6, 1) << 1, 1, 1, -1, -1, -1);
  cv::Mat_<float> inp =
      (cv::Mat_<float>(6, 2) << 1, 2, 2, 2, 4, 6, 102, 100, 104, 105, 99, 101);

  ssig::SVMClassifier classifier;
  classifier.setC(0.1f);
  classifier.setKernelType(cv::ml::SVM::LINEAR);
  classifier.setModelType(cv::ml::SVM::C_SVC);

  classifier.setTermType(cv::TermCriteria::MAX_ITER);
  classifier.setEpsilon(0.01f);

  classifier.learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1, 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100, 103);

  cv::Mat_<float> resp;
  classifier.predict(query1, resp);
  auto ordering = classifier.getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  classifier.predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);

  classifier.save("svm.yml", "root");

  ssig::SVMClassifier loaded;
  loaded.load("svm.yml", "root");

  ordering = loaded.getLabelsOrdering();
  idx = ordering[1];
  classifier.predict(query1, resp);
  EXPECT_GE(resp[0][idx], 0);
  classifier.predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}
