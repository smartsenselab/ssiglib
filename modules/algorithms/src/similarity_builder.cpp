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
#include <opencv2/core.hpp>
#include "algorithms/similarity_builder.hpp"

namespace ssf{

cv::Mat_<float> SimilarityBuilder::buildSimilarity(const cv::Mat_<float>& input){
  int len = input.rows;
  cv::Mat_<float> similarity(len, len);
  similarity = 0;
  for(int i = 0; i < len; ++i){
    for(int j = i; j < len; ++j){
      auto x = input.row(i);
      auto y = input.row(j);

      similarity[i][j] = similarityFunction(x, y);
    }
  }
  return similarity;
}

float CosineSimilarity::similarityFunction(const cv::Mat_<float>& x,
                                           const cv::Mat_<float>& y){
  return static_cast<float>(x.dot(y) /
    (cv::norm(x, cv::NORM_L2) * cv::norm(y, cv::NORM_L2)));
}

float CorrelationSimilarity::similarityFunction(const cv::Mat_<float>& x,
                                                const cv::Mat_<float>& y){
  float correlation = 0;
  float i = 0, j = 0, ij = 0, ii = 0, jj = 0;
  int n = x.cols;
  for(int s = 0; s < n; ++s){
    i += x[0][s];
    ii += x[0][s] * x[0][s];

    j += y[0][s];
    jj += y[0][s] * y[0][s];

    ij += x[0][s] * y[0][s];
  }
  correlation = (n * ij - i * j) /
    (sqrt(n * ii - i * i) * sqrt(n * jj - j * j));
  return correlation;
}
}
