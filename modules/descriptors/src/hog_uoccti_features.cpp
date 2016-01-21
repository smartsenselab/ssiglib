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

#include "descriptors/hog_uoccti_features.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <vector>
#include <algorithm>

namespace ssig {

HOGUOCCTI::HOGUOCCTI(const cv::Mat& input) : Descriptor2D(input) {}

HOGUOCCTI::HOGUOCCTI(const cv::Mat& input, const ssig::HOGUOCCTI& descriptor)
  : Descriptor2D(input, descriptor) {
  mBlockConfiguration = descriptor.getBlockConfiguration();
  mBlockStride = descriptor.getBlockStride();
  mCellConfiguration = descriptor.getCellConfiguration();
  mClipping = descriptor.getClipping();
  mNumberOfBins = descriptor.getNumberOfBins();
}

HOGUOCCTI::HOGUOCCTI(const ssig::HOGUOCCTI& descriptor) :
  Descriptor2D(descriptor) {
  mBlockConfiguration = descriptor.getBlockConfiguration();
  mBlockStride = descriptor.getBlockStride();
  mCellConfiguration = descriptor.getCellConfiguration();
  mClipping = descriptor.getClipping();
  mNumberOfBins = descriptor.getNumberOfBins();
}

void HOGUOCCTI::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
  const int imgRows = patch.height;
  const int imgCols = patch.width;

  const int blockWidth = mBlockConfiguration.width;
  const int blockHeight = mBlockConfiguration.height;
  const int rowOffset = imgRows % blockHeight;
  const int colOffset = imgCols % blockWidth;

  for (int row = 0; row <= imgRows - rowOffset - blockHeight;
       row += mBlockStride.height) {
    for (int col = 0; col <= imgCols - colOffset - blockWidth;
         col += mBlockStride.width) {
      cv::Mat_<float> cellDescriptor;
      computeBlockDescriptor(row, col, mIntegralImages,
                             mSignedIntegralImages,
                             cellDescriptor);

      if (output.empty()) {
        output = cellDescriptor;
      } else {
        cv::hconcat(output.clone(), cellDescriptor, output);
      }
    }
  }
}

void HOGUOCCTI::beforeProcess() {
  if (mImage.empty())return;
  mIntegralImages = computeIntegralGradientImages(mImage, false);
  mSignedIntegralImages = computeIntegralGradientImages(mImage, true);
}

