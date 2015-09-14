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

#include "algorithms/firefly_method.hpp"


class Utility{
public:
  float operator()(const cv::Mat_<float>& x){
    return static_cast<float>(1
      /
      cv::norm(x - cv::Mat::ones(1, x.cols, x.type()), cv::NORM_L2));
  }

};

class Distance{
public:
  float operator()(const cv::Mat_<float>& x, const cv::Mat_<float>& y){
    return -1 * static_cast<float>(cv::norm(x - y, cv::NORM_L2));
  }
};

cv::Mat_<float> randomVector(const int d){
  auto& rng = cv::theRNG();
  cv::Mat_<float> vec(1, d);
  for(int i = 0; i < d; ++i){
    vec[0][i] = static_cast<float>(rng.gaussian(100));
  }
  return vec;
}

TEST(Utils, Reorder){

  //TODO: move this test to test_util.cpp

  std::vector<int> a;
  std::vector<int> o;
  for(int i = 0; i < 20; ++i){
    a.push_back(rand() % 20);
  }
  auto gt = a;
  std::sort(gt.begin(), gt.end());
  auto sorted = ssf::Util::sort(a, (a.size()), o);
  ASSERT_EQ(sorted, gt);
}

TEST(Firefly, Execution){
  //Todo: Finish this test implementation
  ssf::Firefly<Utility, Distance> firefly;

  cv::Mat_<float> pop;
  int d = 1;
  pop = cv::Mat::zeros(10, d, CV_32F);
  for(int i = 0; i < 10; ++i){
    auto vec = randomVector(d);
    vec.copyTo(pop.row(i));
  }

  auto clonePop = pop.clone();

  float eps = 0.0f;
  int maxIt = 25;
  float abs = 2.0f;
  float step = 0.005f;
  float annealling = 0.97f;


  firefly.setup(clonePop, {eps, maxIt, abs, step, annealling});
  while(!firefly.iterate()){
    auto state = firefly.getState();
    auto results = firefly.getResults();
  };
  auto results = firefly.getResults();
}
