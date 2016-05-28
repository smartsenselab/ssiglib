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
#include <vector>

#include "ssiglib/ml/clustering.hpp"
#include "ssiglib/ml/classification.hpp"

namespace ssig {

void Clustering::setup(const cv::Mat_<float>& input) {
  mReady = true;
  mSamples = input;
}

size_t Clustering::getSize() const {
  return mClusters.size();
}

void Clustering::setInitialClustering(const std::vector<Cluster>& init) {
  mClusters = init;
}

void Clustering::setPredictionDistanceType(
  ssig::Clustering::PredictionType predictionDistanceType) {
  mPredictionDistanceType = predictionDistanceType;
}

void Clustering::setPredictionDistanceType(
  Classifier& predictionClassifier) {
  mPredictionDistanceType = CLASSIFIER_PREDICTION;
  mPredictionClassifier = cv::Ptr<ssig::OAAClassifier>
      (new ssig::OAAClassifier(predictionClassifier));
}

int Clustering::getPredictionDistanceType() const {
  return mPredictionDistanceType;
}

void Clustering::predict(
  const cv::Mat_<float>& sample,
  const cv::Mat_<float>& centroids,
  const ssig::Clustering::PredictionType normtype,
  cv::Mat_<float>& resp) {
  const int n = centroids.rows;

  resp = cv::Mat_<float>::zeros(1, n);
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < n; ++i) {
    auto cvNorm = static_cast<cv::NormTypes>(normtype);
    resp[0][i] = -1 * static_cast<float>(
      cv::norm(sample - centroids.row(i), cvNorm));
  }
}

void Clustering::predict(
  const cv::Mat_<float>& samples,
  const cv::Mat_<float>& probes,
  const std::vector<ssig::Cluster>& clusters,
  cv::Ptr<ssig::Classifier>& classifier,
  cv::Mat_<float>& resp) {
  if (!classifier)
    std::runtime_error("Please Set the Classifier before hand!");
  for (int c = 0; c < static_cast<int>(clusters.size()); ++c) {
    cv::Mat_<int> labels(samples.rows, 1, -1);
    for (const auto& id : clusters[c]) {
      labels.at<int>(id) = c;
    }
    classifier->learn(samples, labels);
  }
  classifier->predict(probes, resp);
}
}  // namespace ssig
