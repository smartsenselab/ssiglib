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


#include <ml/classifier_clustering.hpp>

#include <algorithm>
#include <vector>

namespace ssig {

std::vector<Cluster> ClassifierClustering::getClustering() const {
  return mNewClusters;
}

ClassifierClustering::~ClassifierClustering() {}

void ClassifierClustering::setup(cv::Mat_<float>& input) {
  Clustering::setup(input);
  precondition();

  const int N = mSamples.rows;
  const int k = static_cast<int>(N / 8);

  mInitialK = std::min(static_cast<int>(k), mMaximumK);

  initializeClusterings(mDiscovery[0]);
  initializeClassifiers();
  trainClassifiers(mSamples, mClusters, mNatural[0]);

  assignment(mSamples, mMValue, static_cast<int>(mClusters.size()),
             mDiscovery[1], mClustersResponses, mClustersIds, mNewClusters);
  trainClassifiers(mSamples, mClusters, mNatural[1]);

  mClustersOld = mClusters;

  mReady = true;
  mIt = 0;
}

bool ClassifierClustering::iterate() {
  if (!mReady) {
    // ssig::Log::ERROR("Setup method must be called First!");
    // TODO(Ricardo) Throws an exception
  }
  int order = mIt % 2;
  mClusters = mNewClusters;
  mNewClusters.clear();

  assignment(mSamples, mMValue, static_cast<int>(mClusters.size()),
             mDiscovery[order], mClustersResponses, mClustersIds, mNewClusters);
  trainClassifiers(mSamples, mNewClusters, mNatural[order]);

  mClustersOld = mClusters;

  mIt++;

  auto termination = isFinished();
  if (termination) {
    mClusters = mNewClusters;
  }
  return termination;
}

void ClassifierClustering::addNaturalWorld(
    cv::Mat_<float>& natSamples, std::vector<std::vector<int>>& distribution) {
  mNatural = distribution;
  mNaturalSamples = natSamples;
}

int ClassifierClustering::getInitialK() const { return mInitialK; }

void ClassifierClustering::setInitialK(int mInitialK1) {
  mInitialK = mInitialK1;
}

int ClassifierClustering::getMValue() const { return mMValue; }

void ClassifierClustering::setMValue(int m) { mMValue = m; }

std::vector<std::vector<int>> ClassifierClustering::getDiscovery() const {
  return mDiscovery;
}

void ClassifierClustering::setDiscoveryConfiguration(
    const std::vector<std::vector<int>>& discovery) {
  mDiscovery = discovery;
}

void ClassifierClustering::precondition() {
  if (mSamples.rows <= 0) {
    throw std::length_error("argument not set");
  }

  if (mDiscovery.size() <= 0) throw std::length_error("Argument not Set");
}

void ClassifierClustering::learn(cv::Mat_<float>& input) {
  setup(input);
  /********
    **main loop
    ********/
  mIt = 0;
  bool terminated = false;
  do {
    terminated = iterate();
  } while (!terminated);

  postCondition();
}

std::vector<std::vector<float>> ClassifierClustering::getClustersResponses()
    const {
  return mClustersResponses;
}

}  // namespace ssig
