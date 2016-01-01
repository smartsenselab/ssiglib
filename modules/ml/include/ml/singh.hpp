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


#ifndef _SSIG_ML_SINGH_HPP_
#define _SSIG_ML_SINGH_HPP_

#include <memory>
#include <string>
#include <vector>

#include "ml/classifier_clustering.hpp"
#include "ml/hard_mining_classifier.hpp"
#include "ml/kmeans.hpp"

namespace ssig {

class Singh : public ClassifierClustering {
 public:
  ML_EXPORT Singh(void) = default;
  ML_EXPORT virtual ~Singh(void);

  ML_EXPORT void predict(cv::Mat_<float>& inp,
                         cv::Mat_<float>& resp) const override;
  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;
  ML_EXPORT void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;

  ML_EXPORT void setClassifier(Classifier& classifier) override;

  ML_EXPORT float getLambda() const;

  ML_EXPORT void setLambda(float lambda);

  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

 protected:
  ML_EXPORT void precondition() override;
  ML_EXPORT void initializeClusterings(
      const std::vector<int>& assignmentSet) override;
  ML_EXPORT void initializeClassifiers() override;
  ML_EXPORT void trainClassifiers(
    const cv::Mat_<float>& samples,
    const std::vector<Cluster>& clusters,
    const std::vector<int>& negativeLearningSet,
    const std::vector<int>& negativeExtras) override;
  ML_EXPORT bool isFinished() override;
  ML_EXPORT void postCondition() override;
  ML_EXPORT void assignment(const cv::Mat_<float>& samples,
                            const int clusterSize, const int nClusters,
                            const std::vector<int>& assignmentSet,
                            std::vector<std::vector<float>>& clustersResponses,
                            std::vector<int>& clustersIds,
                            std::vector<Cluster>& out) override;

 private:
  // private members
  float mLambda;
  bool mTrained;
  std::vector<HardMiningClassifier*> mClassifiers;
  std::unique_ptr<Classifier> mUnderlyingClassifier;
};

}  // namespace ssig

#endif  // !_SSIG_ML_SINGH_HPP_
