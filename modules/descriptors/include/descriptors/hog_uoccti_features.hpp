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

#ifndef _SSIG_DESCRIPTORS_HOG_UOCCTI_HPP_
#define _SSIG_DESCRIPTORS_HOG_UOCCTI_HPP_

#include <vector>

#include "descriptor_2d.hpp"



namespace ssig {
class HOGUOCCTI : public ssig::Descriptor2D {
  cv::Size mBlockConfiguration;
  cv::Size mCellConfiguration;
  cv::Size mBlockStride;
  int mNumberOfBins = 9;
  float mClipping = 0.2f;
  bool mGammaCorrection = true;

  std::vector<cv::Mat_<double>> mSignedIntegralImages;
  std::vector<cv::Mat_<double>> mIntegralImages;

 public:
  DESCRIPTORS_EXPORT HOGUOCCTI(const cv::Mat& input);

  DESCRIPTORS_EXPORT HOGUOCCTI(const cv::Mat& input,
                               const ssig::HOGUOCCTI& descriptor);

  DESCRIPTORS_EXPORT HOGUOCCTI(const ssig::HOGUOCCTI& descriptor);

  DESCRIPTORS_EXPORT virtual ~HOGUOCCTI(void) = default;

  DESCRIPTORS_EXPORT cv::Size getBlockConfiguration() const;

  DESCRIPTORS_EXPORT void setBlockConfiguration(
    const cv::Size& blockConfiguration);

  DESCRIPTORS_EXPORT cv::Size getBlockStride() const;

  DESCRIPTORS_EXPORT void setBlockStride(const cv::Size& blockStride);

  DESCRIPTORS_EXPORT cv::Size getCellConfiguration() const;

  DESCRIPTORS_EXPORT void setCellConfiguration(
    const cv::Size& cellConfiguration);

  DESCRIPTORS_EXPORT int getNumberOfBins() const;

  DESCRIPTORS_EXPORT void setNumberOfBins(int numberOfBins);

  DESCRIPTORS_EXPORT float getClipping() const;

  DESCRIPTORS_EXPORT void setClipping(float clipping);


 protected:
  DESCRIPTORS_EXPORT void read(const cv::FileNode& fn) override;
  DESCRIPTORS_EXPORT void write(cv::FileStorage& fs) const override;

  DESCRIPTORS_EXPORT void extractFeatures(
    const cv::Rect& patch,
    cv::Mat& output) override;

  DESCRIPTORS_EXPORT void beforeProcess() override;

 private:
  DESCRIPTORS_EXPORT void computeBlockDescriptor(
    int rowOffset,
    int colOffset,
    const std::vector<cv::Mat_<double>>& integralImages,
    const std::vector<cv::Mat_<double>>& signedIntegralImages,
    cv::Mat_<float>& out) const;

  DESCRIPTORS_EXPORT
  std::vector<cv::Mat_<double>> computeIntegralGradientImages(
    const cv::Mat& img,
    bool signedGradient) const;

  DESCRIPTORS_EXPORT cv::Mat normalizeBlock(
    const cv::Mat_<float>& blockFeat) const;
};
}  // namespace ssig
#endif  // !_SSF_DESCRIPTORS_HOG_UOCCTI_HPP_


