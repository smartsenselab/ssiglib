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
#ifndef _SSIG_CORE_MATH_HPP_
#define _SSIG_CORE_MATH_HPP_

#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include "ssiglib/core/core_defs.hpp"

namespace ssig {
class UtilityFunctor {
 public:
  virtual ~UtilityFunctor() {}
  UtilityFunctor() = default;
  UtilityFunctor(const UtilityFunctor& rhs) {};

  CORE_EXPORT virtual float operator()(const cv::Mat& vector) const = 0;
};

class DistanceFunctor {
 public:
  virtual ~DistanceFunctor() = default;
  DistanceFunctor() = default;
  DistanceFunctor(const DistanceFunctor& rhs) {};
  CORE_EXPORT virtual float operator()(const cv::Mat& x,
                                       const cv::Mat& y) const = 0;
};

struct CosineSimilarity : DistanceFunctor {
  CORE_EXPORT float operator()(const cv::Mat& x,
                               const cv::Mat& y) const override;
};

struct CorrelationSimilarity : DistanceFunctor {
  CORE_EXPORT float operator()(const cv::Mat& x,
                               const cv::Mat& y) const override;
};

struct Chi2Similarity : DistanceFunctor {
  CORE_EXPORT float operator()(const cv::Mat& x,
                               const cv::Mat& y) const override;
};

struct EuclideanDistance : DistanceFunctor {
  CORE_EXPORT float operator()(
    const cv::Mat& x,
    const cv::Mat& y) const override;
};

typedef DistanceFunctor SimilarityFunctor;

class Math {
 public:
  Math(void);
  virtual ~Math(void);
  Math(const Math& rhs);
  Math& operator=(const Math& rhs);

  CORE_EXPORT static cv::Mat_<float> buildSimilarity(
    const cv::Mat_<float>& input,
    SimilarityFunctor
    & similarityFunction);
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

#endif   // !_SSF_CORE_MATH_HPP_
