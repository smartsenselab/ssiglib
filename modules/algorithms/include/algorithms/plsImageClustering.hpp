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

#ifndef _SSF_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
#define _SSF_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
#include <random>
#include <core/util.hpp>
#include "classifierClustering.hpp"
#include "oaa_classifier.hpp"
#include "similarity_builder.hpp"

namespace ssf{

enum ClusterRepresentationType{
  Centroids,
  ClustersResponses
};

struct PLSICParams: ClassifierClusteringParams{
  SimilarityBuilder* simBuilder = nullptr;
  int clusterRepresentationType = Centroids;
  float mergeThreshold = 0.75f;
};


template<class ClassificationType>
class PLSImageClustering :
  public ClassifierClustering{
public:
  ALG_EXPORT PLSImageClustering(void) = default;

  ALG_EXPORT virtual ~PLSImageClustering(void);

  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp) const override;

  ALG_EXPORT virtual bool empty() const override;

  ALG_EXPORT virtual bool isTrained() const override;

  ALG_EXPORT void setup(cv::Mat_<float>& input, ClusteringParams* parameters) override;

  ALG_EXPORT virtual bool isClassifier() const override;

  ALG_EXPORT virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;

  ALG_EXPORT virtual void load(const std::string& filename, const std::string& nodename) override;

  ALG_EXPORT virtual void save(const std::string& filename, const std::string& nodename) const override;
protected:

  ALG_EXPORT virtual void precondition() override;

  ALG_EXPORT virtual void initializeClusterings(
    const std::vector<int>& assignmentSet) override;

  ALG_EXPORT virtual void initializeClassifiers() override;

  ALG_EXPORT virtual void trainClassifiers(const std::vector<Cluster>& clusters,
                                           const std::vector<int>& negativeLearningSet) override;

  ALG_EXPORT virtual void trainClassifiers(const std::vector<Cluster>& clusters,
                                           const std::vector<int>& negativeLearningSet,
                                           OAAClassifier<ClassificationType>& classifier) const;

  ALG_EXPORT virtual bool isFinished() override;

  ALG_EXPORT virtual void postCondition() override;

  ALG_EXPORT virtual void assignment(
    const int clusterSize,
    const int nClusters,
    const std::vector<int>& assignmentSet,
    std::vector<std::vector<float>>& clusterResponses,
    std::vector<int>& clusterIds,
    std::vector<Cluster>& out) override;

  ALG_EXPORT virtual void merge(std::vector<Cluster>& clusters);
private:
  bool findClosestClusters(const cv::Mat& similarityMatrix,
                           const float threshold,
                           std::pair<int, int>& closestPair);
  void buildClusterRepresentation(const cv::Mat_<float>& samples,
                                  const std::vector<std::vector<int>>& clusters,
                                  cv::Mat_<float>& clusterRepresentation) const;
private:
  //private members
  OAAClassifier<ClassificationType> mClassifier;
  SimilarityBuilder* mSimBuilder;

  int mRepresentationType;

  float mMergeThreshold;
  bool mMergeOcurred;
};

template<class ClassificationType>
PLSImageClustering<ClassificationType>::~PLSImageClustering(){}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::predict(cv::Mat_<float>& inp,
                                                     cv::Mat_<float>& resp) const{
  resp.release();
  mClassifier.predict(inp, resp);
}

template<class ClassificationType>
bool PLSImageClustering<ClassificationType>::empty() const{
  return mClassifier.empty();
}

