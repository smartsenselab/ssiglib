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
#include "classifier_clustering.hpp"
#include "oaa_classifier.hpp"
#include "similarity_builder.hpp"

namespace ssf {

  enum ClusterRepresentationType {
    Centroids,
    ClustersResponses
  };

  class PLSImageClustering :
    public ClassifierClustering {
    public:
    ALG_EXPORT PLSImageClustering() = default;

    ALG_EXPORT virtual ~PLSImageClustering() = default;

    ALG_EXPORT virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp) const override;

    ALG_EXPORT virtual bool empty() const override;

    ALG_EXPORT virtual bool isTrained() const override;

    ALG_EXPORT virtual bool isClassifier() const override;

    ALG_EXPORT virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;

    ALG_EXPORT virtual void setClassifier(Classification& classifier) override;

    ALG_EXPORT void setClusterRepresentationType(ClusterRepresentationType type);

    ALG_EXPORT virtual void load(const std::string& filename, const std::string& nodename) override;

    ALG_EXPORT virtual void save(const std::string& filename, const std::string& nodename) const override;


    ALG_EXPORT virtual void read(const cv::FileNode& fn) override;
    ALG_EXPORT virtual void write(cv::FileStorage& fs) const override;

    ALG_EXPORT std::shared_ptr<OAAClassifier> getClassifier() const;

    ALG_EXPORT std::function < float(cv::Mat_<float>&,
      cv::Mat_<float>&) > getSimBuilder() const;

    ALG_EXPORT void setSimBuilder(const std::function <
      float(cv::Mat_<float>&, cv::Mat_<float>&) > & function);

    ALG_EXPORT int getRepresentationType() const;

    ALG_EXPORT void setRepresentationType(int mRepresentationType1);

    ALG_EXPORT float getMergeThreshold() const;

    ALG_EXPORT void setMergeThreshold(float mMergeThreshold1);

    protected:

    ALG_EXPORT virtual void precondition() override;

    ALG_EXPORT virtual void initializeClusterings(
      const std::vector<int>& assignmentSet) override;

    ALG_EXPORT virtual void initializeClassifiers() override;

    ALG_EXPORT virtual void trainClassifiers(const cv::Mat_<float>& samples, const std::vector<Cluster>& clusters, const std::vector<int>& negativeLearningSet) override;

    ALG_EXPORT virtual void trainClassifiers(const std::vector<Cluster>& clusters,
      const std::vector<int>& negativeLearningSet,
      OAAClassifier& classifier) const;

    ALG_EXPORT virtual bool isFinished() override;

    ALG_EXPORT virtual void postCondition() override;

    ALG_EXPORT virtual void assignment(const cv::Mat_<float>& samples,
      const int clusterSize,
      const int nClusters,
      const std::vector<int>& assignmentSet,
      std::vector<std::vector<float>>& clusterResponses,
      std::vector<int>& clusterIds,
      std::vector<Cluster>& out) override;

    ALG_EXPORT virtual void merge(std::vector<Cluster>& clusters);

    ALG_EXPORT bool findClosestClusters(const cv::Mat& similarityMatrix,
      const float threshold,
      std::pair<int, int>& closestPair);

    ALG_EXPORT void buildClusterRepresentation(const cv::Mat_<float>& samples,
      const std::vector<std::vector<int>>& clusters,
      cv::Mat_<float>& clusterRepresentation) const;

    private:
    //private members
    std::unique_ptr<OAAClassifier> mClassifier;
    std::function <
      float(cv::Mat_<float>&, cv::Mat_<float>&) > mSimilarityFunction;

    int mRepresentationType = ClustersResponses;

    float mMergeThreshold = 0.7f;
    bool mMergeOcurred = false;
  };

}
#endif // !_SSF_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
