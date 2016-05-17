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

#ifndef _SSIG_CORE_GENETIC_OPTIMIZATOR_HPP_
#define _SSIG_CORE_GENETIC_OPTIMIZATOR_HPP_

#include <memory>
#include <vector>

#include "optimization.hpp"

namespace ssig {
/*
@brief
  This implements a genetic optimization.
  This king of heuristical optimization is more recommended
  if the space is not differentiable.
*/
class GeneticOptimizator : public Optimization {
  class CrossOverFunctor {
  public:
    CORE_EXPORT virtual ~CrossOverFunctor() = default;

    CORE_EXPORT virtual void operator()(
      const cv::Mat& indA,
      const cv::Mat& indB,
      cv::Mat& child) = 0;
  };

public:
  virtual ~GeneticOptimizator(void) = default;

  CORE_EXPORT static std::unique_ptr<GeneticOptimizator> create(
    UtilityFunctor& utilityFunction,
    CrossOverFunctor& crossOverFunction);

  CORE_EXPORT void learn(cv::Mat_<float>& input) override;

  CORE_EXPORT void setup(cv::Mat_<float>& input) override;
  CORE_EXPORT void iterate();


protected:
  CORE_EXPORT GeneticOptimizator(void);
  CORE_EXPORT GeneticOptimizator(UtilityFunctor& utilityFunction,
                                 CrossOverFunctor& crossOverFunction);

  void applyReproduction(
    const cv::Mat& pop,
    const cv::Mat& utilities,
    const int newPopLen,
    const CrossOverFunctor& crossover,
    cv::Mat& newPop
  ) const;

  void applyMutation(
    const double mutationRate,
    const cv::Mat& pop,
    cv::Mat& newPop);

  CrossOverFunctor& crossOver;
  UtilityFunctor& utility;

  int mPopulationLength;
  double mElistimFactor,
         mMutationFactor;

  cv::Point2d mMutationRange;

private:
  // private members
};
} // namespace ssig
#endif  // !_SSIG_CORE_GENETIC_OPTIMIZATOR_HPP_
