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
#include <vector>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include "ssiglib/core/math.hpp"
#include "ssiglib/ml/kmeans.hpp"
#include "ssiglib/ml/pls_classifier.hpp"
#include "ssiglib/ml/pls_image_clustering.hpp"


TEST(PLSIC, CorrelationClusteringTest) {
  srand(1234);
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;

  auto plsclassifier = ssig::PLSClassifier::create();
  plsclassifier->setNumberOfFactors(2);

  auto oaaclassifier = ssig::OAAClassifier::create(*plsclassifier);

  std::vector<ssig::Cluster> discoverySubsets;
  discoverySubsets.resize(2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 30; ++j) {
      discoverySubsets[i].push_back(j + (30 * i));
    }
  }

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["discovery"] >> inp;
  stg.release();

  std::vector<ssig::Cluster> initialClustering =
      {{1}, {8}, {14}, {15}, {23}, {28}};
  std::vector<ssig::Cluster> natVector = {{}, {}};

  auto clustering = ssig::PLSImageClustering::create(
                                                     *oaaclassifier,
                                                     discoverySubsets,
                                                     initialClustering);
  clustering->setK(2);
  clustering->setClusterRepresentationType(
    ssig::ClusterRepresentationType::ClustersResponses);
  clustering->setMergeThreshold(0.7f);
  auto correlation = std::unique_ptr<ssig::CorrelationSimilarity>(
    new ssig::CorrelationSimilarity);
  clustering->setSimBuilder(std::move(correlation));
  clustering->setDiscoveryConfiguration(discoverySubsets);
  clustering->setClusterSize(5);
  clustering->setMaxIterations(8);
  clustering->setClassifier(*oaaclassifier);


  clustering->addNaturalWorld(neg, natVector);

  clustering->setInitialClustering(initialClustering);
  clustering->setup(inp);
  bool finished = false;
  do {
    auto c = clustering->getClustering();
    auto r = clustering->getClustersResponses();
    ASSERT_EQ(c.size(), r.size());
    finished = clustering->iterate();
  } while (!finished);

  auto clusters = clustering->getClustering();

  bool label1 = false;
  bool label2 = false;
  for (auto& cluster : clusters) {
    std::vector<int> label1Vector;
    std::vector<int> label2Vector;
    for (auto& el : cluster) {
      if ((el < 15 && el >= 0) || (el >= 30 && el < 45)) {
        label1Vector.push_back(el);
      } else {
        label2Vector.push_back(el);
      }
    }
    if (label1Vector.empty() ^ label2Vector.empty()) {
      if (label1Vector.empty())
        label2 = true;
      else
        label1 = true;
    }
  }
  EXPECT_TRUE(label1 && label2);
}

TEST(PLSIC, CosineClusteringTest) {
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;

  auto plsclassifier = ssig::PLSClassifier::create();
  plsclassifier->setNumberOfFactors(2);

  auto oaaclassifier = ssig::OAAClassifier::create(*plsclassifier);

  std::vector<ssig::Cluster> discoverySubsets;
  discoverySubsets.resize(2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 30; ++j) {
      discoverySubsets[i].push_back(j + (30 * i));
    }
  }

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["discovery"] >> inp;
  stg.release();

  std::vector<ssig::Cluster> initialClustering =
      {{1}, {8}, {14}, {15}, {23}, {28}};
  std::vector<ssig::Cluster> natVector = {{}, {}};

  auto clustering = ssig::PLSImageClustering::create(
    *oaaclassifier,
    discoverySubsets,
    initialClustering);

  clustering->setK(2);
  clustering->setClusterRepresentationType(
    ssig::ClusterRepresentationType::ClustersResponses);
  clustering->setMergeThreshold(0.7f);

  auto cosine = std::unique_ptr<ssig::CosineSimilarity>(
    new ssig::CosineSimilarity);
  clustering->setSimBuilder(std::move(cosine));

  clustering->addNaturalWorld(neg, natVector);

  clustering->setDiscoveryConfiguration(discoverySubsets);
  clustering->setClusterSize(5);
  clustering->setMaxIterations(8);
  clustering->setClassifier(*oaaclassifier);


  clustering->setInitialClustering(initialClustering);
  clustering->setup(inp);
  bool finished = false;
  do {
    auto c = clustering->getClustering();
    auto r = clustering->getClustersResponses();
    ASSERT_EQ(c.size(), r.size());
    finished = clustering->iterate();
  } while (!finished);

  auto clusters = clustering->getClustering();

  bool label1 = false;
  bool label2 = false;
  for (auto& cluster : clusters) {
    std::vector<int> label1Vector;
    std::vector<int> label2Vector;
    for (auto& el : cluster) {
      if ((el < 15 && el >= 0) || (el >= 30 && el < 45)) {
        label1Vector.push_back(el);
      } else {
        label2Vector.push_back(el);
      }
    }
    if (label1Vector.empty() ^ label2Vector.empty()) {
      if (label1Vector.empty())
        label2 = true;
      else
        label1 = true;
    }
  }
  EXPECT_TRUE(label1 && label2);
}
