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
#include <algorithms/classifierClustering.hpp>

namespace ssf{

std::vector<Cluster> ClassifierClustering::
getClustering() const{
  return newClusters_;
}

ClassifierClustering::
~ClassifierClustering(){
  delete classificationParams_;
}

void ClassifierClustering::
setup(cv::Mat_<float>& input,
      ClusteringParams* parameters){
  ClusteringMethod::setup(input, parameters);
  auto p = static_cast<ClassifierClusteringParams*>(parameters);
  m_ = p->m;
  int d1Len = p->d1Len;
  mMaximumK = p->maximumK;
  classificationParams_ = p->classifierParams;

  precondition();

  discovery_.resize(2);//Discoveries subsets are inferred from the input samples
  natural_.resize(2);
  const int N = samples_.rows;
  for(int i = 0; i < d1Len; ++i){
    discovery_[0].push_back(i);
  }
  for(int i = d1Len; i < N; ++i){
    discovery_[1].push_back(i);
  }

  if(mNaturalSamples.rows > 0){
    int len = mNaturalSamples.rows;
    int halfLen = len / 2;
    for(int i = 0; i < halfLen; ++i){
      natural_[0].push_back(i);
    }
    for(int i = halfLen; i < len; ++i){
      natural_[1].push_back(i);
    }
  }

  mInitialK = std::min(static_cast<int>(d1Len / 4), mMaximumK);

  initializeClusterings(discovery_[0]);
  initializeClassifiers();
  trainClassifiers(clusters_, natural_[0]);

  assignment(m_,
             static_cast<int>(clusters_.size()),
             discovery_[1],
             clustersResponses_,
             clustersIds_,
             newClusters_);

  clustersOld_ = clusters_;

  ready_ = true;
  it_ = 0;
}

void ClassifierClustering::
addExtraSamples(cv::Mat_<float>& extra){
  mNaturalSamples = extra;
}

bool ClassifierClustering::
iterate(){
  if(!ready_){
    ssf::Log::ERROR("Setup method must be called First!");
  }
  int order = it_ % 2;
  clusters_ = newClusters_;
  trainClassifiers(clusters_, natural_[order]);
  newClusters_.clear();
  order = (order + 1) % 2;
  assignment(m_,
             static_cast<int>(clusters_.size()),
             discovery_[order],
             clustersResponses_,
             clustersIds_,
             newClusters_);
  clustersOld_ = clusters_;
  it_++;

  return isFinished();
}

void ClassifierClustering::
learn(
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
  trainClassifiers(clusters_, natural_[order]);
  postCondition();
}

}
