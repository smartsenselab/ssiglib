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

#ifndef _SSF_ALGORITHMS_CLUSTERINGMETHOD_HPP_
#define _SSF_ALGORITHMS_CLUSTERINGMETHOD_HPP_

#include <opencv2/core.hpp>
#include <memory>
#include <vector>
#include "learningMethod.hpp"

#include "alg_defs.hpp"

namespace ssf{
typedef std::vector<int> Cluster;

struct ClusteringParams{
  int K;
  int maxIterations;
};

class ClusteringMethod : public
  ssf::UnsupervisedLearningMethod<cv::Mat_<float>,
                                  cv::Mat_<float>,
                                  ClusteringParams>{
public:
  ALG_EXPORT ClusteringMethod(void) = default;
  ALG_EXPORT virtual ~ClusteringMethod(void) = default;

  ALG_EXPORT virtual void addInitialClustering(
    const std::vector<Cluster>& init);

  ALG_EXPORT virtual void setup(cv::Mat_<float>& input,
                        ClusteringParams* parameters) = 0;

  ALG_EXPORT void learn(cv::Mat_<float>& input,
                        ClusteringParams* parameters) override = 0;

  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp)const override = 0;

  ALG_EXPORT virtual std::vector<Cluster> getClustering()const = 0;

  virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const = 0;

  ALG_EXPORT virtual bool empty() const override = 0;
  ALG_EXPORT virtual bool isTrained() const override = 0;
  ALG_EXPORT virtual bool isClassifier() const override = 0;

  virtual void load(const std::string& filename, const std::string& nodename) override = 0;
  virtual void save(const std::string& filename, const std::string& nodename) const override = 0;

protected:
  cv::Mat_<float> samples_;
  std::vector<Cluster> clusters_;
  int K_;
  int maxIterations_;
  bool ready_;
};

}

#endif // !_SSF_ALGORITHMS_CLUSTERINGMETHOD_HPP_

