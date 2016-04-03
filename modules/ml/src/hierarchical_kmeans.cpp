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

#include "ml/hierarchical_kmeans.hpp"

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>

namespace ssig {
HierarchicalKmeans::HierarchicalKmeans(): mDistType(L2) {
  // Constructor
}

HierarchicalKmeans::~HierarchicalKmeans() {
  // Destructor
}

HierarchicalKmeans::HierarchicalKmeans(const HierarchicalKmeans& rhs)
  : mDistType(L2) {
  // Constructor Copy
}

HierarchicalKmeans&
HierarchicalKmeans::operator=(const HierarchicalKmeans& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void HierarchicalKmeans::setup(const cv::Mat_<float>& input) { }

void HierarchicalKmeans::learn(const cv::Mat_<float>& input) {
  mSamples = input.clone();
  cv::Mat features = input;
  cv::Mat_<float> centers(getK(), features.cols, CV_32F);

  cvflann::KMeansIndexParams kMeansIndexParams(
    getBranchingFactor(),
    getMaxIterations(),
    getInitialization(),
    getCBIndex());

  int k;
  switch (getDistance()) {
  case L2: {
    cvflann::L2<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case L1: {
    cvflann::L1<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case MinkowskiDistance: {
    cvflann::MinkowskiDistance<float> distType(getMinkowskiParameter());
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case MaxDistance: {
    cvflann::MaxDistance<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case HistIntersectionDistance: {
    cvflann::HistIntersectionDistance<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case HellingerDistance: {
    cvflann::HellingerDistance<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case ChiSquareDistance: {
    cvflann::ChiSquareDistance<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  case KL_Divergence: {
    cvflann::KL_Divergence<float> distType;
    k = cv::flann::hierarchicalClustering(
      features,
      centers,
      kMeansIndexParams,
      distType);
  }
    break;
  default: {}
    break;
  }
  mCenters = centers;
}

void HierarchicalKmeans::predict(const cv::Mat_<float>& inp,
  cv::Mat_<float>& resp) const {
  // TODO(Ricardo): implement this
}

std::vector<Cluster> HierarchicalKmeans::getClustering() const {
  std::vector<Cluster> ans(mCenters.rows);
  const int nCenters = mCenters.rows;
  for (int r = 0; r < mSamples.rows; ++r) {
    int chosenCenter = -1;
    float minDist = FLT_MAX;
    cv::Mat query = mSamples.row(r);
    for (int rc = 0; rc < nCenters; ++rc) {
      cv::Mat sample = mCenters.row(rc);
      float dist = cv::norm(sample - query);
      if (dist < minDist) {
        minDist = dist;
        chosenCenter = rc;
      }
    }
    ans[chosenCenter].push_back(r);
  }

  return ans;
}

void HierarchicalKmeans::getCentroids(cv::Mat_<float>& centroidsMatrix) const {
  centroidsMatrix = mCenters.clone();
}

bool HierarchicalKmeans::empty() const {
  return mCenters.empty();
}

bool HierarchicalKmeans::isTrained() const {
  return !mCenters.empty();
}

bool HierarchicalKmeans::isClassifier() const {
  return false;
}

void HierarchicalKmeans::read(const cv::FileNode& fn) {}

void HierarchicalKmeans::write(cv::FileStorage& fs) const {}

void HierarchicalKmeans::setDistance(
  const ClusteringDistance& distType,
  const int minkowski) {
  mDistType = distType;
  mMinkowski = minkowski;
}

ClusteringDistance HierarchicalKmeans::getDistance() const {
  return mDistType;
}

int HierarchicalKmeans::getMinkowskiParameter() const {
  return mMinkowski;
}

void HierarchicalKmeans::setInitialization(
  const cvflann::flann_centers_init_t& initType) {
  mInitType = initType;
}

cvflann::flann_centers_init_t HierarchicalKmeans::getInitialization() const {
  return mInitType;
}

void HierarchicalKmeans::setBranchingFactor(const int branchingFactor) {
  mBranchingFactor = branchingFactor;
}

int HierarchicalKmeans::getBranchingFactor() const {
  return mBranchingFactor;
}

void HierarchicalKmeans::setCBIndex(const float cbIndex) {
  mCBIndex = cbIndex;
}

float HierarchicalKmeans::getCBIndex() const {
  return mCBIndex;
}
}  // namespace ssig


