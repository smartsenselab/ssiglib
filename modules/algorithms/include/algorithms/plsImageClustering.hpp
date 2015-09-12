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
#include "classifierClustering.hpp"
#include "oaa_classifier.hpp"
#include "merger.hpp"
#include "similarity_builder.hpp"

namespace ssf{
struct PLSICParams: ClassifierClusteringParams{
  SimilarityBuilder& simBuilder;
};


template<class ClassificationType>
class PLSImageClustering : public ClassifierClustering{

public:
  PLSImageClustering(void) = default;
  virtual ~PLSImageClustering(void) = default;

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
  virtual void trainClassifiers(const std::vector<Cluster>& clusters,
                                const std::vector<int>& negativeLearningSet) override;
  virtual bool isFinished() override;
  virtual void postCondition() override;
  virtual std::vector<Cluster> assignment(int clusterSize, const std::vector<int>& assignmentSet) override;

  virtual void merge();
private:
  std::vector<Cluster> joinClosestClusters(cv::Mat& similarityMatrix);
private:
  //private members
  OAAClassifier<ClassificationType> mClassifier;
  SimilarityBuilder* mSimBuilder;
};

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
void PLSImageClustering<ClassificationType>::initializeClusterings(){
  if(!clusters_.empty()) return;
  //Make the standard initial Clustering
}

template<class ClassificationType>
void PLSImageClustering<ClassificationType>::merge(){
  cv::Mat_<float> similarity = mSimBuilder->buildSimilarity();
  auto mergeResult = mMerger->merge(similarity);
}
}

#endif // !_SSF_ALGORITHMS_PLSIMAGECLUSTERING_HPP_