template<class ClassificationType>
bool PLSImageClustering<ClassificationType>::isTrained() const{
  return mClassifier.isTrained();
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::setup(cv::Mat_<float>& input,
                                                   ClusteringParams* parameters){
  auto p = static_cast<PLSICParams*>(parameters);
  mMergeThreshold = p->mergeThreshold;
  mSimBuilder = p->simBuilder;
  mRepresentationType = p->clusterRepresentationType;
  ClassifierClustering
    ::setup(input, parameters);
}

template<class ClassificationType>
bool PLSImageClustering<ClassificationType>::isClassifier() const{
  return false;
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::getCentroids(cv::Mat_<float>& centroidsMatrix) const{
  cv::Mat_<float> centroids;
  buildClusterRepresentation(samples_, clusters_, centroids);
  centroidsMatrix = centroids;
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::load(const std::string& filename, const std::string& nodename){
  //TODO
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::save(const std::string& filename, const std::string& nodename) const{
  //TODO:
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::precondition(){}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::initializeClusterings(
  const std::vector<int>& assignmentSet){
  if(!clusters_.empty()){
    for(int i = 0; i < static_cast<int>(clusters_.size()); ++i){
      clustersIds_.push_back(i);
    }
    return;
  }
  //Make the standard initial Clustering
  std::vector<int> chosen;
  for(int i = 0; i < static_cast<int>(assignmentSet.size()); ++i){
    chosen.push_back(i);
  }
  std::shuffle(chosen.begin(), chosen.end(), std::default_random_engine());
  for(int i = 0; i < mInitialK; ++i){
    clusters_.push_back({chosen[i]});
    clustersIds_.push_back(i);
  }
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::initializeClassifiers(){}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::trainClassifiers(
  const std::vector<Cluster>& clusters,
  const std::vector<int>& negativeLearningSet){
  trainClassifiers(clusters, negativeLearningSet, mClassifier);
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::trainClassifiers(
  const std::vector<Cluster>& clusters,
  const std::vector<int>& negativeLearningSet,
  OAAClassifier<ClassificationType>& classifier) const{
  cv::Mat_<float> inp;
  cv::Mat_<int> labels;
  int label = 0;
  for(auto& cluster : clusters){
    ++label;
    for(auto id : cluster){
      inp.push_back(samples_.row(id));
      labels.push_back(label);
    }
  }

  classifier.learn(inp, labels, classificationParams_);
}

template<class ClassificationType>
bool PLSImageClustering<ClassificationType>::isFinished(){
  if(maxIterations_ > 0 && (it_ > maxIterations_)){
    printf("Convergence due to max number of iterations reached\n");
    return true;
  }
  if(K_){
    auto kConvergence = (static_cast<int>(newClusters_.size()) <= K_);
    if(kConvergence){
      printf("Converged due to minimum K!\n");
      return true;
    }
  }
  if(!mMergeOcurred){
    return true;
  }
  return false;
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::postCondition(){}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::assignment(
  const int clusterSize,
  const int nClusters,
  const std::vector<int>& assignmentSet,
  std::vector<std::vector<float>>& clustersResponses,
  std::vector<int>& clustersIds,
  std::vector<Cluster>& out){

  const int C = static_cast<int>(MIN(nClusters, assignmentSet.size() / clusterSize));
  const int nLabels = static_cast<int>(mClassifier.getLabelsOrdering().size());
  std::unordered_map<int, bool> pointAvailability;
  std::vector<Cluster> clusters;
  clustersResponses.clear();
  std::vector<int> ids;
  cv::Mat_<float> responsesMatrix(
    static_cast<int>(assignmentSet.size()), nLabels);
  for(int sample = 0; sample < static_cast<int>(assignmentSet.size()); ++sample){
    cv::Mat_<float> response;
    cv::Mat_<float> feat = samples_.row(sample);
    mClassifier.predict(feat, response);
    response.copyTo(responsesMatrix.row(sample));
  }
  cv::transpose(responsesMatrix, responsesMatrix);

  cv::Mat_<int> ordering;
  cv::sortIdx(responsesMatrix, ordering, cv::SORT_DESCENDING + cv::SORT_EVERY_ROW);

  //Loop consists of two steps
  // calculating the sum of responses
  // picking the fittest cluster
  int nAssignment = 0;
  std::vector<bool> clusterAssigned(nClusters, false);
  while(nAssignment < C){
    Cluster newCluster;
    //step one:
    float maxSum = -FLT_MAX;
    int chosenClusterId = -1;
    for(int clusterId = 0; clusterId < nClusters; ++clusterId){
      if(clusterAssigned[clusterId])continue;

      int m = 0;
      int i = 0;
      float sum = 0;
      Cluster clusterSet;
      clusterSet.reserve(clusterSize);
      do{
        int sampleId = ordering[clusterId][i];
        auto it = pointAvailability.find(sampleId);
        bool availability = (it == pointAvailability.end()) || it->second;
        if(availability){
          sum += responsesMatrix[clusterId][sampleId];
          clusterSet.push_back(sampleId);
          ++m;
        }
        ++i;
      } while(m < clusterSize);
      if(sum > maxSum){
        maxSum = sum;
        chosenClusterId = clusterId;
        newCluster = clusterSet;
      }
    }

    //step two
    clusterAssigned[chosenClusterId] = true;
    clustersResponses.push_back({});
    ids.push_back(clustersIds[chosenClusterId]);
    for(int p = 0; p < static_cast<int>(newCluster.size()); p++){
      clustersResponses[clusters.size()].push_back(0);
    }
    clusters.push_back(newCluster);
    for(auto& sampleId : newCluster){
      pointAvailability[sampleId] = false;
    }
    nAssignment++;
  }
  clustersIds = ids;

  //MERGING
  merge(clusters);
  out = clusters;
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::buildClusterRepresentation(
  const cv::Mat_<float>& samples,
  const std::vector<std::vector<int>>& clusters,
  cv::Mat_<float>& clusterRepresentation) const{
  if(mRepresentationType == Centroids){
    const int dimensions = samples.cols;
    clusterRepresentation.create(static_cast<int>(clusters.size()), dimensions);
    int i = 0;
    for(auto cluster : clusters){
      cv::Mat_<float> sample(1, dimensions);
      sample = 0;
      for(auto id : cluster){
        sample = sample + samples.row(id);
      }
      cv::Mat_<float> value = (sample / static_cast<int>(cluster.size()));
      value.copyTo(clusterRepresentation.row(i));
      ++i;
    }
  } else if(mRepresentationType == ClustersResponses){
    OAAClassifier<ClassificationType> classifier;
    trainClassifiers(clusters, natural_[0], classifier);
    const int dimensions = static_cast<int>(clusters.size());

    clusterRepresentation.create(samples.rows, dimensions);
    clusterRepresentation = 0;
    for(int r = 0; r < samples.rows; ++r){
      cv::Mat_<float> resp;
      cv::Mat_<float> feat = samples.row(r);
      classifier.predict(feat, resp);
      resp.copyTo(clusterRepresentation.row(r));
    }
    cv::transpose(clusterRepresentation, clusterRepresentation);
  }
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::merge(std::vector<Cluster>& clusters){
  mMergeOcurred = false;

  bool hasMerged = false;
  std::vector<Cluster> ans;
  do{
    if(static_cast<int>(clusters.size()) <= K_){
      ans = clusters;
      break;
    }
    cv::Mat_<float> clusterRepresentation;
    buildClusterRepresentation(samples_, clusters, clusterRepresentation);

    cv::Mat_<float> similarity = mSimBuilder->buildSimilarity(clusterRepresentation);

    std::pair<int, int> mergedPair;
    hasMerged = findClosestClusters(similarity, mMergeThreshold, mergedPair);
    if(hasMerged){
      mMergeOcurred = true;
      int id1 = mergedPair.first;
      int id2 = mergedPair.second;

      clusters[id1].insert(clusters[id1].end(),
                           clusters[id2].begin(),
                           clusters[id2].end());

      Cluster mergeResult;
      mergeResult.insert(mergeResult.end(), clusters[id1].begin(),
                         clusters[id1].end());

      clusters.erase(clusters.begin() + id2);
      clusters.erase(clusters.begin() + id1);

      ans.push_back(mergeResult);
    }

    similarity.release();
  } while(hasMerged);
  if(clusters.size() > 0){
    ans.insert(ans.end(), clusters.begin(), clusters.end());
  }
  clusters = ans;
}

template<class ClassificationType>
bool PLSImageClustering<ClassificationType>::findClosestClusters(
  const cv::Mat& similarityMatrix,
  const float threshold,
  std::pair<int, int>& closestPair){
  double max = 0;
  int idxs[] = {0, 0};
  cv::minMaxIdx(similarityMatrix, nullptr, &max, nullptr, idxs);
  closestPair = std::make_pair(idxs[0], idxs[1]);
  return max >= threshold;
}
}

#endif // !_SSF_ALGORITHMS_PLSIMAGECLUSTERING_HPP_

