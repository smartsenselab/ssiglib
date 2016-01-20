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


#ifdef _OPENMP
#include <omp.h>
#endif

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "descriptors/hog_features.hpp"
#include "core/exception.hpp"

namespace ssig {


HOG::HOG(const cv::Mat& input) : Descriptor2D(input) {}

HOG::HOG(const cv::Mat& input, const ssig::HOG& descriptor)
  : Descriptor2D(input, descriptor) {
  mBlockConfiguration = descriptor.getBlockConfiguration();
  mBlockStride = descriptor.getBlockStride();
  mCellConfiguration = descriptor.getCellConfiguration();
  mClipping = descriptor.getClipping();
  mNumberOfBins = descriptor.getNumberOfBins();
}

HOG::HOG(const ssig::HOG& descriptor) : Descriptor2D(descriptor) {
  mBlockConfiguration = descriptor.getBlockConfiguration();
  mBlockStride = descriptor.getBlockStride();
  mCellConfiguration = descriptor.getCellConfiguration();
  mClipping = descriptor.getClipping();
  mNumberOfBins = descriptor.getNumberOfBins();
}

// void HOG::computeGradient(
//  const cv::Mat& img,
//  std::vector<cv::Mat_<double>>& magnitudes,
//  std::vector<cv::Mat_<uint8_t>>& binnings) const {
//  cv::Mat dy = img.clone(), dx = img.clone();
//  cv::Mat_<float> kernelX = (cv::Mat_<float>(1, 3) << -1 , 0 , 1);
//  cv::Mat_<float> kernelY = (cv::Mat_<float>(3, 1) << -1 , 0 , 1);
//  cv::filter2D(mImage, dx, CV_32F, kernelX);
//  cv::filter2D(mImage, dy, CV_32F, kernelX);
//
//  magnitudes.clear();
//  magnitudes.resize(2);
//  binnings.clear();
//  binnings.resize(2);
//  for (int i = 0; i < 2; ++i) {
//    magnitudes[i].create(img.rows, img.cols);
//    binnings[i].create(img.rows, img.cols);
//  }
//
//  cv::Mat_<float> gradient(img.rows, img.cols, 0.f);
//
//  std::vector<cv::Mat> dxs, dys;
//  cv::split(dx, dxs);
//  cv::split(dy, dys);
//
//  std::vector<cv::Mat_<float>> gradients(img.channels());
//  for (int c = 0; c < img.channels(); ++c) {
//    cv::Mat localdx, localdy;
//    cv::pow(dxs[c], 2, localdx);
//    cv::pow(dys[c], 2, localdy);
//
//    cv::Mat g = localdy + localdx;
//    cv::sqrt(g.clone(), g);
//    gradients[c] = g;
//    gradient = cv::max(gradient, g);
//  }
//
//  const float angleRange = mSignedGradient?360.f : 180.f;
//  const float binSize = angleRange / mNumberOfBins;
//  for (int i = 0; i < img.rows; ++i) {
//    for (int j = 0; j < img.cols; ++j) {
//      float x = -FLT_MAX, y = -FLT_MAX;
//      float gradientValue = -FLT_MAX;
//      for(int c = 0; c < img.channels(); ++c) {
//        if(gradients[c][i][j] > gradientValue) {
//          x = dxs[c].at<float>(i,j);
//          y = dys[c].at<float>(i,j);
//        }
//      }
//      float angle = cv::fastAtan2(x, y);
//      if (!mSignedGradient) {
//        angle = angle >= 180?angle - 180 : angle;
//      }
//
//
//      const float bin = angle / binSize;
//      const float remainder = bin - floor(bin);
//
//      binnings[0][i][j] = static_cast<uint8_t>(bin);
//      binnings[1][i][j] = static_cast<uint8_t>(bin + 1) % mNumberOfBins;
//
//      magnitudes[0][i][j] = gradient[i][j] * (1 - remainder);
//      magnitudes[1][i][j] = gradient[i][j] * (remainder);
//
//    }
//  }
//  cv::Mat g, b;
//  cv::merge(magnitudes, g);
//  cv::merge(binnings, b);
//}

std::vector<cv::Mat_<double>> HOG::computeIntegralGradientImages(
  const cv::Mat& img) const {
  cv::HOGDescriptor hogCalculator;
  cv::Mat grad, angleOfs;
  int rows, cols = 0;
  std::vector<cv::Mat_<double>> integralImages;

  hogCalculator.gammaCorrection = mGammaCorrection;
  hogCalculator.signedGradient = mSignedGradient;
  hogCalculator.nbins = mNumberOfBins;

  hogCalculator.computeGradient(img, grad, angleOfs);

  rows = img.rows , cols = img.cols;
  integralImages.resize(mNumberOfBins);
  for (int bin = 0; bin < mNumberOfBins; ++bin) {
    integralImages[bin] = cv::Mat::zeros(rows, cols, CV_64F);
  }
  std::vector<cv::Mat_<uint8_t>> angles;
  std::vector<cv::Mat_<float>> gradients;
  cv::split(grad, gradients);
  cv::split(angleOfs, angles);

  const int cellWidth = mBlockConfiguration.width / mCellConfiguration.width;
  const int cellHeight = mBlockConfiguration.height / mCellConfiguration.height;

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

        int centerCol = static_cast<int>(j / cellWidth) + 4;
        int centerRow = static_cast<int>(i / cellHeight) + 4;
        cv::Mat_<int> centerRows = (cv::Mat_<int>(1, 5) <<
          centerRow , centerRow - cellHeight ,
          centerRow + cellHeight , centerRow , centerRow);
        cv::Mat_<int> centerCols = (cv::Mat_<int>(1, 5) <<
          centerCol , centerCol , centerCol ,
          centerCol - cellWidth , centerCol + cellWidth);


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
        if (i >= 0 && i < img.rows
          && j + cellWidth >= 0
          && j + cellWidth < img.cols)
          integralImages[bin][i][j + 8] += mag *
            centerDistances.at<float>(TOP);
        if (i >= 0 && i < img.rows
          && j - cellWidth >= 0
          && j - cellWidth < img.cols)
          integralImages[bin][i][j - 8] += mag *
            centerDistances.at<float>(BOTTOM);
        if (i + cellHeight >= 0 &&
          i + cellHeight < img.rows &&
          j >= 0 && j < img.cols)
          integralImages[bin][i + 8][j] += mag *
            centerDistances.at<float>(LEFT);
        if (i - cellHeight >= 0 &&
          i - cellHeight < img.rows &&
          j >= 0 &&
          j < img.cols)
          integralImages[bin][i - 8][j] += mag *
            centerDistances.at<float>(RIGHT);
      }
    }
  }

