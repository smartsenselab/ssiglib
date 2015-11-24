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

#include <ml/pls_classifier.hpp>
#include <ml/hard_mining_classifier.hpp>

class HardMiningClassifierTest : public ::testing::Test {
 protected:
  cv::Mat_<int> labels;
  cv::Mat_<float> inp;
  cv::Mat_<float> negatives;
  ssig::PLSClassifier classifier;
  std::unique_ptr<ssig::HardMiningClassifier> hmc;


  void SetUp() override {
    labels = (cv::Mat_<int>(6, 1) << 1 , 1 , 1 , -1 , -1 , -1);
    inp =
      (cv::Mat_<float>(6, 2) << 1 , 2 , 2 , 2 , 4 , 6 ,
        102 , 100 , 104 , 105 , 99 , 101);

    negatives =
      (cv::Mat_<float>(3, 2) << 100 , 100 , 101 , 101 , 102 , 102);


    classifier.setNumberOfFactors(2);
    hmc = std::unique_ptr<ssig::HardMiningClassifier>
      (new ssig::HardMiningClassifier(classifier));

    hmc->setMaxIterations(6);
    hmc->setNegatives(negatives);
  }
};

TEST_F(HardMiningClassifierTest, SimpleExecution) {
  hmc->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);
  cv::Mat_<float> resp;
  hmc->predict(query1, resp);
  auto ordering = hmc->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  hmc->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}

TEST_F(HardMiningClassifierTest, Improvement) {}

TEST_F(HardMiningClassifierTest, Persistence) {
  hmc->learn(inp, labels);

  cv::Mat_<float> query1 = (cv::Mat_<float>(1, 2) << 1 , 2);
  cv::Mat_<float> query2 = (cv::Mat_<float>(1, 2) << 100 , 103);

  cv::Mat_<float> resp;
  hmc->predict(query1, resp);
  auto ordering = hmc->getLabelsOrdering();
  int idx = ordering[1];
  EXPECT_GE(resp[0][idx], 0);
  hmc->predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);

  hmc->save("hmc.yml", "root");

  ssig::PLSClassifier pls;
  ssig::HardMiningClassifier loaded(pls);

  loaded.load("hmc.yml", "root");
  remove("hmc.yml");

  ordering = loaded.getLabelsOrdering();
  idx = ordering[1];
  resp.release();
  loaded.predict(query1, resp);
  EXPECT_GE(resp[0][idx], 0);
  loaded.predict(query2, resp);
  idx = ordering[-1];
  EXPECT_GE(resp[0][idx], 0);
}

