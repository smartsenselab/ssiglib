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

#ifndef _SSIG_CORE_RESULTS_HPP_
#define _SSIG_CORE_RESULTS_HPP_

#include <utility>
#include <vector>
#include <unordered_map>

#include <opencv2/core.hpp>
#include <ml/ml_defs.hpp>

namespace ssig {
class Classifier;

class Results {
  cv::Mat_<int> mConfusionMatrix;
  cv::Mat_<int> mGroundTruth;
  cv::Mat_<int> mLabels;

 public:
  ML_EXPORT Results() = default;
  ML_EXPORT Results(
    const cv::Mat_<int>& actualLabels,
    const cv::Mat_<int>& expectedLabels);
  ML_EXPORT virtual ~Results(void) = default;

  int getClassesLen() const;

  ML_EXPORT float getAccuracy();

  ML_EXPORT cv::Mat getConfusionMatrix();

  ML_EXPORT static std::pair<float, float> crossValidation(
    const cv::Mat_<float>& features,
    const cv::Mat_<int>& labels,
    const int nfolds,
    ssig::Classifier& classifier,
    std::vector<Results>& out);

  ML_EXPORT static void makeConfusionMatrixVisualization(
    const int blockWidth,
    const cv::Mat_<float>& confusionMatrix,
    cv::Mat& visualization);

 private:
  std::unordered_map<int, int> compute(
    const cv::Mat_<int>& groundTruth,
    const cv::Mat_<int>& labels,
    cv::Mat_<int>& confusionMatrix) const;
  // private members
};
}  // namespace ssig
#endif  // !_SSF_CORE_RESULTS_HPP_


