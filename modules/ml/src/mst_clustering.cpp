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
#define L2Dist(sampleA, sampleB) static_cast<float>(\
                                  cv::norm((sampleA) - (sampleB)))

#include "ssiglib/ml/mst_clustering.hpp"

#include <vector>
#include <stack>
#include <numeric>
#include <algorithm>
#include <utility>
#include <ctime>

namespace ssig {
static void computeMST(
  const cv::Mat_<float>& samples,
  std::vector<std::pair<int, int>>& edges);

void MSTreeClustering::setup(const cv::Mat_<float>& input) {}

void MSTreeClustering::learn(const cv::Mat_<float>& input) {
  mSamples = input;
  // cv::Mat_<float> adjMat;
  std::vector<std::pair<int, int>> edges;
  // computeAdjacencyMatrix(mSamples, adjMat);
  computeMST(input, edges);

  std::sort(edges.begin(), edges.end(),
            [&input](const std::pair<int, int>& a,
              const std::pair<int, int>& b) {
              float weightA = L2Dist(input.row(a.first),
                    input.row(a.second)),
                  weightB = L2Dist(input.row(b.first),
                    input.row(b.second));
              return weightA > weightB;
            });
  edges.erase(edges.begin(), edges.begin() + (mK - 1));

  // find the components after pruning
  std::vector<std::vector<int>> children(mSamples.rows);
  for (const auto& edge : edges) {
    const int &i = edge.first,
        &j = edge.second;
    children[i].push_back(j);
    children[j].push_back(i);
  }

  mClusters.resize(getK());
  int clusterId = 0;
  // dfs for finding components
  std::vector<bool> visited(mSamples.rows, false);
  for (int r = 0; r < mSamples.rows; ++r) {
    if (visited[r])
      continue;
    std::stack<int> stack;
    stack.push(r);
    while (!stack.empty()) {
      auto element = stack.top();
      visited[element] = true;
      stack.pop();
      mClusters[clusterId].push_back(element);
      for (const auto& child : children[element]) {
        if (!visited[child]) {
          stack.push(child);
        }
      }
    }
    ++clusterId;
  }
}

void MSTreeClustering::predict(
  const cv::Mat_<float>& inp,
  cv::Mat_<float>& resp) const {
  cv::Mat_<float> centroids;
  getCentroids(centroids);
  ssig::Clustering::predict(
                            inp,
                            centroids,
                            ssig::Clustering::NORM_L2,
                            resp);
}

std::vector<Cluster> MSTreeClustering::getClustering() const {
  return mClusters;
}

void MSTreeClustering::getCentroids(cv::Mat_<float>& centroidsMatrix) const {
  int nrows = static_cast<int>(mClusters.size());
  centroidsMatrix = cv::Mat_<float>::zeros(nrows,
                                           mSamples.cols);
  for (int i = 0; i < nrows; ++i) {
    const auto& cluster = mClusters[i];
    for (const auto& id : cluster) {
      centroidsMatrix.row(i) += mSamples.row(id);
    }
    centroidsMatrix.row(i) /= static_cast<float>(cluster.size());
  }
}

bool MSTreeClustering::empty() const {
  return mClusters.empty();
}

bool MSTreeClustering::isTrained() const {
  return !mClusters.empty();;
}

bool MSTreeClustering::isClassifier() const {
  return false;
}

void MSTreeClustering::read(const cv::FileNode& fn) {
  // TODO(Ricardo): Not implemented
}

void MSTreeClustering::write(cv::FileStorage& fs) const {
  // TODO(Ricardo): Not implemented
}


void MSTreeClustering::computeMinimumSpanningTree(
  const cv::Mat_<float>& input,
  std::vector<std::pair<int, int>>& edges) {
  // Simple Prim since the graph is dense
  const int nrows = input.rows;
  std::srand(static_cast<unsigned int>(time(nullptr)));
  int u = std::rand() % nrows;
  int solLen = 0;
  std::vector<bool> inSolution(nrows);
  std::vector<float> weights(nrows, FLT_MAX);
  std::vector<int> predecessors(nrows, -1);

  weights[u] = 0;

  while (solLen < nrows) {
    float minWeight = FLT_MAX;
    int pos = 0;;
    for (int n = 0; n < nrows; ++n) {
      const auto& weight = weights[n];
      if (!inSolution[n] && weight < minWeight) {
        minWeight = weight;
        pos = n;
      }
    }
    ++solLen;
    inSolution[pos] = true;

    for (int j = 0; j < nrows; ++j) {
      if (!inSolution[j] && input[pos][j] < weights[j]) {
        weights[j] = input[pos][j];
        predecessors[j] = pos;
      }
    }
  }

  // From here onwards it is just making sure the answers are always ordered
  edges.reserve(nrows - 1);
  for (int i = 0; i < nrows; ++i) {
    int j = predecessors[i];
    if (j < 0)
      continue;
    edges.push_back(std::make_pair(i, j));
  }
}

void MSTreeClustering::computeMinimumSpanningTree(
  const cv::Mat_<float>& input,
  std::vector<std::forward_list<std::pair<int, float>>>& adjList) {
  std::vector<std::pair<int, int>> edges;
  computeMinimumSpanningTree(input, edges);

  edges.reserve(edges.size() * 2);
  const int len = static_cast<int>(edges.size());
  for (int i = 0; i < len; ++i) {
    const auto& edge = edges[i];
    edges.push_back(std::make_pair(edge.second, edge.first));
  }
  std::sort(edges.begin(), edges.end(),
            [](const std::pair<int, int>& a,
              const std::pair<int, int>& b) -> bool {
              return a.second > b.second;
            });

  adjList.resize(input.rows);
  for (const auto& edge : edges) {
    int i = edge.first,
        j = edge.second;
    adjList[i].push_front(std::make_pair(j, input[i][j]));
  }
}

void MSTreeClustering::computeAdjacencyMatrix(
  const cv::Mat_<float>& input,
  cv::Mat_<float>& adjMatrix) {
  const int nrows = input.rows;
  adjMatrix = cv::Mat_<float>::zeros(nrows, nrows);
  adjMatrix = FLT_MAX;

#ifdef _OPENMP
  #pragma omp parallel for
#endif
  for (int i = 0; i < nrows; ++i) {
    cv::Mat_<float> sampleA = input.row(i);
    for (int j = i + 1; j < nrows; ++j) {
      cv::Mat_<float> sampleB = input.row(j);
      float weight = static_cast<float>(cv::norm(sampleA - sampleB));
      adjMatrix[i][j] = weight;
      adjMatrix[j][i] = weight;
    }
  }
}

void computeMST(
  const cv::Mat_<float>& samples,
  std::vector<std::pair<int, int>>& edges) {
  // Simple Prim since the graph is dense
  const int nrows = samples.rows;
  std::srand(static_cast<unsigned int>(time(nullptr)));
  int u = std::rand() % nrows;
  int solLen = 0;
  std::vector<bool> inSolution(nrows);
  std::vector<float> weights(nrows, FLT_MAX);
  std::vector<int> predecessors(nrows, -1);

  weights[u] = 0;

  while (solLen < nrows) {
    float minWeight = FLT_MAX;
    int pos = 0;;
    for (int n = 0; n < nrows; ++n) {
      const auto& weight = weights[n];
      if (!inSolution[n] && weight < minWeight) {
        minWeight = weight;
        pos = n;
      }
    }
    ++solLen;
    inSolution[pos] = true;

    for (int j = 0; j < nrows; ++j) {
      float dist = L2Dist(samples.row(pos), samples.row(j));
      if (!inSolution[j] && dist < weights[j]) {
        weights[j] = dist;
        predecessors[j] = pos;
      }
    }
  }

  // From here onwards it is just making sure the answers are always ordered
  edges.reserve(nrows - 1);
  for (int i = 0; i < nrows; ++i) {
    int j = predecessors[i];
    if (j < 0)
      continue;
    edges.push_back(std::make_pair(i, j));
  }
}

}  // namespace ssig
