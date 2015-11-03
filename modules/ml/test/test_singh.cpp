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

#include "ml/singh.hpp"
#include "ml/classification.hpp"
#include "ml/svm_classifier.hpp"
#include "ml/pls_classifier.hpp"

//TEST(Singh, SVMSeparationTest){
//  cv::Mat_<float> inp;
//  cv::Mat_<float> neg;
//  int N = 60;
//
//  ssf::SVMClassifier classifier;
//  classifier.setC(0.1f);
//  classifier.setKernelType(cv::ml::SVM::LINEAR);
//  classifier.setModelType(cv::ml::SVM::C_SVC);
//
//  classifier.setTermType(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER);
//  classifier.setMaxIterations(static_cast<int>(1e4));
//  classifier.setEpsilon(1e-6f);
//
//
//  cv::FileStorage stg("singhData.yml", cv::FileStorage::READ);
//  ASSERT_TRUE(stg.isOpened());
//  stg["discovery"] >> inp;
//  stg["natural"] >> neg;
//  stg.release();
//
//  std::vector<ssf::Cluster> discoverySubsets;
//  discoverySubsets.resize(2);
//  const int d1len = inp.rows / 2;
//  for(int i = 0; i < 2; ++i){
//    for(int j = 0; j < d1len; ++j){
//      discoverySubsets[i].push_back(j + (d1len * i));
//    }
//  }
//
//  std::vector<ssf::Cluster> naturalVector;
//  naturalVector.resize(2);
//  const int n1Len = neg.rows / 2;
//  for(int i = 0; i < 2; ++i){
//    for(int j = 0; j < n1Len; ++j){
//      naturalVector[i].push_back(j + (n1Len * i));
//    }
//  }
//
//  ssf::Singh clustering;
//
//  clustering.setMaxIterations(8);
//  clustering.setLambda(1.0f);
//  clustering.setMValue(5);
//  clustering.setK(2);
//  clustering.setInitialK(N / 8);
//
//  clustering.setDiscoveryConfiguration(discoverySubsets);
//  clustering.setClassifier(classifier);
//  clustering.addNaturalWorld(neg, naturalVector);
//
//  clustering.setup(inp);
//  bool finished = false;
//  do{
//    auto c = clustering.getClustering();
//    finished = clustering.iterate();
//  } while(!finished);
//
//  auto clusters = clustering.getClustering();
//
//  bool label1 = false;
//  bool label2 = false;
//  for(auto& cluster : clusters){
//    std::vector<int> label1Vector;
//    std::vector<int> label2Vector;
//    for(auto& el : cluster){
//      if((el < 15 && el >= 0) || (el >= 30 && el < 45)){
//        label1Vector.push_back(el);
//      } else{
//        label2Vector.push_back(el);
//      }
//    }
//    if(label1Vector.empty() ^ label2Vector.empty()){
//      if(label1Vector.empty())
//        label2 = true;
//      else
//        label1 = true;
//    }
//  }
//  EXPECT_TRUE(label1 && label2);
//}
