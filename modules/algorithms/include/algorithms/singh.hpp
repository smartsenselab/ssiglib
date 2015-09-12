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

#ifndef _SSF_ALGORITHMS_SINGH_HPP_
#define _SSF_ALGORITHMS_SINGH_HPP_
#include <cstdlib>
#include "classifierClustering.hpp"
#include "kmeans.hpp"
#include "alg_defs.hpp"
#include <iostream>

namespace ssf{

struct SinghParameters : ClassifierClusteringParams{
  float lambda = 1.0;
};

template<class ClassificationType>
class Singh : public ClassifierClustering{

public:
  ALG_EXPORT Singh(void) = default;
  ALG_EXPORT virtual ~Singh(void);

  virtual void setup(cv::Mat_<float>& input,
                     ClusteringParams* parameters) override;
  virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp) const override;
  virtual bool empty() const override;
  virtual bool isTrained() const override;
  virtual bool isClassifier() const override;
  virtual cv::Mat_<float> getCentroids() const override;

  virtual void load(const std::string& filename, const std::string& nodename) override;
  virtual void save(const std::string& filename, const std::string& nodename) const override;
protected:
  virtual void precondition() override;
  virtual void initializeClusterings() override;
  virtual void initializeClassifiers() override;
  virtual void trainClassifiers(const std::vector<Cluster>& clusters, const std::vector<int> & negativeLearningSet) override;
  virtual bool isFinished() override;
  virtual void postCondition() override;
  virtual std::vector<Cluster> assignment(int clusterSize, const std::vector<int> & assignmentSet) override;

private:
  //private members
  std::vector<ClassificationType*> classifiers_;
  float lambda_;
  bool trained_;
};

template<class ClassificationType>
Singh<ClassificationType>::~Singh(){
  for(auto& label : classifiers_)
    delete label;
}

template<class ClassificationType>
void Singh<ClassificationType>::setup(cv::Mat_<float>& input, ClusteringParams* parameters){
  ClassifierClustering::setup(input, parameters);
  auto p = static_cast<SinghParameters*>(parameters);
  lambda_ = p->lambda;
}

template<class ClassificationType>
void Singh<ClassificationType>::predict(
  cv::Mat_<float>& inp,
  cv::Mat_<float>& resp) const{
  resp = cv::Mat_<float>::zeros(inp.rows, static_cast<int>(classifiers_.size()));
  for(int r = 0; r < inp.rows; ++r){
    for(int i = 0; i < static_cast<int>(classifiers_.size()); ++i){
      cv::Mat_<float> sampleResp;
      cv::Mat_<float> sample = inp.row(r);
      classifiers_[i]->predict(sample, sampleResp);
      resp[r][i] = sampleResp[0][0];
    }
  }
}

template<class ClassificationType>
bool Singh<ClassificationType>::empty() const{
  return classifiers_.empty();
}

template<class ClassificationType>
bool Singh<ClassificationType>::isTrained() const{
  return trained_;
}

template<class ClassificationType>
bool Singh<ClassificationType>::isClassifier() const{
  return false;
}

template<class ClassificationType>
cv::Mat_<float> Singh<ClassificationType>::getCentroids() const{
  //TODO:
  return{};
}

template<class ClassificationType>
void Singh<ClassificationType>::load(const std::string& filename, const std::string& nodename){
  //TODO:
}

template<class ClassificationType>
void Singh<ClassificationType>::save(const std::string& filename,
                                     const std::string& nodename) const{
  //TODO:
}

template<class ClassificationType>
void Singh<ClassificationType>::precondition(){ }

template<class ClassificationType>
void Singh<ClassificationType>::initializeClusterings(){
  cv::Mat_<float> feats;
  for(int row : discovery_[0]){
    feats.push_back(samples_.row(row));
  }
  ssf::Kmeans kmeans;
  ssf::KmeansParams p;
  p.K = K_;
  p.flags = cv::KMEANS_RANDOM_CENTERS;
  p.nAttempts = 1;
  p.predicitonDistanceType = cv::NORM_L2;
  p.maxIterations = 1000;

  kmeans.learn(feats, &p);
  auto initialClustering = kmeans.getClustering();
  cv::Mat_<float> centroids = kmeans.getCentroids();

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
  for (int i = 0; i < static_cast<int>(initialClustering.size()); ++i) {
    clustersIds_.push_back(i);
  }
  clusters_ = initialClustering;
}

