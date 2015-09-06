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

#ifndef _SSF_ALGORITHMS_CLASSIFICATIONCLUSTERING_HPP_
#define _SSF_ALGORITHMS_CLASSIFICATIONCLUSTERING_HPP_

#include "alg_defs.hpp"

#include "clusteringMethod.hpp"
#include "classification.hpp"
#include "iterableMethod.hpp"

namespace ssf{
struct ClassifierClusteringParams : ClusteringParams{
  int m = 5;
  int minimumK = 20;
  int maximumK = static_cast<int>(1.0e6);
};

class ClassifierClustering : public ClusteringMethod,
                             IterableMethod{
public:
  ALG_EXPORT virtual ~ClassifierClustering(void) = default;
  ClassifierClustering(const ClassifierClustering& rhs);
  ClassifierClustering& operator=(const ClassifierClustering& rhs);

  ALG_EXPORT virtual void setup(cv::Mat_<float>& input,
                                ClusteringParams* parameters) override;

  ALG_EXPORT void learn(cv::Mat_<float>& input,
                        ClusteringParams* parameters) override;

  ALG_EXPORT virtual void predict(cv::Mat_<float>& inp,
                                  cv::Mat_<float>& resp) const override = 0;

  ALG_EXPORT virtual std::vector<Cluster> getClustering() const override;
  ALG_EXPORT virtual bool empty() const override = 0;
  ALG_EXPORT virtual bool isTrained() const override = 0;
  ALG_EXPORT virtual bool isClassifier() const override = 0;

  ALG_EXPORT bool iterate() override;

  ALG_EXPORT virtual cv::Mat_<float> getCentroids()const override = 0;

  ALG_EXPORT virtual void load(const std::string& filename,
                               const std::string& nodename) override = 0;
  ALG_EXPORT virtual void save(const std::string& filename,
                               const std::string& nodename)const override = 0;

protected:
  virtual void precondition() = 0;

  virtual void initializeClusterings() = 0;
  virtual void initializeClassifiers() = 0;
  virtual void trainClassifiers(const std::vector<Cluster>& clusters, std::vector<int> learningSet, std::vector<int> negativeLearningSet) = 0;
  virtual bool isFinished() = 0;

  virtual void postCondition() = 0;

  virtual std::vector<Cluster> assignment(int clusterSize, std::vector<int> assignmentSet) = 0;

  //Attributes /////////
  int maximumK_;
  int minimumK_;
  int m_;
  int it_;

private:
  //private members
  std::vector<std::unique_ptr<Classification>> classifiers_;
  std::vector<std::vector<int>> discovery_;
  std::vector<std::vector<int>> natural_;

  std::vector<Cluster> clustersOld_, newClusters_;


};

}

#endif // !_SSF_ALGORITHMS_CLASSIFICATIONCLUSTERING_HPP_

