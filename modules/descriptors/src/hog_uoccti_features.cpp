///*L*****************************************************************************
//*
//*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
//*
//*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//*
//*  By downloading, copying, installing or using the software you agree to this
//*  license. If you do not agree to this license, do not download, install, copy
//*  or use the software.
//*
//*                Software License Agreement (BSD License)
//*             For Smart Surveillance Interest Group Library
//*                         http://ssig.dcc.ufmg.br
//*
//*  Redistribution and use in source and binary forms, with or without
//*  modification, are permitted provided that the following conditions are met:
//*
//*    1. Redistributions of source code must retain the above copyright notice,
//*       this list of conditions and the following disclaimer.
//*
//*    2. Redistributions in binary form must reproduce the above copyright
//*       notice, this list of conditions and the following disclaimer in the
//*       documentation and/or other materials provided with the distribution.
//*
//*    3. Neither the name of the copyright holder nor the names of its
//*       contributors may be used to endorse or promote products derived from
//*       this software without specific prior written permission.
//*
//*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//*  POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************L*/
//
//#include "descriptors/hog_uoccti_features.hpp"
//
//namespace ssig {
//
//HOGUOCCTI::HOGUOCCTI(const cv::Mat& input) : HOG(input) {}
//
//HOGUOCCTI::HOGUOCCTI(const cv::Mat& input, const ssig::HOGUOCCTI& descriptor)
//  : HOG(input, descriptor) {
//  mBlockConfiguration = descriptor.getBlockConfiguration();
//  mBlockStride = descriptor.getBlockStride();
//  mCellConfiguration = descriptor.getCellConfiguration();
//  mClipping = descriptor.getClipping();
//  mNumberOfBins = descriptor.getNumberOfBins();
//}
//
//HOGUOCCTI::HOGUOCCTI(const ssig::HOGUOCCTI& descriptor) : HOG(descriptor) {
//  mBlockConfiguration = descriptor.getBlockConfiguration();
//  mBlockStride = descriptor.getBlockStride();
//  mCellConfiguration = descriptor.getCellConfiguration();
//  mClipping = descriptor.getClipping();
//  mNumberOfBins = descriptor.getNumberOfBins();
//}
//
//void HOGUOCCTI::computeBlockDescriptor(
//  int rowOffset,
//  int colOffset,
//  const std::vector<cv::Mat_<float>>& integralImages,
//  cv::Mat_<float>& out) const {
//  const int blockWidth = mBlockConfiguration.width;
//  const int blockHeight = mBlockConfiguration.height;
//  int ncells_cols = mCellConfiguration.width,
//    ncells_rows = mCellConfiguration.height;
//
//  const int cellWidth =
//    static_cast<int>(blockWidth / static_cast<float>(ncells_cols));
//  const int cellHeight =
//    static_cast<int>(blockHeight / static_cast<float>(ncells_rows));
//
//  const int ncells = ncells_cols * ncells_rows;
//
//  std::vector<cv::Mat_<float>> cellHistograms(ncells);
//  for(int i = 0; i <ncells; ++i){
//    cellHistograms[i].create(1, mNumberOfBins);
//    cellHistograms[i] = FLT_MAX ;
//  }
//  int cell_it = -1;
//  for (int cellRow = 0; cellRow < ncells_rows; ++cellRow) {
//    for (int cellCol = 0; cellCol < ncells_cols; ++cellCol) {
//      const int a = rowOffset + cellRow * cellWidth;
//      const int b = colOffset + cellHeight * cellCol;
//      const int w = cellWidth - 1;
//      const int h = cellHeight - 1;
//
//      for (int bin = 0; bin < mNumberOfBins; ++bin) {
//        auto integralImage = integralImages[bin];
//        float v1 = integralImage[a][b];
//        float v2 = integralImage[a][b + w];
//        float v3 = integralImage[a + h][b];
//        float v4 = integralImage[a + h][b + w];
//
//        float value = std::max(v1 + v4 - (v2 + v3), 0.0f);
//        cellHistograms[++cell_it][0][bin] = value;
//      }
//    }
//  }
//
//  // L2Hys
//  float l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
//  ans = ans / (cv::sqrt(l2norm * l2norm + 0.1f));
//  cv::checkRange(ans, false, nullptr, 0.0, FLT_MAX);
//  if (mClipping > 0) {
//    for (int i = 0; i < ans.cols; i++) {
//      ans[0][i] = std::min(ans[0][i], mClipping);
//    }
//  }
//  cv::checkRange(ans, false, nullptr, 0.0, mClipping + FLT_EPSILON);
//  l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
//  ans = ans / (cv::sqrt(l2norm * l2norm + 0.1f));
//  cv::checkRange(ans, false);
//  out = ans;
//}
//
//bool HOGUOCCTI::getSignedGradient() const {
//  return false;
//}
//
//void HOGUOCCTI::setSignedGradient(const bool signedGradient) {}
//} // namespace ssig
//
//