template<class ClassificationType>
void Singh<ClassificationType>::initializeClassifiers(){
  classifiers_.resize(clusters_.size());
  for(int c = 0; c < static_cast<int>(classifiers_.size()); c++)
    classifiers_[c] = nullptr;
}

template<class ClassificationType>
void Singh<ClassificationType>::trainClassifiers(const std::vector<Cluster>& clusters, const std::vector<int> & negativeLearningSet){
  cv::Mat_<float> natural;
  for(int id : negativeLearningSet){
    natural.push_back(naturalSamples_.row(id));
  }
  classifiers_.clear();
  classifiers_.resize(clusters.size());
  for (int clusterNum = 0; clusterNum < static_cast<int>(clusters.size()); ++clusterNum) {
    //Initialization
    if (classifiers_[clusterNum] != nullptr) {
      delete classifiers_[clusterNum];
      classifiers_[clusterNum] = new ClassificationType();
    } else {
      classifiers_[clusterNum] = new ClassificationType();
    }
  }
  for(int clusterNum = 0; clusterNum < static_cast<int>(clusters.size()); ++clusterNum){
    Cluster cluster = clusters[clusterNum];
    cv::Mat_<int> labels = cv::Mat_<int>::zeros(static_cast<int>(negativeLearningSet.size())
                                                + static_cast<int>(cluster.size()), 1);
    labels = -1;

    cv::Mat_<float> trainSamples =
      cv::Mat_<float>::zeros(static_cast<int>(cluster.size()), samples_.cols);
    int i = 0;
    for(int sample : cluster){
      samples_.row(sample).copyTo(trainSamples.row(i));
      labels[i][0] = 1;

      ++i;
    }
    trainSamples.push_back(natural);
    classifiers_[clusterNum]->learn(trainSamples, labels, classificationParams_);
  }
}

template<class ClassificationType>
bool Singh<ClassificationType>::isFinished(){
  if(maxIterations_ > 0 && (it_ > maxIterations_)){
    printf("Convergence due to max number of iterations reached\n");
    return true;
  }
  if(minimumK_){
    auto kConvergence = (static_cast<int>(newClusters_.size()) <= minimumK_);
    if(kConvergence){
      printf("Converged due to minimum K!\n");
      return true;
    }
  }
  return false;
}

template<class ClassificationType>
void Singh<ClassificationType>::postCondition(){}

template<class ClassificationType>
std::vector<Cluster> Singh<ClassificationType>::assignment(int clusterSize, const std::vector<int> & assignmentSet){
  std::vector<std::pair<int, float>> responsesVec;
  std::vector<Cluster> clusters;
  std::vector<int> ids;
  clustersResponses_.clear();
  cv::Mat_<float> responses;
  for(int c = 0; c <static_cast<int>(clusters_.size()); c++){
    responsesVec.clear();

    int firings = 0;
    responses.release();
    for(int i = 0; i <static_cast<int>(assignmentSet.size()); i++){
      cv::Mat_<float> response;
      cv::Mat_<float> featMat = samples_.row(assignmentSet[i]);
      classifiers_[c]->predict(featMat, response);
      auto labelOrdering = classifiers_[c]->getLabelsOrdering();
      int labelIdx = labelOrdering[c];
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
      clustersResponses_.push_back(std::vector<float>());
      ids.push_back(clustersIds_[c]);
      for(int i = 0; i < clusterSize; i++){
        newCluster.push_back(responsesVec[i].first);
        clustersResponses_[clusters.size()].push_back(responsesVec[i].second);
      }
      clusters.push_back(newCluster);
    }
  }
  clustersIds_ = ids;
  return clusters;
}

}

#endif // !_SSF_ALGORITHMS_SINGH_HPP_

