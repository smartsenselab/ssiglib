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

#include "ssiglib/ml/results.hpp"

#include <limits.h>
#include <sstream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <ctime>
#include <vector>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include <ssiglib/ml/classification.hpp>

namespace ssig {
Results::Results(
  const cv::Mat_<int>& actualLabels,
  const cv::Mat_<int>& expectedLabels) :
  mGroundTruth(expectedLabels),
  mLabels(actualLabels) {}

void Results::computeLabelsVec(
  const cv::Mat_<int>& groundTruth,
  std::vector<int>& labelsVec) const {
  for (int i = 0; i < groundTruth.rows; ++i) {
    auto label = groundTruth.at<int>(i);
    labelsVec.push_back(label);
  }
  std::sort(labelsVec.begin(), labelsVec.end(), [](const int a, const int b) {
              return a < b;
            });
  auto pos = std::unique(labelsVec.begin(), labelsVec.end());
  labelsVec.erase(pos, labelsVec.end());
}

void Results::compute(
  const cv::Mat_<int>& groundTruth,
  const cv::Mat_<int>& labels,
  std::vector<int>& labelsVec,
  std::vector<int>& labelsVecGt,
  cv::Mat_<int>& confusionMatrix) const {
  computeLabelsVec(groundTruth, labelsVecGt);
  computeLabelsVec(labels, labelsVec);


  auto len1 = static_cast<int>(labelsVecGt.size());
  int len2 = static_cast<int>(labelsVec.size());
  confusionMatrix = cv::Mat_<int>::zeros(len1, len2);
  for (int i = 0; i < groundTruth.rows; ++i) {
    auto value = labels.at<int>(i);
    auto gt = groundTruth.at<int>(i);
    confusionMatrix[labelsVecGt[gt]][labelsVec[value]] += 1;
  }

  std::unordered_map<int, int> labelsMap;
  for (int i = 0; i < static_cast<int>(labelsVec.size()); ++i) {
    labelsMap[labelsVec[i]] = i;
  }
}

int Results::getClassesLen() const {
  return mConfusionMatrix.rows;
}

float Results::getAccuracy() {
  if (mConfusionMatrix.empty())
    compute(mGroundTruth, mLabels,
            mLabelMap,
            mGtLabelMap,
            mConfusionMatrix);

  auto accrcy = cv::trace(mConfusionMatrix);
  accrcy = accrcy / cv::sum(mConfusionMatrix);
  return static_cast<float>(accrcy[0]);
}

float Results::getMeanAccuracy() {
  float ans = 0.f;
  int ncols = mConfusionMatrix.cols;
  for (int r = 0; r < mConfusionMatrix.rows; ++r) {
    float accuracy;
    if (r > ncols) {
      accuracy = 0;
    } else {
      float sum = static_cast<float>(cv::sum(mConfusionMatrix.row(r))[0]);
      accuracy = mConfusionMatrix.at<int>(r, r) / sum;
    }

    ans += accuracy;
  }
  ans = ans / mConfusionMatrix.rows;
  return ans;
}

cv::Mat Results::getConfusionMatrix() {
  if (mConfusionMatrix.empty())
    compute(mGroundTruth,
            mLabels,
            mLabelMap,
            mGtLabelMap,
            mConfusionMatrix);
  return mConfusionMatrix;
}

void Results::getLabelMap(std::vector<int>& rowLabels,
                          std::vector<int>& colLabels) const {
  colLabels.resize(mLabelMap.size()) ,
      rowLabels.resize(mGtLabelMap.size());

  for (int i = 0; i < static_cast<int>(mLabelMap.size()); ++i) {
    colLabels[i] = mLabelMap[i];
  }

  for (int i = 0; i < static_cast<int>(mGtLabelMap.size()); ++i) {
    rowLabels[i] = mGtLabelMap[i];
  }
}

void Results::setStringLabels(std::unordered_map<int,
                                                 std::string>& stringLabels) {
  mStringLabels = stringLabels;
}

std::vector<int> Results::getLabelsCount() {
  if (mConfusionMatrix.empty())
    compute(mGroundTruth, mLabels,
            mLabelMap,
            mGtLabelMap,
            mConfusionMatrix);
  int nrows = mConfusionMatrix.rows;
  std::vector<int> ans(mConfusionMatrix.rows);

  for (int r = 0; r < nrows; ++r) {
    ans[r] = static_cast<int>(cv::sum(mConfusionMatrix.row(r))[0]);
  }
  return ans;
}

std::pair<float, float> Results::crossValidation(
  const cv::Mat_<float>& features,
  const cv::Mat_<int>& labels,
  const int nfolds,
  const size_t seed,
  ssig::Classifier& classifier,
  std::vector<Results>& out) {
  cv::Mat_<float> accuracies(nfolds, 1, 0.0f);
  cv::RNG rng(static_cast<uint64>(seed));
  const int len = features.rows;
  cv::Mat_<int> ordering(len, 1);
  for (int i = 0; i < len; ++i)
    ordering.at<int>(i) = i;
  cv::randShuffle(ordering, 5, &rng);
  int foldLen = static_cast<int>(len / static_cast<float>(nfolds));
  cv::Mat_<float> test, train;

  for (int fold = 0; fold < nfolds; ++fold) {
    const int offset = foldLen * fold;
    cv::Mat_<int> foldOrdering = ordering(cv::Range(offset, foldLen + offset),
                                          cv::Range(0, ordering.cols)).clone();
    cv::sort(foldOrdering, foldOrdering, CV_SORT_EVERY_COLUMN);
    int testIndex = 0;
    cv::Mat_<int> testLabels, trainLabels;
    for (int i = 0; i < len; ++i) {
      auto feature = features.row(i);
      const auto label = labels.at<int>(i);
      if (testIndex < foldOrdering.rows &&
        i == foldOrdering.at<int>(testIndex)) {
        test.push_back(feature);
        testLabels.push_back(label);
        ++testIndex;
      } else {
        train.push_back(feature);
        trainLabels.push_back(label);
      }
    }
    classifier.learn(train, trainLabels);

    cv::Mat_<float> resp;
    cv::Mat_<int> actual;
    for (int r = 0; r < test.rows; ++r) {
      auto query = test.row(r);
      classifier.predict(query, resp);
      auto labelOrdering = classifier.getLabelsOrdering();
      float maxResp = -FLT_MAX;
      int bestLabel = 0;
      for (auto& p : labelOrdering) {
        float curResp = resp.at<float>(p.second);
        if (curResp > maxResp) {
          maxResp = curResp;
          bestLabel = p.first;
        }
      }
      actual.push_back(bestLabel);
    }

    Results result(actual, testLabels);
    out.push_back(result);
    auto acrcy = result.getAccuracy();
    accuracies.at<float>(fold) = acrcy;
    train.release();
    test.release();
  }
  cv::Scalar mean, stdev;
  cv::meanStdDev(accuracies, mean, stdev);

  return std::make_pair(static_cast<float>(mean[0]),
                        static_cast<float>(stdev[0]));
}

void Results::makeConfusionMatrixVisualization(
  const int blockWidth,
  const cv::Mat_<float>& confusionMatrix,
  cv::Mat& visualization) {
  if (confusionMatrix.rows != confusionMatrix.cols) {
    std::string warningMessage = "A confusion matrix must have same";
    warningMessage = warningMessage + "number of rows and cols";
    std::runtime_error(warningMessage.c_str());
  }
  const int nclasses = confusionMatrix.rows;
  cv::Mat aux = confusionMatrix.clone();
  aux.convertTo(aux, CV_64F);

  cv::Mat_<float> visFloat = cv::Mat_<float>::zeros
      (blockWidth * nclasses, blockWidth * nclasses);
  for (int r = 0; r < confusionMatrix.rows; ++r) {
    cv::normalize(aux.row(r), aux.row(r), 1, 0, cv::NORM_L1);
  }
  for (int i = 0; i < nclasses; ++i) {
    for (int j = 0; j < nclasses; ++j) {
      cv::Mat roi = visFloat(cv::Rect(j * blockWidth, i * blockWidth,
                                      blockWidth, blockWidth));
      roi = aux.at<float>(i, j);
    }
  }

  visFloat.convertTo(aux, CV_8UC1, 255);

  cv::applyColorMap(aux, visualization, cv::COLORMAP_JET);

  for (int i = 0; i < nclasses; ++i) {
    cv::Mat temp = visualization(cv::Rect(i * blockWidth, i * blockWidth,
                                          blockWidth, blockWidth));
    const int x = i * blockWidth;
    const int y = i * blockWidth;
    auto color = CV_RGB(255, 255, 255);
    const int len = blockWidth - 1;
    cv::line(visualization,
             cv::Point(x, y),
             cv::Point(x + len, y),
             color, 1);

    cv::line(visualization,
             cv::Point(x, y),
             cv::Point(x, y + len),
             color, 1);

    cv::line(visualization,
             cv::Point(x + len, y),
             cv::Point(x + len, y + len),
             color, 1);

    cv::line(visualization,
             cv::Point(x, y + len),
             cv::Point(x + len, y + len),
             color, 1);
  }
}

void Results::makeConfusionMatrixVisualization(const int blockWidth,
                                               cv::Mat& visualization) {
  cv::Mat confusionMatrix = getConfusionMatrix();
  const int nclasses = static_cast<int>(mLabelMap.size());
  cv::Mat aux = confusionMatrix.clone();
  aux.convertTo(aux, CV_64F);

  /* cv::Mat textLabels;
   makeTextImage(textLabels);
   float scale = blockWidth * nclasses / static_cast<float>(textLabels.cols);
   cv::resize(textLabels, textLabels,
              cv::Size(blockWidth * nclasses,
                       static_cast<int>(scale * textLabels.rows)));*/

  cv::Mat_<float> visFloat = cv::Mat_<float>::zeros
      (blockWidth * nclasses, blockWidth * nclasses);
  for (int r = 0; r < aux.rows; ++r) {
    cv::normalize(aux.row(r), aux.row(r), 1, 0, cv::NORM_L1);
  }
  for (int i = 0; i < nclasses; ++i) {
    for (int j = 0; j < nclasses; ++j) {
      cv::Mat roi = visFloat(cv::Rect(j * blockWidth, i * blockWidth,
                                      blockWidth, blockWidth));
      roi = aux.at<double>(i, j);
    }
  }

  visFloat.convertTo(aux, CV_8UC1, 255);

  cv::applyColorMap(aux, visualization, cv::COLORMAP_JET);

  for (int i = 0; i < nclasses; ++i) {
    cv::Mat temp = visualization(cv::Rect(i * blockWidth, i * blockWidth,
                                          blockWidth, blockWidth));
    const int x = i * blockWidth;
    const int y = i * blockWidth;
    auto color = CV_RGB(255, 255, 255);
    const int len = blockWidth - 1;
    cv::line(visualization,
             cv::Point(x, y),
             cv::Point(x + len, y),
             color, 1);

    cv::line(visualization,
             cv::Point(x, y),
             cv::Point(x, y + len),
             color, 1);

    cv::line(visualization,
             cv::Point(x + len, y),
             cv::Point(x + len, y + len),
             color, 1);

    cv::line(visualization,
             cv::Point(x, y + len),
             cv::Point(x + len, y + len),
             color, 1);
  }
  // textLabels.push_back(visualization);
  // visualization = textLabels;
}

// TODO(Ricardo): Improve label text visualization
//  void Results::makeTextImage(cv::Mat& img) {
//  int textLen = 0;
//  std::vector<std::string> strVec(mLabelMap.size());
//  if (mStringLabels.size() >= mLabelMap.size()) {
//    for (const auto& it : mStringLabels) {
//      if (mLabelMap.find(it.first) != mLabelMap.end()) {
//        strVec[mLabelMap[it.first]] = it.second;
//      }
//      int len = static_cast<int>(it.second.size());
//      if (len > textLen)
//        textLen = len;
//    }
//  }
//
//  for (int j = 0; j < textLen; ++j) {
//    cv::Mat auxMat;
//    std::stringstream aux;
//    for (int i = 0; i < static_cast<int>(strVec.size()); ++i) {
//      if (j < strVec[i].size())
//        aux << strVec[i][j];
//      else
//        aux << " ";
//    }
//    int baseline;
//    cv::Size sz = cv::getTextSize(aux.str(),
//                                cv::HersheyFonts::FONT_HERSHEY_COMPLEX_SMALL,
//                                  10, 3, &baseline);
//    auxMat = cv::Mat::zeros(sz, CV_8UC3);
//    auxMat = 0;
//    cv::putText(auxMat, aux.str(), cv::Point(0, auxMat.rows),
//                cv::HersheyFonts::FONT_HERSHEY_COMPLEX_SMALL,
//                10, cv::Scalar(255, 255, 255), 3, cv::LineTypes::FILLED);
//    if (!img.empty())
//      cv::resize(auxMat, auxMat, cv::Size(img.cols, auxMat.rows));
//    img.push_back(auxMat);
//  }
//  }
}  // namespace ssig
