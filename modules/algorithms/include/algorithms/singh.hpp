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
#include <memory>
#include "classifier_clustering.hpp"
#include "kmeans.hpp"
#include "alg_defs.hpp"

namespace ssf{

class Singh :
  public ClassifierClustering{
public:
  ALG_EXPORT Singh(void) = default;
  ALG_EXPORT virtual ~Singh(void);

  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp, cv::Mat_<float>& resp) const override;
  ALG_EXPORT virtual bool empty() const override;
  ALG_EXPORT virtual bool isTrained() const override;
  ALG_EXPORT virtual bool isClassifier() const override;
  ALG_EXPORT virtual void getCentroids(cv::Mat_<float>& centroidsMatrix) const override;

  ALG_EXPORT virtual void setClassifier(Classification& classifier) override;

  ALG_EXPORT float getLambda() const;

  ALG_EXPORT void setLambda(float lambda);


  ALG_EXPORT virtual void load(const std::string& filename, const std::string& nodename) override;
  ALG_EXPORT virtual void save(const std::string& filename, const std::string& nodename) const override;

  ALG_EXPORT virtual void read(const cv::FileNode& fn) override;
  ALG_EXPORT virtual void write(cv::FileStorage& fs) const override;
protected:
  ALG_EXPORT virtual void precondition() override;
  ALG_EXPORT virtual void initializeClusterings(const std::vector<int>& assignmentSet) override;
  ALG_EXPORT virtual void initializeClassifiers() override;
  ALG_EXPORT virtual void trainClassifiers(const cv::Mat_<float>& samples, const std::vector<Cluster>& clusters, const std::vector<int>& negativeLearningSet) override;
  ALG_EXPORT virtual bool isFinished() override;
  ALG_EXPORT virtual void postCondition() override;
  ALG_EXPORT virtual void assignment(const cv::Mat_<float>& samples, const int clusterSize, const int nClusters, const std::vector<int>& assignmentSet, std::vector<std::vector<float>>& clustersResponses, std::vector<int>& clustersIds, std::vector<Cluster>& out) override;

private:
  //private members
  float mLambda;
  bool mTrained;
  std::vector<Classification*> mClassifiers;
  std::unique_ptr<Classification> mUnderlyingClassifier;
};

}

#endif // !_SSF_ALGORITHMS_SINGH_HPP_

