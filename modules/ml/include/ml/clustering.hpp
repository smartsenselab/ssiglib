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


#ifndef _SSIG_ALGORITHMS_CLUSTERING_HPP_
#define _SSIG_ALGORITHMS_CLUSTERING_HPP_

#include <opencv2/core.hpp>

#include <vector>
#include <string>

#include "ml/ml_defs.hpp"
#include "core/algorithm.hpp"

namespace ssig {
typedef std::vector<int> Cluster;

class Clustering : public Algorithm {
public:
  ML_EXPORT Clustering(void) = default;
  ML_EXPORT virtual ~Clustering(void) = default;

  ML_EXPORT virtual void setInitialClustering(const std::vector<Cluster>& init);

  ML_EXPORT virtual void setup(
    const cv::Mat_<float>& input) = 0;

  ML_EXPORT virtual void learn(
    const cv::Mat_<float>& input) = 0;

  ML_EXPORT virtual void predict(
    const cv::Mat_<float>& inp,
    cv::Mat_<float>& resp) = 0;

  ML_EXPORT virtual std::vector<Cluster> getClustering() const = 0;

  virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const = 0;

  ML_EXPORT virtual bool empty() const = 0;
  ML_EXPORT virtual bool isTrained() const = 0;
  ML_EXPORT virtual bool isClassifier() const = 0;

  ML_EXPORT void read(const cv::FileNode& fn) override = 0;
  ML_EXPORT void write(cv::FileStorage& fs) const override = 0;

  ML_EXPORT int getK() const {
    return mK;
  }

  ML_EXPORT void setK(int k) {
    mK = k;
  }

  ML_EXPORT int getMaxIterations() const {
    return mMaxIterations;
  }

  ML_EXPORT void setMaxIterations(int maxIterations) {
    mMaxIterations = maxIterations;
  }

protected:
  cv::Mat_<float> mSamples;
  std::vector<Cluster> mClusters;
  int mK;
  int mMaxIterations;
  bool mReady;
};

} // namespace ssig
#endif // !_SSIG_ALGORITHMS_CLUSTERING_HPP_


