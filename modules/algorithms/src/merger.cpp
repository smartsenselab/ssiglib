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

#include "algorithms/merger.hpp"
#include <set>
#include <algorithms/classification.hpp>
#include <algorithms/similarity_builder.hpp>
#include <memory>

namespace ssf{

void HierarchicalMerger::setup(cv::Mat_<float>& samples,
                               ssf::Classification& const classifier,
                               SimilarityBuilder& simBuilder){
  mSamples = samples;
  mClassifier = classifier;
  mSimilarityBuilder = simBuilder;
}

MergerNode HierarchicalMerger::merge(cv::Mat& similarityMatrix,
                                     float simThreshold){
  //MergerNode root;
  //ssf::Classification* newClassifiers = nullptr;
  //bool mergeTermination = false;
  //int nMerges = 0;
  //while(!mergeTermination){
  //  double maxVal;
  //  int pos[] = {-1, -1};
  //  cv::minMaxIdx(similarityMatrix, nullptr, &maxVal, nullptr, pos);
  //  if(maxVal > simThreshold){
  //    similarityMatrix.row(pos[0]) = 0;
  //    similarityMatrix.row(pos[1]) = 0;
  //    similarityMatrix.col(pos[0]) = 0;
  //    similarityMatrix.col(pos[1]) = 0;//in order to avoid comparing again

  //    markedToDie[pos[1]] = true;
  //    auto c1 = clusters[pos[0]];
  //    auto c2 = clusters[pos[1]];
  //    ++nMerges;
  //  } else{
  //    mergeTermination = true;
  //  }

  //}

  //return root;
}

SimpleMerger::~SimpleMerger(){}

MergerNode SimpleMerger::merge(cv::Mat& similarityMatrix, float simThreshold){
  MergerNode root;
  auto merge_termination = false;
  std::vector<std::vector<float>> addToResps;
  int nMerges = 0;
  std::set<int> elements;
  const int n = similarityMatrix.rows;
  for(int i = 0; i < n; ++i){
    elements.insert(i);
  }
  while(!merge_termination){
    double maxVal;
    int pos[] = {-1, -1};
    cv::minMaxIdx(similarityMatrix, nullptr, &maxVal, nullptr, pos);
    if(maxVal > simThreshold){
      similarityMatrix.row(pos[0]) = 0;
      similarityMatrix.row(pos[1]) = 0;
      similarityMatrix.col(pos[0]) = 0;
      similarityMatrix.col(pos[1]) = 0;//in order to avoid comparing again

      MergerNode node;
      std::vector<int> v = {pos[0], pos[1]};
      node.elements.insert(node.elements.begin, v.begin(), v.end());
      root.children.push_back(node);
      ++nMerges;
      elements.erase(pos[0]);
      elements.erase(pos[1]);
    } else{
      merge_termination = true;
    }
  }
  root.elements.insert(root.elements.begin(),
                       elements.begin(), elements.end());
  return root;
}


}
