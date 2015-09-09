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
#include "classifierClustering.hpp"
#include "kmeans.hpp"
#include "alg_defs.hpp"

namespace ssf{

struct SinghParameters : ClassifierClusteringParams{
  float lambda = 1.0;
};

template<class ClassificationType>
class Singh : public ClassifierClustering{

public:
  ALG_EXPORT Singh(void) = default;
  ALG_EXPORT virtual ~Singh(void) = default;

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
  virtual void trainClassifiers(const std::vector<Cluster>& clusters, std::vector<int> learningSet, std::vector<int> negativeLearningSet) override;
  virtual bool isFinished() override;
  virtual void postCondition() override;
  virtual std::vector<Cluster> assignment(int clusterSize, std::vector<int> assignmentSet) override;

private:
  //private members
  std::vector<std::unique_ptr<ClassificationType*>> classifiers_;
  float lambda_;
  bool trained_;
};

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
    for(int i = 0; i < classifiers_.size(); ++i){
      cv::Mat_<float> sampleResp;
      classifiers_[i]->predict(inp.row(r), sampleResp);
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

  for(auto it = initialClustering.begin(); it != initialClustering.end(); ++it){
    if(it->size() < 3){
      initialClustering.erase(it);
    }
  }
  clusters_ = initialClustering;

}

template<class ClassificationType>
void Singh<ClassificationType>::initializeClassifiers(){
  classifiers_.resize(clusters_.size());
  for(int c = 0; c < classifiers_.size(); c++)
    classifiers_[c] = nullptr;
}

template<class ClassificationType>
void Singh<ClassificationType>::trainClassifiers(const std::vector<Cluster>& clusters,
                                                 std::vector<int> learningSet,
                                                 std::vector<int> negativeLearningSet){
  classifiers_.clear();
  classifiers_.resize(clusters.size());
  for(int clusterNum = 0; clusterNum < clusters.size(); clusterNum++){
    //Initialization
    if(classifiers_[clusterNum] != nullptr){
      delete classifiers_[clusterNum];
      classifiers_[clusterNum] = new ClassificationType();
    } else{
      classifiers_[clusterNum] = new ClassificationType();
    }
    Cluster clusterSet = clusters[clusterNum];
    //Positives
    cv::Mat_<float> feature;
    for(int sample : clusterSet){
      dataX_.row(sample);
      classifiers_[clusterNum]->addSamples(feature, std::to_string(clusterNum));
    }

    ///Negatives
    cv::Mat_<float> naturalFeat;
    for(int row : negativeLearningSet){
       = extraData_.row(row);
      classifiers_[clusterNum]->addSamples(naturalFeat, -1);
    }
    for(int row : negativeLearningSet){
      cv::Mat_<float> naturalFeat = extraData_.row(row);
      classifiers_[clusterNum]->addExtraSamples(naturalFeat, -1);
    }

    classifiers_[clusterNum]->learn();
  }
}
}

#endif // !_SSF_ALGORITHMS_SINGH_HPP_

