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

#ifndef _SSIG_DESCRIPTORS_CO_OCCURRENCE_GENERAL_HPP_
#define _SSIG_DESCRIPTORS_CO_OCCURRENCE_GENERAL_HPP_

#define COOCALLDIRS
#define FEATURESCG 12
#define SIGN(x, y) ((y) < 0 ? -fabs(x) : fabs(x))
#define SWAP(a, b) {y = (a); (a) = (b); (b) = y;}
#define PGM_MAXMAXVAL 257
#define RADIX 2.0
#define EPSILON 0.000000001
#define COOC_MAX_MEAS 14
#define COOC_MAX_ANGLES 4
#undef MEAN

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "descriptor_2d.hpp"

typedef int gray;

namespace ssig {
class CoOccurrenceGeneral {
private:
  float Pxpy[2 * PGM_MAXMAXVAL];
  int nbins;
  int distance;

  cv::Mat_<float> M0, M45, M90, M135;
  float **matrix(int nrl, int nrh, int ncl, int nch);
  float *cvector(int nl, int nh);

 public:
  DESCRIPTORS_EXPORT CoOccurrenceGeneral(int nbins, int distance);
  DESCRIPTORS_EXPORT virtual ~CoOccurrenceGeneral(void);
  DESCRIPTORS_EXPORT CoOccurrenceGeneral(const CoOccurrenceGeneral& descriptor);
  DESCRIPTORS_EXPORT CoOccurrenceGeneral& operator=(const CoOccurrenceGeneral&
    rhs);

  DESCRIPTORS_EXPORT int getnBins() const;
  DESCRIPTORS_EXPORT int getDistance() const;
  DESCRIPTORS_EXPORT int getNFeatures();
  DESCRIPTORS_EXPORT void setnBins(const int nbins);
  DESCRIPTORS_EXPORT void setDistance(const int distance);

  // co-occurrence without feature selection
  void ExtractFeatures(int x0, int y0, int x1, int y1, cv::Mat_<int> &img,
    cv::Mat_<float> &m);
  void ExtractFeatures(int x0, int y0, int x1, int y1,
    std::vector<cv::Mat_<int>> &vecImg, cv::Mat_<float> &m);
  void ExtractVectorizedCoocMatrices(int x0, int y0, int x1, int y1,
    cv::Mat_<int> &img, cv::Mat_<float> &m);
  void ExtractVectorizedCoocMatrices(int x0, int y0, int x1, int y1,
    std::vector<cv::Mat_<int>> &vecImg, cv::Mat_<float> &m);

  cv::Mat_<float> getMatrix0();
  cv::Mat_<float> getMatrix45();
  cv::Mat_<float> getMatrix90();
  cv::Mat_<float> getMatrix135();

  DESCRIPTORS_EXPORT void extractMatrix0(const cv::Rect& patch,
    cv::Mat_<int> &img, cv::Mat& output);
  DESCRIPTORS_EXPORT void extractMatrix45(const cv::Rect& patch,
    cv::Mat_<int> &img, cv::Mat& output);
  DESCRIPTORS_EXPORT void extractMatrix90(const cv::Rect& patch,
    cv::Mat_<int> &img, cv::Mat& output);
  DESCRIPTORS_EXPORT void extractMatrix135(const cv::Rect& patch,
    cv::Mat_<int> &img, cv::Mat& output);

  DESCRIPTORS_EXPORT void extractAllMatricesDirections(const cv::Rect& patch,
    cv::Mat_<int> &img, std::vector<cv::Mat>& output);
};
}  // namespace ssig
#endif  // !_SSIG_DESCRIPTORS_CO_OCCURRENCE_GENERAL_HPP_
