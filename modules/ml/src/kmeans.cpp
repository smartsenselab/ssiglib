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


#include "ml/kmeans.hpp"

#include <unordered_map>
#include <vector>
#include <string>

namespace ssig {

Kmeans::Kmeans(const Kmeans& rhs): mFlags(rhs.mFlags),
                                   mNumberOfAttempts(rhs.mNumberOfAttempts),
                                   mPredictionDistanceType(
                                     rhs.mPredictionDistanceType) {
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
  cv::kmeans(mSamples, mK, labels, term, mNumberOfAttempts, mFlags, mCentroids);

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
  cv::Mat_<float>& resp) {
  const int n = mCentroids.rows;

  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) {
    if (mPredictionClassifier)
      std::runtime_error("Please Set the Classifier before hand!");

    for (int c = 0; c < mClusters.size(); ++c) {
      cv::Mat_<int> labels(mSamples.rows, 1, -1);
      for (const auto& id : mClusters[c]) {
        labels.at<int>(id) = c;
      }
      mPredictionClassifier->learn(mSamples, labels);
    }
  }

  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) {
    mPredictionClassifier->predict(sample, resp);
  } else {
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < n; ++i) {
      resp = cv::Mat_<float>::zeros(1, n);
      resp[0][i] = -1 * static_cast<float>(cv::norm(sample - mCentroids.row(i),
                                                    mPredictionDistanceType));
    }
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
  fn["PredictionType"] >> mPredictionDistanceType;
  fn["Centroids"] >> mCentroids;
  if (mPredictionDistanceType == CLASSIFIER_PREDICTION) { }
}

void Kmeans::write(cv::FileStorage& fs) const {
  if (mPredictionDistanceType != CLASSIFIER_PREDICTION) {
    fs << "PredictionType" << mPredictionDistanceType;
    fs << "Centroids" << mCentroids;
  } else { }
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

int Kmeans::getPredictionDistanceType() const {
  return mPredictionDistanceType;
}

void Kmeans::setPredictionDistanceType(
  ssig::Kmeans::PredictionType predicitonDistanceType) {
  mPredictionDistanceType = predicitonDistanceType;
}

void Kmeans::setPredictionDistanceType(
  std::unique_ptr<ssig::Classifier> predictionClassifier) {
  mPredictionDistanceType = CLASSIFIER_PREDICTION;
  mPredictionClassifier = std::unique_ptr<ssig::OAAClassifier>
    (new ssig::OAAClassifier(*predictionClassifier));
}

void Kmeans::setupLabelMatFromInitialization(cv::Mat& labels) {
  if (mClusters.empty()) return;
  labels = cv::Mat_<int>::zeros(mSamples.rows, mSamples.cols);
  for (int c = 0; c < static_cast<int>(mClusters.size()); ++c) {
    for (int s = 0; s < static_cast<int>(mClusters[c].size()); ++s) {
      labels.at<int>(mClusters[c][s], 0) = c;
    }
  }
}

}  // namespace ssig


