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

#include "algorithms/kmeans.hpp"
#include "algorithms/plsClassifier.hpp"
#include "algorithms/plsImageClustering.hpp"

#include "algorithms/similarity_builder.hpp"


TEST(PLSIC, ClusteringTest){
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;
  int N = 60;
  ssf::PLSICParams params;
  auto classifierParam = new ssf::PLSParameters();
  classifierParam->factors = 2;

  params.K = 2;
  params.clusterRepresentationType = ssf::ClusterRepresentationType::ClustersResponses;
  params.mergeThreshold = 0.8f;
  ssf::CorrelationSimilarity sim;
  params.simBuilder = &sim;
  params.d1Len = N / 2;
  params.m = 5;
  params.maxIterations = 8;
  params.classifierParams = classifierParam;

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["discovery"] >> inp;
  stg["natural"] >> neg;
  stg.release();

  ssf::PLSImageClustering<ssf::PLSClassifier> clustering;
  cv::Mat_<float> kmeansInput = inp(cv::Rect(0, 0, inp.cols, 30));
  ssf::Kmeans kmeans;
  ssf::KmeansParams kmeansParams;
  kmeansParams.K = 7;
  kmeansParams.flags = cv::KMEANS_RANDOM_CENTERS;
  kmeansParams.nAttempts = 1;
  kmeansParams.predicitonDistanceType = cv::NORM_L2;
  kmeans.learn(kmeansInput, &kmeansParams);
  auto initialClustering = kmeans.getClustering();

  clustering.addInitialClustering(initialClustering);
  clustering.learn(inp, &params);

  auto clusters = clustering.getClustering();
  EXPECT_EQ(2, static_cast<int>(clusters.size()));

  bool label1 = false;
  bool label2 = false;
  for(auto& cluster : clusters){
    std::vector<int> label1Vector;
    std::vector<int> label2Vector;
    for(auto& el : cluster){
      if((el < 15 && el >= 0) || (el >= 30 && el < 45)){
        label1Vector.push_back(el);
      } else{
        label2Vector.push_back(el);
      }
    }
    if(label1Vector.empty() ^ label2Vector.empty()){
      if(label1Vector.empty())
        label2 = true;
      else
        label1 = true;
    }
  }


  EXPECT_TRUE(label1 && label2);
}

struct TestPlsic : ssf::PLSImageClustering<ssf::PLSClassifier>{
  void assignment(const int clusterSize,
                  const int nClusters,
                  const std::vector<int>& assignmentSet,
                  std::vector<std::vector<float>>& clusterResponses,
                  std::vector<int>& clusterIds,
                  std::vector<ssf::Cluster>& out) override{
    ssf::PLSImageClustering<ssf::PLSClassifier>::assignment(clusterSize,
                                                            nClusters,
                                                            assignmentSet,
                                                            clusterResponses,
                                                            clusterIds,
                                                            out);
  }

  void merge(std::vector<ssf::Cluster>& clusters) override{
    ssf::PLSImageClustering<ssf::PLSClassifier>::merge(clusters);
  }
};

TEST(PLSIC, AssignmentTest){
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;
  int N = 60;
  ssf::PLSICParams params;
  auto classifierParam = new ssf::PLSParameters();
  classifierParam->factors = 2;

  params.K = 2;
  params.clusterRepresentationType = ssf::ClusterRepresentationType::ClustersResponses;
  params.mergeThreshold = 0.8f;
  ssf::CorrelationSimilarity sim;
  params.simBuilder = &sim;
  params.d1Len = N / 2;
  params.m = 5;
  params.maxIterations = 8;
  params.classifierParams = classifierParam;

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  ASSERT_TRUE(stg.isOpened());
  stg["discovery"] >> inp;
  stg["natural"] >> neg;
  stg.release();

  TestPlsic plsic;
  cv::Mat_<float> kmeansInput = inp(cv::Rect(0, 0, inp.cols, 30));
  ssf::Kmeans kmeans;
  ssf::KmeansParams kmeansParams;
  kmeansParams.K = 7;
  kmeansParams.flags = cv::KMEANS_RANDOM_CENTERS;
  kmeansParams.nAttempts = 1;
  kmeansParams.predicitonDistanceType = cv::NORM_L2;
  kmeans.learn(kmeansInput, &kmeansParams);
  auto initialClustering = kmeans.getClustering();
  plsic.addInitialClustering(initialClustering);
  plsic.setup(inp, &params);

  const int nClusters = 5;

  std::vector<int> d1, ids;
  std::vector<std::vector<float>> responses;
  for(int i = 0; i < N / 2; ++i){
    d1.push_back(i);
  }
  for(auto& response : responses){
    response.assign(nClusters, 0);
  }
  for(int i = 0; i < nClusters; ++i){
    ids.push_back(i);
  }
  auto v = plsic.getClustering();
  std::vector<ssf::Cluster> clustering;
  plsic.assignment(5, static_cast<int>(v.size()), d1, responses, ids, clustering);
}
