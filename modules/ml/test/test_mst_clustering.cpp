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
#include "ssiglib/ml/mst_clustering.hpp"

TEST(MSTreeClustering, computeMinimumSpanningTree_Contract) {
  const float inf = FLT_MAX;
  cv::Mat_<float> input = (cv::Mat_<float>(7, 7) <<
          inf , 7 , inf , 5 , inf , inf , inf ,
          7 , inf , 8 , 9 , 7 , inf , inf ,
          inf , 8 , inf , inf , 5 , inf , inf ,
          5 , 9 , inf , inf , 15 , 6 , inf ,
          inf , 7 , 5 , 15 , inf , 8 , 9 ,
          inf , inf , inf , 6 , 8 , inf , 11 ,
          inf , inf , inf , inf , 9 , 11 , inf);
  typedef std::vector<std::forward_list<std::pair<int, float>>> AdjList;
  AdjList adjList;
  AdjList expected{
    {{1, 7.f}, {3, 5.f}},
    {{0, 7.f}, {4, 7.f}},
    {{4, 5.f}},
    {{0, 5.f}, {5, 6.f}},
    {{1, 7.f}, {2, 5.f}, {6, 9.f}},
    {{3, 6.f}},
    {{4, 9.f}}};
  ssig::MSTreeClustering::computeMinimumSpanningTree(input, adjList);

  EXPECT_EQ(expected, adjList);
}
