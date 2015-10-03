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

#include <algorithms/kmeans.hpp>

TEST(KmeansClustering, SanityClusteringTest){
  cv::Mat_<float> inp;
  inp = cv::Mat_<float>::zeros(6, 2);
  for(int i = 0; i < 3; ++i){
    inp[i][0] = static_cast<float>(rand() % 5);
    inp[i][1] = static_cast<float>(rand() % 5);
    inp[3 + i][0] = static_cast<float>(100 + rand() % 5);
    inp[3 + i][1] = static_cast<float>(100 + rand() % 5);
  }

  ssf::Kmeans kmeans;
  kmeans.setK(2);
  kmeans.setFlags(cv::KMEANS_RANDOM_CENTERS);
  kmeans.setMaxIterations(500);
  kmeans.setNAttempts(1);
  kmeans.learn(inp);
  auto clusters = kmeans.getClustering();
  std::vector<int> gt1 = {0, 1, 2};
  std::vector<int> gt2 = {3, 4, 5};
  ASSERT_EQ(2, static_cast<int>(clusters.size()));
  for(auto& cluster : clusters){
    if(cluster != gt1){
      EXPECT_EQ(cluster, gt2);
    } else{
      EXPECT_EQ(cluster, gt1);
    }
  }
}

TEST(KmeansClustering, Persistence){
  //TODO:

}
