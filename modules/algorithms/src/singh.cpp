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

#include "algorithms/singh.hpp"

namespace ssf{
Singh::~Singh(){
  for(auto& label : mClassifiers)
    delete label;
}


void Singh::predict(
  cv::Mat_<float>& inp,
  cv::Mat_<float>& resp) const{
  resp = cv::Mat_<float>::zeros(inp.rows, static_cast<int>(mClassifiers.size()));
  for(int r = 0; r < inp.rows; ++r){
    for(int i = 0; i < static_cast<int>(mClassifiers.size()); ++i){
      cv::Mat_<float> sampleResp;
      cv::Mat_<float> sample = inp.row(r);
      mClassifiers[i]->predict(sample, sampleResp);
      resp[r][i] = sampleResp[0][0];
    }
  }
}


bool Singh::empty() const{
  return mClassifiers.empty();
}


bool Singh::isTrained() const{
  return trained_;
}


bool Singh::isClassifier() const{
  return false;
}


void Singh::getCentroids(cv::Mat_<float>& centroidsMat) const{
  //TODO:  centroids
}


float Singh::getLambda() const{
  return lambda_;
}


void Singh::setLambda(float lambda){
  lambda_ = lambda;
}


void Singh::load(const std::string& filename, const std::string& nodename){
  //TODO: load
}


void Singh::save(const std::string& filename,
                 const std::string& nodename) const{
  //TODO:save
}


void Singh::precondition(){
  ClassifierClustering::precondition();
  if(lambda_ < 0){
    throw(std::invalid_argument("Invalid Argument for lambda"));
  }
  if(mNatural.size() != 2){
    throw std::length_error("Size of Natural Subsets should be two ");
  }
  //TODO: precondition
}


void Singh::initializeClusterings(
  const std::vector<int>& assignmentSet){

  cv::Mat_<float> feats;
  for(int row : assignmentSet){
    feats.push_back(mSamples.row(row));
  }
  ssf::Kmeans kmeans;
  kmeans.setK(mInitialK);
  kmeans.setFlags(cv::KMEANS_RANDOM_CENTERS);
  kmeans.setNAttempts(1);
  kmeans.setPredicitonDistanceType(cv::NORM_L2);
  kmeans.setMaxIterations(1000);

  kmeans.learn(feats);
  auto initialClustering = kmeans.getClustering();
  cv::Mat_<float> centroids;
  kmeans.getCentroids(centroids);

  std::sort(initialClustering.begin(), initialClustering.end(),
            [](const Cluster& i, const Cluster& j)->bool{
              return i.size() > j.size();
            });
  int pos = 0;
  for(; pos < static_cast<int>(initialClustering.size()); ++pos){
    if(initialClustering[pos].size() < 3){
      break;
    }
  }
  initialClustering.erase(initialClustering.begin() + pos, initialClustering.end());
  for(int i = 0; i < static_cast<int>(initialClustering.size()); ++i){
    mClustersIds.push_back(i);
  }
  mClusters = initialClustering;
}


void Singh::initializeClassifiers(){
  mClassifiers.resize(mClusters.size());
  for(int c = 0; c < static_cast<int>(mClassifiers.size()); c++)
    mClassifiers[c] = nullptr;
}


void Singh::trainClassifiers(const cv::Mat_<float>& samples,
                             const std::vector<Cluster>& clusters,
                             const std::vector<int>& negativeLearningSet){
  cv::Mat_<float> natural;
  for(int id : negativeLearningSet){
    natural.push_back(mNaturalSamples.row(id));
  }
  mClassifiers.clear();
  mClassifiers.resize(clusters.size());
  for(int clusterNum = 0; clusterNum < static_cast<int>(clusters.size()); ++clusterNum){
    //Initialization
    if(mClassifiers[clusterNum] != nullptr){
      delete mClassifiers[clusterNum];
      mClassifiers[clusterNum] = mUnderlyingClassifier->clone();
    } else{
      mClassifiers[clusterNum] = mUnderlyingClassifier->clone();
    }
  }
  for(int clusterNum = 0; clusterNum < static_cast<int>(clusters.size()); ++clusterNum){
    Cluster cluster = clusters[clusterNum];
    cv::Mat_<int> labels = cv::Mat_<int>::zeros(static_cast<int>(negativeLearningSet.size())
                                                + static_cast<int>(cluster.size()), 1);
    labels = -1;

    cv::Mat_<float> trainSamples =
      cv::Mat_<float>::zeros(static_cast<int>(cluster.size()), mSamples.cols);
    int i = 0;
    for(int sample : cluster){
      mSamples.row(sample).copyTo(trainSamples.row(i));
      labels[i][0] = 1;

      ++i;
    }
    trainSamples.push_back(natural);
    mClassifiers[clusterNum]->learn(trainSamples, labels);
  }
}


bool Singh::isFinished(){
  if(mMaxIterations > 0 && (mIt > mMaxIterations)){
    printf("Convergence due to max number of iterations reached\n");
    return true;
  }
  if(mK){
    auto kConvergence = (static_cast<int>(mNewClusters.size()) <= mK);
    if(kConvergence){
      printf("Converged due to minimum K!\n");
      return true;
    }
  }
  return false;
}


void Singh::postCondition(){}


void Singh::assignment(const cv::Mat_<float>& samples, const int clusterSize, const int nClusters, const std::vector<int>& assignmentSet, std::vector<std::vector<float>>& clustersResponses, std::vector<int>& clustersIds, std::vector<Cluster>& out){
  std::vector<std::pair<int, float>> responsesVec;
  std::vector<Cluster> clusters;
  std::vector<int> ids;
  mClustersResponses.clear();
  cv::Mat_<float> responses;
  for(int c = 0; c < nClusters; c++){
    responsesVec.clear();

    int firings = 0;
    responses.release();
    for(int i = 0; i < static_cast<int>(assignmentSet.size()); i++){
      cv::Mat_<float> response;
      cv::Mat_<float> featMat = mSamples.row(assignmentSet[i]);
      mClassifiers[c]->predict(featMat, response);
      auto labelOrdering = mClassifiers[c]->getLabelsOrdering();
      int labelIdx = labelOrdering[1];
      if(response[0][labelIdx] > -1){
        firings++;
      }
      responses.push_back(response);
      responsesVec.push_back(std::pair<int, float>(assignmentSet[i], response[0][labelIdx]));
    }
    if(firings > 2){
      std::sort(responsesVec.begin(), responsesVec.end(),
                [](std::pair<int, float> i, std::pair<int, float> j){
                  return i.second > j.second;
                });

      Cluster newCluster;
      clustersResponses.push_back(std::vector<float>());
      ids.push_back(clustersIds[c]);
      for(int i = 0; i < clusterSize; i++){
        newCluster.push_back(responsesVec[i].first);
        clustersResponses[clusters.size()].push_back(responsesVec[i].second);
      }
      clusters.push_back(newCluster);
    }
  }
  clustersIds = ids;
  out = clusters;
}

void Singh::setClassifier(Classification& classifier){
  mUnderlyingClassifier = std::unique_ptr<Classification>(classifier.clone());
}
}
