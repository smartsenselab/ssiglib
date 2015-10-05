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
#include <unordered_map>
#include "algorithms/kmeans.hpp"


namespace ssf{

Kmeans::Kmeans(const Kmeans& rhs){
  //Constructor Copy
}

Kmeans& Kmeans::operator=(const Kmeans& rhs){
  if(this != &rhs){
    //code here
  }
  return *this;
}

void Kmeans::learn(cv::Mat_<float>& input){
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
  for(int i = 0; i < labels.rows; ++i){
    clusters[labels.at<int>(i, 0)].push_back(i);
  }
  for(int i = 0; i < static_cast<int>(clusters.size()); ++i){
    auto cluster = clusters[i];
    mClusters.push_back(cluster);
  }
}

void Kmeans::predict(cv::Mat_<float>& sample, cv::Mat_<float>& resp)const{
  const int n = mCentroids.rows;
  resp = cv::Mat_<float>::zeros(1, n);
  for(int i = 0; i < n; ++i){
    resp[0][i] = static_cast<float>(
      cv::norm(sample - mCentroids.row(i), mPredictionDistanceType));
  }
}

std::vector<Cluster> Kmeans::getClustering() const{
  return mClusters;
}

void Kmeans::getCentroids(cv::Mat_<float>& centroidsMatrix) const{
  centroidsMatrix = mCentroids.clone();
}

bool Kmeans::empty() const{
  return mCentroids.empty();
}

bool Kmeans::isTrained() const{
  return !mCentroids.empty();
}

bool Kmeans::isClassifier() const{
  return false;
}

void Kmeans::setup(cv::Mat_<float>& input){
  mSamples = input;
}

void Kmeans::load(const std::string& filename, const std::string& nodename){
  cv::FileStorage stg;
  stg.open(filename, cv::FileStorage::READ);
  auto node = stg[nodename];
  read(node);
  stg.release();
}

void Kmeans::save(const std::string& filename, const std::string& nodename)const{
  cv::FileStorage stg;
  stg.open(filename, cv::FileStorage::WRITE);
  stg << nodename << "{";

  write(stg);

  stg << "}";
  stg.release();
}

void Kmeans::read(const cv::FileNode& fn){
  fn["Centroids"] >> mCentroids;
}

void Kmeans::write(cv::FileStorage& fs) const{
  fs << "Centroids" << mCentroids;
}

int Kmeans::getFlags() const{
  return mFlags;
}

void Kmeans::setFlags(int flags){
  mFlags = flags;
}

int Kmeans::getNAttempts() const{
  return mNumberOfAttempts;
}

void Kmeans::setNAttempts(int nAttempts){
  mNumberOfAttempts = nAttempts;
}

int Kmeans::getPredicitonDistanceType() const{
  return mPredictionDistanceType;
}

void Kmeans::setPredicitonDistanceType(cv::NormTypes predicitonDistanceType){
  mPredictionDistanceType = predicitonDistanceType;
}

void Kmeans::setupLabelMatFromInitialization(cv::Mat& labels){
  if(mClusters.empty()) return;
  labels = cv::Mat_<int>::zeros(mSamples.rows, mSamples.cols);
  for(int c = 0; c < static_cast<int>(mClusters.size()); ++c){
    for(int s = 0; s < static_cast<int>(mClusters[c].size()); ++s){
      labels.at<int>(mClusters[c][s], 0) = c;
    }
  }
}
}
