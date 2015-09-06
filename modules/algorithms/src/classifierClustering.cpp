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
#include <cassert>
#include "core/log.hpp"

#include "algorithms/classifierClustering.hpp"

namespace ssf{

ClassifierClustering::ClassifierClustering(const ClassifierClustering& rhs){
  //Constructor Copy
}

ClassifierClustering& ClassifierClustering::operator=(const ClassifierClustering& rhs){
  if(this != &rhs){
    //code here
  }
  return *this;
}

std::vector<Cluster> ClassifierClustering::getClustering() const{
  return newClusters_;
}

void ClassifierClustering::setup(cv::Mat_<float>& input,
                                 ClusteringParams* parameters){
  if(clusters_.empty()){
    ssf::Log::ERROR("Call ssf::addInitialClustering First!");
  }
  assert(!clusters_.empty());
  samples_ = input;
  params_ = std::unique_ptr<ClusteringParams>(parameters);
  auto p = static_cast<ClassifierClusteringParams*>(parameters);
  m_ = p->m;
  maximumK_ = p->maximumK;
  minimumK_ = p->minimumK;

  precondition();

  discovery_.resize(2);//Discoveries subsets are inferred from the input samples
  natural_.resize(2);
  const int N = samples_.rows;
  int half = static_cast<int>(ceil(N / 2));
  for(int i = 0; i < half; ++i){
    discovery_[0].push_back(i);
  }
  for(int i = half; i < N; ++i){
    discovery_[1].push_back(i);
  }

  params_->K = std::min(static_cast<int>(half / 4), maximumK_);

  initializeClassifiers();
  trainClassifiers(clusters_, discovery_[0], natural_[0]);

  newClusters_ = assignment(m_, discovery_[0]);
  clustersOld_ = clusters_;

  ready_ = true;
}

bool ClassifierClustering::iterate(){
  if(!ready_){
    ssf::Log::ERROR("Setup method must be called First!");
  }
  int order = it_ % 2;
  clusters_ = newClusters_;
  trainClassifiers(clusters_, discovery_[order], natural_[order]);
  newClusters_.clear();
  order = (order + 1) % 2;
  newClusters_ = assignment(m_, discovery_[order]);
  clustersOld_ = clusters_;
  it_++;

  return isFinished();
}

void ClassifierClustering::learn(
  cv::Mat_<float>& input, ClusteringParams* parameters){
  setup(input, parameters);
  /********
  **main loop
  ********/
  it_ = 0;
  bool terminated = false;
  do{
    terminated = iterate();
  } while(!terminated);
  int order = it_ % 2;
  clusters_ = newClusters_;
  trainClassifiers(clusters_, discovery_[order], natural_[order]);
  postCondition();
}
}