#ifdef _OPENMP
  #pragma omp parallel for
#endif
  for (int bin = 0; bin < mNumberOfBins; ++bin) {
    cv::Mat intImage;
    auto bingrad = integralImages[bin];
    cv::integral(integralImages[bin], intImage, CV_64F);
    intImage =
      intImage(cv::Range(1, intImage.rows), cv::Range(1, intImage.cols));
    intImage.copyTo(integralImages[bin]);
  }
  return integralImages;
}

void HOG::extractFeatures(const cv::Rect& patch, cv::Mat& output) {
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
      computeBlockDescriptor(row, col, mIntegralImages, cellDescriptor);

      if (output.empty()) {
        output = cellDescriptor;
      } else {
        cv::hconcat(output.clone(), cellDescriptor, output);
      }
    }
  }
}

void HOG::computeBlockDescriptor(
  int rowOffset,
  int colOffset,
  const std::vector<cv::Mat_<double>>& integralImages,
  cv::Mat_<float>& out) const {
  const int blockWidth = mBlockConfiguration.width;
  const int blockHeight = mBlockConfiguration.height;
  int ncells_cols = mCellConfiguration.width,
    ncells_rows = mCellConfiguration.height;

  const int cellWidth =
    static_cast<int>(blockWidth / static_cast<float>(ncells_cols));
  const int cellHeight =
    static_cast<int>(blockHeight / static_cast<float>(ncells_rows));

  cv::Mat_<float> ans;
  const int ncells = ncells_cols * ncells_rows;
  std::vector<cv::Mat_<float>> cellsHist(ncells);
  for (int c = 0; c < ncells; ++c)
    cellsHist[c] = cv::Mat_<float>::zeros(1, mNumberOfBins);

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


        cellsHist[cell_it].at<float>(bin) = value;
      }
      ++cell_it;
    }
  }
  for (const auto& hist : cellsHist) {
    if (ans.empty())
      ans = hist;
    else
      cv::hconcat(ans.clone(), hist, ans);
  }

  // L2Hys
  float l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  float scale = 1.f / (l2norm + ans.cols * 0.1f);
  ans = ans * scale;
  if (mClipping > 0) {
    ans = cv::min(ans, mClipping);
  }

  l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  scale = 1.f / (l2norm + 1e-3f);
  ans = ans * scale;
  cv::checkRange(ans, false);
  out = ans;
}

