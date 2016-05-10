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

#include <gtest/gtest.h>

#include <ssiglib/core/math.hpp>

#include "ssiglib/core/pso.hpp"


struct Distance : ssig::DistanceFunctor {
  virtual float operator()(const cv::Mat& x,
    const cv::Mat& y) const override {
    return static_cast<float>(cv::norm(x - y, cv::NORM_L1));
  }
};

TEST(PSO, 2Sqrt) {
  struct Utility : ssig::UtilityFunctor {
    float operator()(const cv::Mat& v) const override {
      cv::Mat_<float> f;
      v.convertTo(f, CV_32FC1);
      float x = f[0][0];
      auto ans = static_cast<float>(x * x - 2);
      ans = -1 * std::abs(ans);
      return ans;
    }
  };
  Utility util;
  Distance dist;
  auto pso = ssig::PSO::create(util, dist);
  cv::Mat_<float> input;
  cv::Mat inertia;
  inertia = (cv::Mat_<float>(1, 3) << 0.8f , 0.8f , 1.f);
  pso->setInertia(inertia);
  pso->setDimensionality(1);
  pso->setPopulationConstraint(-10.f, 10.f);
  pso->setEps(1.0e-9);
  pso->setPopulationLength(static_cast<int>(2.0e2));
  pso->setMaxIterations(500);

  pso->learn(input);
  cv::Mat results = pso->getResults();
  cv::Mat pop = pso->getState();
  auto actual = pso->getBestPosition().at<float>(0);
  ASSERT_LT(std::abs(sqrt(2.f) - std::abs(actual)), 0.005f);
}

