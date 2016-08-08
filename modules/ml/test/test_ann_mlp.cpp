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
#include "ssiglib/ml/results.hpp"
#include "ssiglib/ml/ann_mlp.hpp"



TEST(MultilayerPerceptron, SampleMultilayerPerceptron) {
  // Automatically generated stub
  cv::FileStorage inp_file("iris.yml", cv::FileStorage::READ);
  cv::Mat data;
  inp_file["samples"] >> data;
  cv::Mat labels(150, 3, CV_32F, 0.f);
  labels.rowRange(0, 50).col(0) = 1;
  labels.rowRange(50, 100).col(1) = 1;
  labels.rowRange(100, 150).col(2) = 1;

  cv::Mat X, Y;
  X = data.rowRange(10, 50);
  X.push_back(data.rowRange(60, 100));
  X.push_back(data.rowRange(110, 150));
  Y = labels.rowRange(10, 50);
  Y.push_back(labels.rowRange(60, 100));
  Y.push_back(labels.rowRange(110, 150));

  cv::Mat testX, testY;
  testX = data.rowRange(0, 10);
  testX.push_back(data.rowRange(50, 60));
  testX.push_back(data.rowRange(100, 110));
  testY = labels.rowRange(0, 10);
  testY.push_back(labels.rowRange(50, 60));
  testY.push_back(labels.rowRange(100, 110));

  auto ann_mlp = ssig::MultilayerPerceptron::create();
  // Adding the input
  ann_mlp->addLayer(4, 0);
  ann_mlp->addLayer(3, 0, 0.0f, "logistic");

  ann_mlp->setMaxIterations(5000);
  ann_mlp->setVerbose(true);
  ann_mlp->setLearningRate((float)1e-2);
  ann_mlp->setEpsilon(0.1f);

  ann_mlp->learn(X, Y);
  cv::Mat_<int> actual;
  cv::Mat_<float> resp;
  ann_mlp->predict(testX, resp, actual);

  ssig::Results res(actual, testY);
  float acc = res.getAccuracy();

  EXPECT_EQ(2, 2 + 2);
}