void HOG::generateBlockVisualization(const cv::Mat_<float>& blockFeatures,
                                     const int nBins, cv::Mat& visualization) {
  visualization = 255;
  const float PI = 3.14159265f;
  cv::Mat_<float> vector(1, nBins);
  vector = 0;
  for (int d = 0; d < blockFeatures.cols; ++d) {
    int col = d % nBins;
    vector[0][col] += blockFeatures[0][d];
  }

  for (int d = 0; d < nBins; ++d) {
    float r = vector[0][d];
    r = r * (visualization.rows / 2);

    float theta = static_cast<float>(d * PI) / nBins;

    const int x1 = static_cast<int>(visualization.cols / 2 + r * cos(theta));
    const int y1 = static_cast<int>(visualization.rows / 2 + r * sin(theta));
    const int x2 =
      static_cast<int>(visualization.cols / 2 + r * cos(theta + PI));
    const int y2 =
      static_cast<int>(visualization.rows / 2 + r * sin(theta + PI));

    if (r > 0.1f) {
      cv::line(visualization, cv::Point(x1, y1), cv::Point(x2, y2),
               cv::Scalar(0, 0, 0), 1);
    }
  }
  cv::flip(visualization, visualization, 1);
}

// getter setters
cv::Size HOG::getBlockConfiguration() const {
  return mBlockConfiguration;
}

void HOG::setBlockConfiguration(const cv::Size& blockConfiguration) {
  mBlockConfiguration = blockConfiguration;
}

cv::Size HOG::getBlockStride() const {
  return mBlockStride;
}

void HOG::setBlockStride(const cv::Size& blockStride) {
  mBlockStride = blockStride;
}

cv::Size HOG::getCellConfiguration() const {
  return mCellConfiguration;
}

void HOG::setCellConfiguration(const cv::Size& cellConfiguration) {
  mCellConfiguration = cellConfiguration;
}

int HOG::getNumberOfBins() const {
  return mNumberOfBins;
}

void HOG::setNumberOfBins(int numberOfBins) {
  mNumberOfBins = numberOfBins;
}

float HOG::getClipping() const {
  return mClipping;
}

void HOG::setClipping(float clipping1) {
  mClipping = clipping1;
}

bool HOG::getGammaCorrection() const {
  return mGammaCorrection;
}

void HOG::setGammaCorrection(const bool gammaCorrection) {
  mGammaCorrection = gammaCorrection;
}

bool HOG::getSignedGradient() const {
  return mSignedGradient;
}

void HOG::setSignedGradient(const bool signedGradient) {
  mSignedGradient = signedGradient;
}

void HOG::beforeProcess() {
  if (mImage.empty())return;
  mIntegralImages = computeIntegralGradientImages(mImage);
}

void HOG::computeVisualization(const cv::Mat_<float> feat,
                               const int nBins,
                               const cv::Size& blockSize,
                               const cv::Size& blockStride,
                               const cv::Size& cellSize,
                               const cv::Size& imgSize,
                               cv::Mat& visualization) {
  const int imgRows = imgSize.height;
  const int imgCols = imgSize.width;

  if (imgCols % blockSize.width != 0) {
    throw Exception("Patch size must be multiple of block size");
  }
  if (imgRows % blockSize.height != 0) {
    throw Exception("Patch size must be multiple of block size");
  }

  const int nCellsPerBlock = cellSize.area();
  const int dimensionsPerBlock = nBins * nCellsPerBlock;

  visualization.create(imgRows, imgCols, CV_8UC1);
  visualization = 255;
  int blockNumber = 0;
  for (int row = 0; row < imgRows; row += blockStride.height) {
    for (int col = 0; col < imgCols; col += blockStride.width) {
      auto blockFeat = feat(cv::Range(0, 1),
                            cv::Range(blockNumber * dimensionsPerBlock,
                                      (blockNumber + 1) * dimensionsPerBlock));
      ++blockNumber;

      cv::Mat blockVisualization =
        visualization(cv::Rect(col, row, blockSize.width, blockSize.height));
      generateBlockVisualization(blockFeat, nBins, blockVisualization);
    }
  }
}

}  // namespace ssig


