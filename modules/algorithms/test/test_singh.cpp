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

#include <gtest/gtest.h>
#include <opencv2/core.hpp>

#include "algorithms/singh.hpp"
#include "algorithms/classification.hpp"
#include "algorithms/svmClassifier.hpp"
#include "algorithms/plsClassifier.hpp"

TEST(Singh, SVMSeparationTest){
  ssf::SinghParameters params;
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;
  int N = 60;

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  stg["discovery"] >> inp;
  stg["natural"] >> neg;
  stg.release();

  auto classifierParam = new ssf::SVMParameters();
  classifierParam->kernelType = cv::ml::SVM::LINEAR;
  classifierParam->modelType = cv::ml::SVM::C_SVC;
  classifierParam->c = 0.1f;
  classifierParam->termType = cv::TermCriteria::MAX_ITER;
  classifierParam->eps = 0.01f;
  classifierParam->maxIt = 1000;

  params.minimumK = 2;
  params.lambda = 0.1f;
  params.d1Len = N / 2;
  params.m = 5;
  params.maxIterations = 8;
  params.params = classifierParam;


  ssf::Singh<ssf::SVMClassifier> clustering;
  clustering.addExtraSamples(neg);
  clustering.learn(inp, &params);

  auto clusters = clustering.getClustering();

  bool label1 = false;
  bool label2 = false;
  for(auto& cluster : clusters){
    std::vector<int> label1Vector;
    std::vector<int> label2Vector;
    for(auto& el : cluster){
      if((el < 15 && el >= 0) || (el >= 30 && el < 45)){
        label1Vector.push_back(el);
      } else{
        label2Vector.push_back(el);
      }
    }
    if(label1Vector.empty() ^ label2Vector.empty()){
      if(label1Vector.empty())
        label2 = true;
      else
        label1 = true;
    }
  }
  EXPECT_TRUE(label1 && label2);
}

TEST(Singh, PLSSeparationTest){
  cv::Mat_<float> inp;
  cv::Mat_<float> neg;
  int N = 60;
  ssf::SinghParameters params;
  auto classifierParam = new ssf::PLSParameters();
  classifierParam->factors = 2;
  classifierParam->termType = cv::TermCriteria::MAX_ITER;
  classifierParam->eps = 0.01f;

  params.minimumK = 2;
  params.lambda = 0.1f;
  params.d1Len = N / 2;
  params.m = 5;
  params.maxIterations = 8;
  params.params = classifierParam;

  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
  stg["discovery"] >> inp;
  stg["natural"] >> neg;
  stg.release();

  ssf::Singh<ssf::PLSClassifier> clustering;
  clustering.addExtraSamples(neg);
  clustering.learn(inp, &params);

  auto clusters = clustering.getClustering();

  bool label1 = false;
  bool label2 = false;
  for(auto& cluster : clusters){
    std::vector<int> label1Vector;
    std::vector<int> label2Vector;
    for(auto& el : cluster){
      if((el < 15 && el >= 0) || (el >= 30 && el < 45)){
        label1Vector.push_back(el);
      } else{
        label2Vector.push_back(el);
      }
    }
    if(label1Vector.empty() ^ label2Vector.empty()){
      if(label1Vector.empty())
        label2 = true;
      else
        label1 = true;
    }
  }
  EXPECT_TRUE(label1 && label2);
}
