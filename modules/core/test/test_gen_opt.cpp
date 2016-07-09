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

// c++
#include <random>
#include <numeric>
// ssiglib
#include <ssiglib/core/math.hpp>

#include "ssiglib/core/genetic_optimizator.hpp"

struct TestCrossover : ssig::GeneticOptimizator::CrossOverFunctor {
  void operator()(
    const cv::Mat& indA,
    const cv::Mat& indB,
    cv::Mat& child) const override {
    // implements a random swapping crossover
    child = (indA + indB) / 2;
  }
};

TEST(GenOpt, 2Sqrt) {
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

  cv::Ptr<ssig::UtilityFunctor> util = cv::makePtr<Utility>();
  typedef cv::Ptr<ssig::GeneticOptimizator::CrossOverFunctor> crossPtr;
  crossPtr dist = cv::makePtr<TestCrossover>();
  auto genOpt = ssig::GeneticOptimizator::create(12345, util, dist);
  cv::Mat_<float> input;
  genOpt->setElistimFactor(0.1);
  genOpt->setMutationRange(cv::Point2d(-5, 5));
  genOpt->setMutationRate(0.2);
  genOpt->setPopulationLength(500);
  genOpt->setMutationType(ssig::GeneticOptimizator::Gaussian);
  genOpt->setMaxIterations(500);
  genOpt->setEps(0.0001);
  genOpt->setDimensions(1);

  cv::Mat_<float> minRange = cv::Mat_<float>::zeros(1, 1);
  cv::Mat_<float> maxRange = cv::Mat_<float>::zeros(1, 1);
  minRange = -10.f;
  maxRange = 10.f;

  genOpt->learn(input);
  cv::Mat results = genOpt->getResults();
  cv::Mat_<int> ordering;
  cv::sortIdx(results, ordering, cv::SORT_DESCENDING + cv::SORT_EVERY_COLUMN);
  cv::Mat pop = genOpt->getState();
  auto actual = pop.at<float>(ordering.at<int>(0));
  ASSERT_LT(std::abs(sqrt(2.f) - std::abs(actual)), 0.1f);
}

TEST(GenOpt, 2Dimensions) {
  struct Utility : ssig::UtilityFunctor {
    float operator()(const cv::Mat& v) const override {
      cv::Mat_<float> f;
      v.convertTo(f, CV_32FC1);
      float x = f[0][0];
      float y = f[0][1];
      auto ans = static_cast<float>(x * x + y);
      ans = -1 * std::abs(ans);
      return ans;
    }
  };
  cv::Ptr<ssig::UtilityFunctor> util = cv::makePtr<Utility>();
  typedef cv::Ptr<ssig::GeneticOptimizator::CrossOverFunctor> crossPtr;
  crossPtr cross = cv::makePtr<TestCrossover>();
  auto genOpt = ssig::GeneticOptimizator::create(12345, util, cross);
  cv::Mat_<float> input;
  cv::Vec3f inertia(0.8f, 0.8f, 1.f);

  cv::Mat_<float> minRange = cv::Mat_<float>::zeros(1, 2);
  cv::Mat_<float> maxRange = cv::Mat_<float>::zeros(1, 2);

  genOpt->setElistimFactor(0.1);
  genOpt->setMutationRange(cv::Point2d(-5, 5));
  genOpt->setMutationRate(0.2);
  genOpt->setPopulationLength(500);
  genOpt->setMutationType(ssig::GeneticOptimizator::Gaussian);
  genOpt->setMaxIterations(500);
  genOpt->setEps(0.0001);
  genOpt->setEps(1.0e-5);
  genOpt->setPopulationLength(500);
  genOpt->setMaxIterations(500);

  genOpt->setDimensions(2);

  genOpt->learn(input);
  cv::Mat results = genOpt->getResults();
  cv::Mat_<int> ordering;
  cv::sortIdx(results, ordering, cv::SORT_DESCENDING + cv::SORT_EVERY_COLUMN);
  cv::Mat pop = genOpt->getState();
  cv::Mat actual = pop.row(ordering.at<int>(0));
  auto x = actual.at<float>(0);
  auto y = actual.at<float>(1);

  ASSERT_LE(abs(x*x + y), 0.1f);
}
