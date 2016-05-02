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

#ifndef _SSIG_ML_HIERARCHICAL_KMEANS_HPP_
#define _SSIG_ML_HIERARCHICAL_KMEANS_HPP_

#include <vector>

#include "clustering.hpp"
#include "ml_defs.hpp"

#include <ssiglib/core/math.hpp>
#include <opencv2/flann.hpp>

namespace ssig {
enum ClusteringDistance {
  L2,
  L1,
  MinkowskiDistance,
  MaxDistance,
  HistIntersectionDistance,
  HellingerDistance,
  ChiSquareDistance,
  KL_Divergence,
};

class HierarchicalKmeans : public Clustering {
 public:
  ML_EXPORT HierarchicalKmeans(void);
  ML_EXPORT virtual ~HierarchicalKmeans(void);
  ML_EXPORT HierarchicalKmeans(const HierarchicalKmeans& rhs);
  ML_EXPORT HierarchicalKmeans& operator=(const HierarchicalKmeans& rhs);

  ML_EXPORT void setup(const cv::Mat_<float>& input) override;
  ML_EXPORT void learn(const cv::Mat_<float>& input) override;
  ML_EXPORT void predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) const override;
  ML_EXPORT std::vector<Cluster> getClustering() const override;
  ML_EXPORT void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;
  ML_EXPORT bool empty() const override;
  ML_EXPORT bool isTrained() const override;
  ML_EXPORT bool isClassifier() const override;
  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

  ML_EXPORT void setDistance(
    const ClusteringDistance& distType,
    const int minkowski = 1);
  ML_EXPORT ClusteringDistance getDistance() const;

  ML_EXPORT int getMinkowskiParameter() const;

  ML_EXPORT void setInitialization(
    const cvflann::flann_centers_init_t& initType);
  ML_EXPORT cvflann::flann_centers_init_t getInitialization() const;
  ML_EXPORT void setBranchingFactor(const int branchingFactor);
  ML_EXPORT int getBranchingFactor() const;
  ML_EXPORT void setCBIndex(const float cbIndex);
  ML_EXPORT float getCBIndex() const;

 private:
  // private members

  ClusteringDistance mDistType;
  cvflann::flann_centers_init_t mInitType;
  int mBranchingFactor = 4;
  int mMinkowski = 3;
  float mCBIndex = 0.2f;
  cv::Mat_<float> mCenters;
};
}  // namespace ssig
#endif  // !_SSIG_ML_HIERARCHICAL_KMEANS_HPP_


