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
// c++
#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include <ssiglib/ml/ml_defs.hpp>
#include <ssiglib/ml/classification.hpp>

namespace ssig {
class Results {
  cv::Mat_<int> mConfusionMatrix;
  cv::Mat_<int> mGroundTruth;
  cv::Mat_<int> mLabels;
  std::unordered_map<int, int> mLabelMap;
  std::unordered_map<int, std::string> mStringLabels;

public:
  /**
  @return: a pair of float where first is mean precision and second is stddev
  */
  ML_EXPORT static std::pair<float, float> crossValidation(
    const cv::Mat_<float>& features,
    const cv::Mat_<int>& labels,
    const int nfolds,
    const size_t seed,
    ssig::Classifier& classifier,
    std::vector<Results>& out);

  ML_EXPORT static float leaveOneOut(
    const cv::Mat_<float>& features,
    const cv::Mat_<int>& labels,
    ssig::Classifier& classifier,
    Results& result);

  ML_EXPORT Results() = default;
  ML_EXPORT Results(const Results& rhs);
  ML_EXPORT Results(
    const cv::Mat_<int>& actualLabels,
    const cv::Mat_<int>& expectedLabels);

  /**
  return a confusion matrix from applying a random classifier on the data.
  */
  ML_EXPORT cv::Mat getRandomConfusion();

  ML_EXPORT void computeLabelsVec(
    const cv::Mat_<int>& labelMat,
    const cv::Mat_<int>& gtLabelMat,
    std::unordered_map<int, int>& labelsMap) const;

  ML_EXPORT virtual ~Results(void) = default;


  ML_EXPORT std::unordered_map<int, int> getLabelMap() const;
  ML_EXPORT void setLabelMap(const std::unordered_map<int, int>& labelMap);
  ML_EXPORT int getClassesLen() const;

  ML_EXPORT float getAccuracy();
  ML_EXPORT float getMeanAccuracy();

  ML_EXPORT cv::Mat getConfusionMatrix();

  ML_EXPORT void getMapOrderLabel(std::unordered_map<int, int>& map) const;
  ML_EXPORT void setStringLabels(std::unordered_map<int,
                                                    std::string>& stringLabels);

  ML_EXPORT std::vector<int> getLabelsCount();

  ML_EXPORT static void makeConfusionMatrixVisualization(
    const bool color,
    const int blockWidth,
    const cv::Mat_<float>& confusionMatrix,
    cv::Mat& visualization);

  ML_EXPORT static void makeConfusionMatrixVisualization(
    const bool color,
    const int blockWidth,
    const cv::Mat_<float>& confusionMatrix,
    const std::unordered_map<int, int>& labelsVec,
    const std::unordered_map<int, std::string>& stringLabelsMap,
    cv::Mat& visualization);

  ML_EXPORT void makeConfusionMatrixVisualization(
    const bool color,
    const int blockWidth,
    cv::Mat& visualization);

private:
  void compute(
    const cv::Mat_<int>& groundTruth,
    const cv::Mat_<int>& labels,
    std::unordered_map<int, int>& labelsVec,
    cv::Mat_<int>& confusionMatrix) const;

  ML_EXPORT static void makeTextImage(
    const int blockWidth,
    const bool row,
    const std::unordered_map<int, int>& labelMap,
    const std::unordered_map<int, std::string>& stringLabelsMap,
    cv::Mat& img);
};
} // namespace ssig
#endif  // !_SSF_CORE_RESULTS_HPP_