void HOGUOCCTI::computeBlockDescriptor(
  int rowOffset,
  int colOffset,
  const std::vector<cv::Mat_<double>>& integralImages,
  const std::vector<cv::Mat_<double>>& signedIntegralImages,
  cv::Mat_<float>& out) const {
  const int signedBins = 2 * mNumberOfBins;
  const int blockWidth = mBlockConfiguration.width;
  const int blockHeight = mBlockConfiguration.height;
  int ncells_cols = mCellConfiguration.width,
    ncells_rows = mCellConfiguration.height;

  const int cellWidth =
    static_cast<int>(blockWidth / static_cast<float>(ncells_cols));
  const int cellHeight =
    static_cast<int>(blockHeight / static_cast<float>(ncells_rows));

  const int ncells = ncells_cols * ncells_rows;


  std::vector<cv::Mat_<float>> cellHistograms(ncells);
  std::vector<cv::Mat_<float>> cellSignedHistograms(ncells);
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < ncells; ++i) {
    cellHistograms[i].create(1, mNumberOfBins);
    cellHistograms[i] = FLT_MAX;
    cellSignedHistograms[i].create(1, signedBins);
    cellSignedHistograms[i] = FLT_MAX;
  }
  int cell_it = 0;
  for (int cellRow = 0; cellRow < ncells_rows; ++cellRow) {
    for (int cellCol = 0; cellCol < ncells_cols; ++cellCol) {
      const int a = rowOffset + cellRow * cellWidth;
      const int b = colOffset + cellHeight * cellCol;
      const int w = cellWidth - 1;
      const int h = cellHeight - 1;

      for (int bin = 0; bin < mNumberOfBins; ++bin) {
        auto integralImage = integralImages[bin];

        double v1 = integralImage[a][b];
        double v2 = integralImage[a][b + w];
        double v3 = integralImage[a + h][b];
        double v4 = integralImage[a + h][b + w];

        float value = static_cast<float>(v1 + v4 - (v2 + v3));
        cellHistograms[cell_it][0][bin] = value;
      }

      for (int bin = 0; bin < signedBins; ++bin) {
        auto integralImage = signedIntegralImages[bin];
        double v1 = integralImage[a][b];
        double v2 = integralImage[a][b + w];
        double v3 = integralImage[a + h][b];
        double v4 = integralImage[a + h][b + w];

        float value = static_cast<float>(v1 + v4 - (v2 + v3));
        cellSignedHistograms[cell_it][0][bin] = value;
      }
      ++cell_it;
    }
  }

  cv::Mat_<float> signed_ans, unsigned_ans;

  for (const auto& hist : cellHistograms) {
    if (unsigned_ans.empty())
      unsigned_ans = hist;
    else
      cv::hconcat(unsigned_ans.clone(), hist, unsigned_ans);
  }
  unsigned_ans = normalizeBlock(unsigned_ans);
  for (const auto& hist : cellSignedHistograms) {
    if (signed_ans.empty())
      signed_ans = hist;
    else
      cv::hconcat(signed_ans.clone(), hist, signed_ans);
  }
  signed_ans = normalizeBlock(signed_ans);

  cv::Mat_<float> signed_avg(1, signedBins),
    unsigned_avg(1, mNumberOfBins);

  cv::Mat_<float> l1norms(1, ncells, 0.f);
  for (int i = 0; i < mNumberOfBins; ++i) {
    unsigned_avg.at<float>(i) = unsigned_ans.at<float>(i);
    unsigned_avg.at<float>(i) += unsigned_ans.at<float>(i + mNumberOfBins);
    unsigned_avg.at<float>(i) += unsigned_ans.at<float>(i + 2 * mNumberOfBins);
    unsigned_avg.at<float>(i) += unsigned_ans.at<float>(i + 3 * mNumberOfBins);

    l1norms.at<float>(0) += unsigned_ans.at<float>(i);
    l1norms.at<float>(1) += unsigned_ans.at<float>(i + mNumberOfBins);
    l1norms.at<float>(2) += unsigned_ans.at<float>(i + 2 * mNumberOfBins);
    l1norms.at<float>(3) += unsigned_ans.at<float>(i + 3 * mNumberOfBins);
  }
  unsigned_avg = unsigned_avg * 0.25f;

  for (int i = 0; i < signedBins; ++i) {
    signed_avg.at<float>(i) = signed_ans.at<float>(i);
    signed_avg.at<float>(i) += signed_ans.at<float>(i + signedBins);
    signed_avg.at<float>(i) += signed_ans.at<float>(i + 2 * signedBins);
    signed_avg.at<float>(i) += signed_ans.at<float>(i + 3 * signedBins);
  }
  signed_avg = signed_avg * 0.25f;

  cv::hconcat(unsigned_avg, signed_avg, out);
  cv::hconcat(out.clone(), l1norms, out);
}

