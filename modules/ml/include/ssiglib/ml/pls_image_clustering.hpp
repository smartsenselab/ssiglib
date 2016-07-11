/*L*****************************************************************************
*
*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install, copy
*  or use the software.
*
*                Software License Agreement (BSD License)
*             For Smart Surveillance Interest Group Library
*                         http://ssig.dcc.ufmg.br
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/


#ifndef _SSIG_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
#define _SSIG_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
// c++
#include <utility>
#include <vector>
// ssiglib
#include <ssiglib/core/util.hpp>
#include <ssiglib/core/math.hpp>
#include <ssiglib/ml/classifier_clustering.hpp>
#include <ssiglib/ml/oaa_classifier.hpp>


namespace ssig {

enum ClusterRepresentationType { Centroids, ClustersResponses };

class PLSImageClustering : public ClassifierClustering {
 public:
  ML_EXPORT static cv::Ptr<PLSImageClustering> create();
  ML_EXPORT static cv::Ptr<PLSImageClustering> create(
  ssig::OAAClassifier& classifier,
  const std::vector<std::vector<int>>& discoverySubset,
  const std::vector<ssig::Cluster>& initialClustering);

  ML_EXPORT virtual ~PLSImageClustering() = default;

  ML_EXPORT void predict(const cv::Mat_<float>& inp,
                         cv::Mat_<float>& resp) const override;

  ML_EXPORT bool empty() const override;

  ML_EXPORT bool isTrained() const override;

  ML_EXPORT bool isClassifier() const override;

  ML_EXPORT void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;

  ML_EXPORT void setClassifier(Classifier& classifier) override;

  ML_EXPORT void setClusterRepresentationType(ClusterRepresentationType type);

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT cv::Ptr<OAAClassifier> getClassifier() const;

  ML_EXPORT void setSimBuilder(
    std::unique_ptr<ssig::SimilarityFunctor> function);

  ML_EXPORT int getRepresentationType() const;

  ML_EXPORT float getMergeThreshold() const;

  ML_EXPORT void setMergeThreshold(float mergeThreshold);

  ML_EXPORT float getDeviationThreshold() const;

  ML_EXPORT void setDeviationThreshold(float deviationThreshold);

  ML_EXPORT bool getNormalizeResponses() const;

  ML_EXPORT void setNormalizeResponses(bool normalizeResponses);

  ML_EXPORT bool getMergeConvergence() const;

  ML_EXPORT void setMergeConvergence(bool mergeConvergenve);

  ML_EXPORT int getMaximumMergedPairs() const;

  ML_EXPORT void setMaximumMergedPairs(int nMergesPerIteration1);

 protected:
  ML_EXPORT PLSImageClustering() = default;
  ML_EXPORT PLSImageClustering(
    ssig::OAAClassifier& classifier,
    const std::vector<std::vector<int>>& discoverySubset,
    const std::vector<ssig::Cluster>& initialClustering);

  ML_EXPORT void precondition() override;

  ML_EXPORT void initializeClusterings(
    const std::vector<int>& assignmentSet) override;

  ML_EXPORT void initializeClassifiers() override;

  ML_EXPORT void trainClassifiers(
    const cv::Mat_<float>& samples, const std::vector<Cluster>& clusters,
    const std::vector<int>& negativeLearningSet,
    const std::vector<int>& negativeExtras) override;

  ML_EXPORT virtual void trainClassifiers(
    const std::vector<Cluster>& clusters,
    const std::vector<int>& negativeLearningSet,
    OAAClassifier& classifier) const;

  ML_EXPORT bool isFinished() override;

  ML_EXPORT void postCondition() override;

  ML_EXPORT void assignment(const cv::Mat_<float>& samples,
                            const int clusterSize, const int nClusters,
                            const std::vector<int>& assignmentSet,
                            std::vector<std::vector<float>>& clusterResponses,
                            std::vector<int>& clusterIds,
                            std::vector<Cluster>& out) override;

  ML_EXPORT virtual void merge(std::vector<Cluster>& clusters);

  static
  ML_EXPORT bool findClosestClusters(const cv::Mat& similarityMatrix,
                                     const float threshold,
                                     std::pair<int, int>& closestPair);

  ML_EXPORT void buildClusterRepresentation(
    const cv::Mat_<float>& samples,
    const std::vector<std::vector<int>>& clusters,
    cv::Mat_<float>& clusterRepresentation) const;
  static
  ML_EXPORT void buildResponses(const cv::Mat_<float>& inp,
                                const std::vector<Cluster>& clusters,
                                std::vector<std::vector<float>>& responses,
                                const OAAClassifier& classifier);

  ML_EXPORT void removeMeaninglessClusters(
    std::vector<Cluster>& clusters) const;

 private:
  // private members
  std::unique_ptr<OAAClassifier> mClassifier;
  std::unique_ptr<SimilarityFunctor> mSimilarityFunction;

  int mRepresentationType = ClustersResponses;

  bool mNormalizeResponses = false;

  float mMergeThreshold = 0.7f;
  float mDeviationThreshold = 0.25f;
  bool mMergeOcurred = false;
  bool mMergeConvergence = true;
  int nMergesPerIteration = 8;
};

}  // namespace ssig
#endif  // !_SSIG_ALGORITHMS_PLSIMAGECLUSTERING_HPP_
