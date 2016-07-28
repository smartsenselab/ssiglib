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

#ifndef _SSIG_ML_STACKED_PLS_HPP_
#define _SSIG_ML_STACKED_PLS_HPP_
// c++
#include <vector>
// cv
#include <opencv2/core.hpp>
// ssiglib
#include "ssiglib/core/algorithm.hpp"
#include "ml_defs.hpp"

/**
* Method based on the work of Hasegawa et al(2015)
* Title: Stacked partial least squares regression for image classification
* DOI: 10.1109/ACPR.2015.7486606
* link: http://ieeexplore.ieee.org/xpl/articleDetails.jsp?arnumber=7486606
**/
namespace ssig {
class StackedPLS : public ssig::Algorithm {
 public:
  ML_EXPORT static cv::Ptr<StackedPLS> create();

  virtual ~StackedPLS(void);
  ML_EXPORT StackedPLS(const StackedPLS& rhs);
  ML_EXPORT StackedPLS& operator=(const StackedPLS& rhs);

  ML_EXPORT void learn(
    const std::vector<cv::Mat>& input,
    const cv::Mat& labels);

  ML_EXPORT void extract(
    const cv::Mat& input,
    cv::Mat& output);

  ML_EXPORT std::vector<int> getNumFactors() const;
  ML_EXPORT void setNumFactors(const std::vector<int>& numFactors);
  ML_EXPORT std::vector<int> getConvolutionSize() const;
  ML_EXPORT void setConvolutionSize(const std::vector<int>& convolutionSize);
  ML_EXPORT std::vector<int> getPoolingSize() const;
  ML_EXPORT void setPoolingSize(const std::vector<int>& poolingSize);
  ML_EXPORT cv::Size getCanonicalSize() const;
  ML_EXPORT void setCanonicalSize(const cv::Size& canonicalSize);
  ML_EXPORT std::vector<std::vector<cv::Mat>> getFilters() const;
  ML_EXPORT void setFilters(const std::vector<std::vector<cv::Mat>>& filters);
  ML_EXPORT void getTrainingOutput(cv::Mat& trainSamplesOut) const;

 protected:
  StackedPLS(void);
  void read(const cv::FileNode& fn) override;
  void write(cv::FileStorage& fs) const override;


  /**
  * @brief: this function takes a collection of images and their
   respective labels and pass it through the whole layer pipeline,
   learn filters, convolve, pool and normalize
  *
  **/
  void pass(
    const std::vector<cv::Mat>& input,
    cv::Mat labelMat,
    const int convSize,
    const int poolSize,
    const int numFactors,
    std::vector<cv::Mat>& filters,
    std::vector<std::vector<cv::Mat>>& out) const;

  void resize(
    const cv::Mat& imageMat,
    const int canWidth,
    const int canHeight,
    cv::Mat& unpacked) const;

  void unpack(
    const cv::Mat& input,
    const int S,
    cv::Mat& unpacked) const;

  void computeLayer(
    const std::vector<cv::Mat>& images,
    const cv::Mat& Y,
    const int S,
    const int numFactors,
    std::vector<cv::Mat>& filters) const;

  void normalize(
    const std::vector<cv::Mat>& inp,
    std::vector<cv::Mat>& normalized) const;

  void pool(
    const std::vector<cv::Mat>& convolved,
    const int poolingSize,
    std::vector<cv::Mat>& pooled) const;

 private:
  // private members
  const int mNumLayers = 2;
  std::vector<int> mNumFactors;
  std::vector<int> mConvolutionSize;
  std::vector<int> mPoolingSize;
  cv::Size mCanonicalSize;
  std::vector<std::vector<cv::Mat>> mFilters;

  cv::Mat mTrainOut;
};
}  // namespace ssig
#endif  // !_SSIG_ML_STACKED_PLS_HPP_
