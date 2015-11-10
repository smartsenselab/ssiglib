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


#ifndef _SSIG_ML_PLS_HPP_
#define _SSIG_ML_PLS_HPP_

#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

#include <string>
#include <stdexcept>
#include <vector>

#include "ml_defs.hpp"

namespace ssig {

class PLS {
  // set output matrix according to indices
  void setMatrix(cv::Mat_<float>& input, cv::Mat_<float>& output,
                 std::vector<size_t>& indices);

  // compute regression error
  float regError(cv::Mat_<float>& Y, cv::Mat_<float>& responses);

  // function to computer the Bstar (nfactors must be the maximum the number of
  // factors of the PLS model)
  void computeBstar(int nfactors);

 public:
  PLS() = default;
  virtual ~PLS() = default;
  // compute PLS model
  ML_EXPORT void learn(cv::Mat_<float>& X, cv::Mat_<float>& Y, int nfactors);

  // return projection considering n factors
  ML_EXPORT void predict(const cv::Mat_<float>& X, cv::Mat_<float>& projX,
                         int nfactors);

  // retrieve the number of factors
  ML_EXPORT int getNFactors();

  // projection Bstar considering a number of factors (must be smaller than the
  // maximum)
  ML_EXPORT void predict(const cv::Mat_<float>& X, cv::Mat_<float>& ret);

  // save PLS model
  ML_EXPORT void save(std::string filename);
  ML_EXPORT void save(cv::FileStorage& storage);

  // load PLS model
  ML_EXPORT void load(std::string filename);
  ML_EXPORT void load(const cv::FileNode& node);

  // compute PLS using cross-validation to define the number of factors
  ML_EXPORT void learnWithCrossValidation(int folds, cv::Mat_<float>& X,
                                          cv::Mat_<float>& Y, int minDims,
                                          int maxDims, int step);

 protected:
  cv::Mat_<float> mXmean;
  cv::Mat_<float> mXstd;
  cv::Mat_<float> mYmean;
  cv::Mat_<float> mYstd;

  cv::Mat_<float> mB;
  cv::Mat_<float> mT;
  cv::Mat_<float> mP;
  cv::Mat_<float> mW;

  cv::Mat_<float> mWstar;
  cv::Mat_<float> mBstar;

  cv::Mat_<float> mZDataV;
  cv::Mat_<float> mYscaled;
  int mNFactors;
};

template <class T>
void computeMeanStd(cv::Mat_<T>& m, const int layout, cv::Mat_<T>& mean,
                    cv::Mat_<T>& std) {
  cv::Mat aux, auxMean, auxStd;
  int x;
  int len;
  if (layout == cv::ml::ROW_SAMPLE) {
    len = m.rows;
    mean = cv::Mat_<T>::zeros(len, 1);
    std = cv::Mat_<T>::zeros(len, 1);
  } else {
    len = m.cols;
    mean = cv::Mat_<T>::zeros(1, len);
    std = cv::Mat_<T>::zeros(1, len);
  }

  for (x = 0; x < len; x++) {
    if (layout == cv::ml::ROW_SAMPLE) {
      aux = m.row(x);
    } else {
      aux = m.col(x);
    }

    cv::meanStdDev(aux, auxMean, auxStd);
    if (layout == cv::ml::ROW_SAMPLE) {
      mean[x][0] = static_cast<T>(auxMean.at<double>(0, 0));
      std[x][0] = static_cast<T>(auxStd.at<double>(0, 0));
    } else {
      mean[0][x] = static_cast<T>(auxMean.at<double>(0, 0));
      std[0][x] = static_cast<T>(auxStd.at<double>(0, 0));
    }
  }
}

template <typename Type>
void computeZScore(cv::Mat_<Type>& M, cv::Mat_<Type>& mean,
                   cv::Mat_<Type>& std) {
  int y;

  for (y = 0; y < M.rows; y++) {
    M.row(y) -= mean;
    M.row(y) /= std;
  }
}

}  // namespace ssig

#endif  // !_SSIG_ML_PLS_HPP_
