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

#include "ssiglib/video/optical_flow_farneback.hpp"
#include <opencv2/core.hpp>

namespace ssig {
cv::Ptr<cv::DenseOpticalFlow> OpticalFlowFarneback::create() {
  struct _Farneback :OpticalFlowFarneback {};
  return cv::makePtr<_Farneback>();
}

void OpticalFlowFarneback::calc(cv::InputArray I0,
  cv::InputArray I1,
  cv::InputOutputArray flow) {
  cv::Mat i0 = I0.getMat(),
      i1 = I0.getMat();
  cv::Mat flowMat;
  cv::calcOpticalFlowFarneback(i0, i1, flowMat,
                               mPyrscale, mLevels,
                               mWinsize,
                               mIterations,
                               mPoly_n,
                               mPoly_sigma,
                               mFlags);
  flowMat.copyTo(flow);
}

inline double OpticalFlowFarneback::getPyrscale() const {
  return mPyrscale;
}

inline void OpticalFlowFarneback::setPyrscale(const double pyrscale) {
  this->mPyrscale = pyrscale;
}

inline double OpticalFlowFarneback::getPolySigma() const {
  return mPoly_sigma;
}

inline void OpticalFlowFarneback::setPolySigma(const double polySigma) {
  mPoly_sigma = polySigma;
}

inline int OpticalFlowFarneback::getLevels() const {
  return mLevels;
}

inline void OpticalFlowFarneback::setLevels(const int levels) {
  this->mLevels = levels;
}

inline int OpticalFlowFarneback::getWinsize() const {
  return mWinsize;
}

inline void OpticalFlowFarneback::setWinsize(const int winsize) {
  this->mWinsize = winsize;
}

inline int OpticalFlowFarneback::getIterations() const {
  return mIterations;
}

inline void OpticalFlowFarneback::setIterations(const int iterations) {
  this->mIterations = iterations;
}

inline int OpticalFlowFarneback::getPolyN() const {
  return mPoly_n;
}

inline void OpticalFlowFarneback::setPolyN(const int polyN) {
  mPoly_n = polyN;
}

inline int OpticalFlowFarneback::getFlags() const {
  return mFlags;
}

inline void OpticalFlowFarneback::setFlags(const int flags) {
  this->mFlags = flags;
}

}  // namespace ssig


