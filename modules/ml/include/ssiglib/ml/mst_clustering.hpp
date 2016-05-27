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

#ifndef _SSIG_ML_MST_CLUSTERING_HPP_
#define _SSIG_ML_MST_CLUSTERING_HPP_

#include <forward_list>
#include <utility>
#include <vector>

#include "clustering.hpp"

namespace ssig {
class MSTreeClustering : Clustering {
 public:
  MSTreeClustering(void) = default;
  virtual ~MSTreeClustering(void) = default;

  void setup(const cv::Mat_<float>& input) override;
  void learn(const cv::Mat_<float>& input) override;
  void predict(const cv::Mat_<float>& inp,
               cv::Mat_<float>& resp) const override;
  std::vector<Cluster> getClustering() const override;
  void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;
  bool empty() const override;
  bool isTrained() const override;
  bool isClassifier() const override;
  void read(const cv::FileNode& fn) override;
  void write(cv::FileStorage& fs) const override;

  /**
  @brief Uses the Prim algorithm to compute a minimum spanning tree over
  a graph represented by the adjacency matrix input (see computeAdjacencyMatrix)
  */
  ML_EXPORT static void computeMinimumSpanningTree(
    const cv::Mat_<float>& input,
    std::vector<std::forward_list<std::pair<int, float>>>& adjList);
  ML_EXPORT static void computeMinimumSpanningTree(
    const cv::Mat_<float>& input,
    std::vector<std::pair<int, int>>& edges);

 private:
  /**
  @brief Given a set of samples it computes a graph represented by an adjacency matrix
  where the edge represents the euclidean distance from point 'i' to 'j'
  */
  ML_EXPORT static void computeAdjacencyMatrix(const cv::Mat_<float>& input,
                                               cv::Mat_<float>& adjMatrix);

  // private members
};
}  // namespace ssig
#endif  // !_SSIG_ML_MST_CLUSTERING_HPP_
