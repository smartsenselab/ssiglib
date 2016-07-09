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


#include "ssiglib/ml/kmeans.hpp"

#include <unordered_map>
#include <vector>
#include <string>

namespace ssig {

cv::Ptr<Kmeans> Kmeans::create() {
  return cv::Ptr<Kmeans>(new Kmeans());
}

Kmeans::Kmeans(const Kmeans& rhs) :
  mFlags(rhs.mFlags),
  mNumberOfAttempts(rhs.mNumberOfAttempts) {
  this->setPredictionDistanceType(
                                  static_cast<ssig::Clustering::PredictionType>
                                  (rhs.getPredictionDistanceType()));
  // Constructor Copy
}

Kmeans& Kmeans::operator=(const Kmeans& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void Kmeans::learn(
  const cv::Mat_<float>& input) {
  mCentroids.release();
  mSamples.release();
  mClusters.clear();

  setup(input);
  cv::Mat labels;
  setupLabelMatFromInitialization(labels);
  cv::TermCriteria term;
  term.maxCount = mMaxIterations;
  term.type = term.MAX_ITER;

  cv::Mat centroids = mCentroids;
  cv::kmeans(mSamples, mK, labels, term, mNumberOfAttempts,
             mFlags, mCentroids);

  std::unordered_map<int, Cluster> clusters;
  for (int i = 0; i < labels.rows; ++i) {
    clusters[labels.at<int>(i, 0)].push_back(i);
  }
  for (int i = 0; i < static_cast<int>(clusters.size()); ++i) {
    auto cluster = clusters[i];
    mClusters.push_back(cluster);
  }
}

void Kmeans::predict(
  const cv::Mat_<float>& sample,
  cv::Mat_<float>& resp) const {
  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) {
    if (!mPredictionClassifier)
      std::runtime_error("Please Set the Classifier before hand!");
    cv::Ptr<ssig::Classifier> classifier =
        cv::Ptr<ssig::Classifier>(mPredictionClassifier->clone());
    ssig::Clustering::predict(
                              mSamples,
                              sample,
                              mClusters,
                              classifier,
                              resp);
  } else {
    ssig::Clustering::predict(
                              sample,
                              mCentroids,
                              mPredictionDistanceType,
                              resp);
  }
}

std::vector<Cluster> Kmeans::getClustering() const {
  return mClusters;
}

void Kmeans::getCentroids(cv::Mat_<float>& centroidsMatrix) const {
  centroidsMatrix = mCentroids.clone();
}

bool Kmeans::empty() const {
  return mCentroids.empty();
}

bool Kmeans::isTrained() const {
  return !mCentroids.empty();
}

bool Kmeans::isClassifier() const {
  return false;
}

void Kmeans::setup(const cv::Mat_<float>& input) {
  mSamples = input;
}

void Kmeans::read(const cv::FileNode& fn) {
  int pdist;
  fn["PredictionType"] >> pdist;
  mPredictionDistanceType = static_cast<ssig::Clustering::PredictionType>(
    pdist);
  fn["Centroids"] >> mCentroids;
  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) {
    if (mPredictionClassifier == nullptr) {
      std::runtime_error("Classifier not set for this prediction type");
    }
    mPredictionClassifier->read(fn);
  }
}

void Kmeans::write(cv::FileStorage& fs) const {
  fs << "PredictionType" << mPredictionDistanceType;
  fs << "Centroids" << mCentroids;
  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) {
    cv::Mat_<float> inp;
    cv::Mat_<int> labels;
    int label = 0;
    for (const auto& cluster : mClusters) {
      for (const auto& clusterElement : cluster) {
        inp.push_back(mSamples.row(clusterElement));
        labels.push_back(label);
      }
      ++label;
    }
    mPredictionClassifier->learn(inp, labels);

    mPredictionClassifier->write(fs);
  }
}

int Kmeans::getFlags() const {
  return mFlags;
}

void Kmeans::setFlags(int flags) {
  mFlags = flags;
}

int Kmeans::getNAttempts() const {
  return mNumberOfAttempts;
}

void Kmeans::setNAttempts(int nAttempts) {
  mNumberOfAttempts = nAttempts;
}

size_t Kmeans::getSize() const {
  int ans = 0;
  if (mCentroids.empty())
    ans = ~static_cast<int>(mClusters.size());
  else
    ans = mCentroids.rows;
  return ans;
}

void Kmeans::setupLabelMatFromInitialization(cv::Mat& labels) {
  if (mClusters.empty())
    return;
  labels = cv::Mat_<int>::zeros(mSamples.rows, mSamples.cols);
  for (int c = 0; c < static_cast<int>(mClusters.size()); ++c) {
    for (int s = 0; s < static_cast<int>(mClusters[c].size()); ++s) {
      labels.at<int>(mClusters[c][s], 0) = c;
    }
  }
}

} // namespace ssig