std::vector<cv::Mat_<double>> HOGUOCCTI::computeIntegralGradientImages(
  const cv::Mat& img,
  bool signedGradient) const {
  cv::HOGDescriptor hogCalculator;
  cv::Mat grad, angleOfs;
  int rows, cols = 0;
  std::vector<cv::Mat_<double>> integralImages;

  hogCalculator.gammaCorrection = mGammaCorrection;
  hogCalculator.signedGradient = signedGradient;
  const int nbins = signedGradient?2 * mNumberOfBins : mNumberOfBins;;
  hogCalculator.nbins = nbins;

  hogCalculator.computeGradient(img, grad, angleOfs);

  rows = img.rows , cols = img.cols;
  integralImages.resize(nbins);
  for (int bin = 0; bin < nbins; ++bin) {
    integralImages[bin] = cv::Mat::zeros(rows, cols, CV_64F);
  }
  std::vector<cv::Mat_<uint8_t>> angles;
  std::vector<cv::Mat_<float>> gradients;
  cv::split(grad, gradients);
  cv::split(angleOfs, angles);

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < grad.rows; ++i) {
    for (int j = 0; j < grad.cols; ++j) {
      for (int k = 0; k < 2; ++k) {
        auto angle = angles[k];
        auto bin = (angle.at<uint8_t>(i, j));
        auto bingrad = gradients[k];
        float mag = bingrad[i][j];

        int centerCol = static_cast<int>(j / 8) + 4;
        int centerRow = static_cast<int>(i / 8) + 4;
        cv::Mat_<int> centerRows = (cv::Mat_<int>(1, 5) <<
          centerRow , centerRow - 8 , centerRow + 8 , centerRow , centerRow);
        cv::Mat_<int> centerCols = (cv::Mat_<int>(1, 5) <<
          centerCol , centerCol , centerCol , centerCol - 8 , centerCol + 8);


        /* This mat stores the values of the distance of
        the current pixel to each cell center
        The order of the centers are center, top, bottom, left, right*/
        cv::Mat_<float> centerDistances(1, 5, 0.f);
        const int CENTER = 0, TOP = 1, BOTTOM = 2, LEFT = 3, RIGHT = 4;

        for (int n = 1; n < 5; ++n) {
          centerDistances.at<float>(n) = static_cast<float>(
            (centerRows.at<int>(n) - centerRow) *
            (centerRows.at<int>(n) - centerRow));
          centerDistances.at<float>(n) += static_cast<float>(
            (centerCols.at<int>(n) - centerCol) *
            (centerCols.at<int>(n) - centerCol));
          centerDistances.at<float>(n) = cv::sqrt(centerDistances.at<float>(n));
        }
        cv::normalize(centerDistances, centerDistances, 1, 0, cv::NORM_L1);
        centerDistances = 1 - centerDistances;
        cv::normalize(centerDistances, centerDistances, 1, 0, cv::NORM_L1);

        integralImages[bin][i][j] += mag *
          centerDistances.at<float>(CENTER);
        if (i >= 0 && i < img.rows && j + 8 >= 0 && j + 8 < img.cols)
          integralImages[bin][i][j + 8] += mag *
            centerDistances.at<float>(TOP);
        if (i >= 0 && i < img.rows && j - 8 >= 0 && j - 8 < img.cols)
          integralImages[bin][i][j - 8] += mag *
            centerDistances.at<float>(BOTTOM);
        if (i + 8 >= 0 && i + 8 < img.rows && j >= 0 && j < img.cols)
          integralImages[bin][i + 8][j] += mag *
            centerDistances.at<float>(LEFT);
        if (i - 8 >= 0 && i - 8 < img.rows && j >= 0 && j < img.cols)
          integralImages[bin][i - 8][j] += mag *
            centerDistances.at<float>(RIGHT);
      }
    }
  }

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int bin = 0; bin < nbins; ++bin) {
    cv::Mat intImage;
    auto bingrad = integralImages[bin];
    cv::integral(integralImages[bin], intImage, CV_64F);
    intImage =
      intImage(cv::Range(1, intImage.rows), cv::Range(1, intImage.cols));
    intImage.copyTo(integralImages[bin]);
  }
  return integralImages;
}

cv::Mat HOGUOCCTI::normalizeBlock(const cv::Mat_<float>& blockFeat) const {
  // L2Hys
  cv::Mat_<float> ans;
  float l2norm = static_cast<float>(cv::norm(blockFeat, cv::NORM_L2));
  float scale = 1.f / (l2norm + blockFeat.cols * 0.1f);
  ans = blockFeat * scale;
  if (mClipping > 0) {
    ans = cv::min(ans, mClipping);
  }

  l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  scale = 1.f / (l2norm + 1e-3f);
  ans = ans * scale;

  return ans;
}

// getter setters
cv::Size HOGUOCCTI::getBlockConfiguration() const {
  return mBlockConfiguration;
}

void HOGUOCCTI::setBlockConfiguration(const cv::Size& blockConfiguration) {
  mBlockConfiguration = blockConfiguration;
}

cv::Size HOGUOCCTI::getBlockStride() const {
  return mBlockStride;
}

void HOGUOCCTI::setBlockStride(const cv::Size& blockStride) {
  mBlockStride = blockStride;
}

cv::Size HOGUOCCTI::getCellConfiguration() const {
  return mCellConfiguration;
}

void HOGUOCCTI::setCellConfiguration(const cv::Size& cellConfiguration) {
  mCellConfiguration = cellConfiguration;
}

int HOGUOCCTI::getNumberOfBins() const {
  return mNumberOfBins;
}

void HOGUOCCTI::setNumberOfBins(int numberOfBins) {
  mNumberOfBins = numberOfBins;
}

float HOGUOCCTI::getClipping() const {
  return mClipping;
}

void HOGUOCCTI::setClipping(float clipping1) {
  mClipping = clipping1;
}

void HOGUOCCTI::read(const cv::FileNode& fn) {}

void HOGUOCCTI::write(cv::FileStorage& fs) const {}
}  // namespace ssig


