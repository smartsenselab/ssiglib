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

void Kmeans::setup(cv::Mat_<float>& input, ClusteringParams* parameters){
  samples_ = input;
  params_ = std::unique_ptr<ClusteringParams>(parameters);
  auto p = static_cast<KmeansParams*>(parameters);//might throw an exception
  flags_ = p->flags;
  nAttempts_ = p->nAttempts;
  predicitonDistanceType_ = p->predicitonDistanceType;

}

std::vector<Cluster> Kmeans::learn(cv::Mat_<float>& input, ClusteringParams* parameters){
  setup(input, parameters);
  cv::Mat_<int> labels;
  cv::TermCriteria term;
  term.maxCount = params_->maxIterations;
  term.type = term.MAX_ITER;

  cv::kmeans(samples_, params_->K, labels, term, nAttempts_, flags_, centroids_);

  std::unordered_map<int, Cluster> clusters;
  for(int i = 0; i < labels.rows; ++i){
    clusters[labels[i][0]].push_back(i);
  }
  clusters_.assign(clusters.begin(), clusters.end());

  return clusters_;
}

cv::Mat_<float> Kmeans::predict(cv::Mat_<float>& sample){
  const int n = centroids_.rows;
  cv::Mat_<float> prediction = cv::Mat_<float>::zeros(1, n);
  for(int i = 0; i < n; ++i){
    prediction[0][i] = cv::norm(sample - centroids_.row(i), predicitonDistanceType_);
  }
  return prediction;
}

std::vector<Cluster> Kmeans::getResults(){
  return clusters_;
}

cv::Mat_<float> Kmeans::getCentroids(){
  return centroids_;
}

cv::Mat_<float> Kmeans::getState(){
  return samples_;
}

void Kmeans::load(const std::string& filename, const std::string& nodename){
  cv::FileStorage stg;
  stg.open(filename, cv::FileStorage::READ);

  stg["Kmeans" + nodename] >> centroids_;

  stg.release();
}

void Kmeans::save(const std::string& filename, const std::string& nodename){
  cv::FileStorage stg;
  stg.open(filename, cv::FileStorage::WRITE);
  stg << "Kmeans" + nodename << "{";

  stg << "Centroids" << centroids_;

  stg << "}";
  stg.release();
}

void Kmeans::clear(){
  centroids_.release();
  samples_.release();
  clusters_.clear();
}
}
