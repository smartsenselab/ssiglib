/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include "algorithms/hog_features.hpp"


namespace ssf{

HOG::HOG(const cv::Mat& input):DescriptorInterface(input){
  mIntegralImages = computeIntegralGradientImages(mImage);
}

HOG::HOG(const cv::Mat& input, const cv::Rect& patch) : DescriptorInterface(input, patch){
  mIntegralImages = computeIntegralGradientImages(mImage);
}

HOG::HOG(const cv::Mat& input, const std::vector<cv::Rect>& patches) :
  DescriptorInterface(input, patches){
  mIntegralImages = computeIntegralGradientImages(mImage);
}

void HOG::computeVisualization(const cv::Mat_<float> feat,
                               const int nBins,
                               const cv::Size& blockSize,
                               const cv::Size& blockStride,
                               const cv::Size& cellSize,
                               const cv::Size& imgSize,
                               cv::Mat& visualization){
  const int imgRows = imgSize.height;
  const int imgCols = imgSize.width;

  if(imgCols % blockSize.width != 0){
    throw std::invalid_argument("Patch size must be multiple of block size");
  }
  if(imgRows % blockSize.height != 0){
    throw std::invalid_argument("Patch size must be multiple of block size");
  }

  const int nCellsPerBlock = cellSize.area();
  const int dimensionsPerBlock = nBins * nCellsPerBlock;

  visualization.create(imgRows, imgCols, CV_8UC1);
  visualization = 255;
  int blockNumber = 0;
  for(int row = 0; row < imgRows; row += blockStride.height){
    for(int col = 0; col < imgCols; col += blockStride.width){
      auto blockFeat = feat(
        cv::Range(0, 1),
        cv::Range(
          blockNumber * dimensionsPerBlock,
          (blockNumber + 1) * dimensionsPerBlock));
      ++blockNumber;

      cv::Mat blockVisualization = visualization(
        cv::Rect(col, row, blockSize.width, blockSize.height));
      generateBlockVisualization(blockFeat, nBins, blockVisualization);
    }
  }
}

std::vector<cv::Mat_<float>> HOG::computeIntegralGradientImages(const cv::Mat& img) const{
  cv::HOGDescriptor hogCalculator;
  cv::Mat grad, angleOfs;
  int rows, cols = 0;
  std::vector<cv::Mat_<float>> integralImages;
  hogCalculator.computeGradient(img, grad, angleOfs);
  rows = img.rows , cols = img.cols;
  integralImages.resize(9);
  for(int bin = 0; bin < 9; ++bin){
    integralImages[bin] = cv::Mat::zeros(rows, cols, CV_32F);
  }
  std::vector<cv::Mat_<uint8_t>> angles;
  std::vector<cv::Mat_<float>> gradients;
  cv::split(grad, gradients);
  cv::split(angleOfs, angles);
  for(int i = 0; i < grad.rows; ++i){
    for(int j = 0; j < grad.cols; ++j){
      for(int k = 0; k < 2; ++k){
        auto angle = angles[k];
        auto bin = (angle.at<uint8_t>(i, j));
        auto bingrad = gradients[k];
        float mag = bingrad[i][j];
        integralImages[bin][i][j] += mag;
      }
    }
  }
  for(int bin = 0; bin < 9; ++bin){
    cv::Mat intImage;
    auto bingrad = integralImages[bin];
    cv::integral(integralImages[bin], intImage);
    intImage = intImage(cv::Range(1, intImage.rows), cv::Range(1, intImage.cols));
    intImage.convertTo(integralImages[bin], CV_32F);
  }
  return integralImages;
}

void HOG::getBlockDescriptor(int rowOffset, int colOffset, const std::vector<cv::Mat_<float>>& integralImages, cv::Mat_<float>& out){
  const int blockWidth = mBlockConfiguration.width;
  const int blockHeight = mBlockConfiguration.height;
  int ncells_cols = mCellConfiguration.width, ncells_rows = mCellConfiguration.height;

  const int cellWidth = static_cast<int>(blockWidth / static_cast<float>(ncells_cols));
  const int cellHeight = static_cast<int>(blockHeight / static_cast<float>(ncells_rows));

  cv::Mat_<float> ans;
  ans.create(1, mNumberOfBins * ncells_cols * ncells_rows);
  ans = FLT_MAX ;
  for(int cellRow = 0; cellRow < ncells_rows; ++cellRow){
    for(int cellCol = 0; cellCol < ncells_cols; ++cellCol){
      const int binOffset = ncells_rows * cellRow + cellCol;
      const int a = rowOffset + cellRow * cellWidth;
      const int b = colOffset + cellHeight * cellCol;
      const int w = cellWidth - 1;
      const int h = cellHeight - 1;

      for(int bin = 0; bin < mNumberOfBins; ++bin){
        auto integralImage = integralImages[bin];
        float v1 = integralImage[a][b];
        float v2 = integralImage[a][b + w];
        float v3 = integralImage[a + h][b];
        float v4 = integralImage[a + h][b + w];

        float value = std::max(v1 + v4 - (v2 + v3), 0.0f);
        ans[0][bin + (binOffset * mNumberOfBins)] = value;
      }
    }
  }

  //L2Hys
  float l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  ans = ans / (cv::sqrt(l2norm * l2norm + 0.1f));
  cv::checkRange(ans, false, nullptr, 0.0, FLT_MAX);
  if(mClipping > 0){
    for(int i = 0; i < ans.cols; i++){
      ans[0][i] = std::min(ans[0][i], mClipping);
    }
  }
  cv::checkRange(ans, false, nullptr, 0.0, mClipping + FLT_EPSILON);
  l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  ans = ans / (cv::sqrt(l2norm * l2norm + 0.1f));
  cv::checkRange(ans, false);
  out = ans;
}

void HOG::generateBlockVisualization(const cv::Mat_<float>& blockFeatures,
                                     const int nBins,
                                     cv::Mat& visualization){
  visualization = 255;
  const float PI = 3.14159265f;
  cv::Mat_<float> vector(1, nBins);
  vector = 0;
  for(int d = 0; d < blockFeatures.cols; ++d){
    int col = d % nBins;
    vector[0][col] += blockFeatures[0][d];
  }

  for(int d = 0; d < nBins; ++d){
    float r = vector[0][d];
    r = r * (visualization.rows / 2);

    float theta = static_cast<float>(d * PI) / nBins;

    const int x1 = static_cast<int>(visualization.cols / 2 + r * cos(theta));
    const int y1 = static_cast<int>(visualization.rows / 2 + r * sin(theta));
    const int x2 = static_cast<int>(visualization.cols / 2 + r * cos(theta + PI));
    const int y2 = static_cast<int>(visualization.rows / 2 + r * sin(theta + PI));

    if(r > 0.1f){
      cv::line(visualization,
               cv::Point(x1, y1),
               cv::Point(x2, y2),
               cv::Scalar(0, 0, 0),
               1);
    }
  }
  cv::flip(visualization, visualization, 1);
}


bool HOG::hasNext(){
  return !mPatches.empty();
}

void HOG::nextFeatureVector(cv::Mat& out){
  auto& patch = mPatches.back();

  const int imgRows = patch.height;
  const int imgCols = patch.width;

  if(imgCols % mBlockConfiguration.width != 0){
    throw std::invalid_argument("Patch size must be multiple of block size");
  }
  if(imgRows % mBlockConfiguration.height != 0){
    throw std::invalid_argument("Patch size must be multiple of block size");
  }

  const int blocksPerRows = imgRows / (mBlockStride.height);
  const int blocksPerCols = imgCols / mBlockStride.width;
  const int nblocks = blocksPerCols * blocksPerRows;
  const int nCellsPerBlock = mCellConfiguration.area();
  const int dimensionsPerBlock = mNumberOfBins * nCellsPerBlock;
  out.create(1, dimensionsPerBlock * nblocks, CV_32F);
  out = 0;
  int blockNumber = 0;
  /*cv::HOGDescriptor hog({mImg.rows, mImg.cols}, mBlockConfiguration,
  mBlockConfiguration, mBlockConfiguration, 9);
  std::vector<float> descriptors;
  hog.compute(mImg, descriptors);
  out = cv::Mat_<float>(1, static_cast<int>(descriptors.size()), descriptors.data());
  */
  for(int row = 0; row < imgRows; row += mBlockStride.height){
    for(int col = 0; col < imgCols; col += mBlockStride.width){
      cv::Mat_<float> cellDescriptor;
      getBlockDescriptor(row, col, mIntegralImages, cellDescriptor);

      auto blockFeat = out(
        cv::Range(0, 1),
        cv::Range(
          blockNumber * dimensionsPerBlock,
          (blockNumber + 1) * dimensionsPerBlock));
      ++blockNumber;
      cellDescriptor.copyTo(blockFeat);
    }
  }
  mPatches.pop_back();
}

void HOG::save(const std::string& filename, const std::string& nodename) const{
  //TODO: save
}

void HOG::load(const std::string& filename, const std::string& nodename){
  //TODO: load
}

//getter setters
cv::Size HOG::getBlockConfiguration() const{
  return mBlockConfiguration;
}

void HOG::setBlockConfiguration(const cv::Size& blockConfiguration){
  mBlockConfiguration = blockConfiguration;
}

cv::Size HOG::getBlockStride() const{
  return mBlockStride;
}

void HOG::setBlockStride(const cv::Size& blockStride){
  mBlockStride = blockStride;
}

cv::Size HOG::getCellConfiguration() const{
  return mCellConfiguration;
}

void HOG::setCellConfiguration(const cv::Size& cellConfiguration){
  mCellConfiguration = cellConfiguration;
}

int HOG::getNumberOfBins() const{
  return mNumberOfBins;
}

void HOG::setNumberOfBins(int numberOfBins){
  mNumberOfBins = numberOfBins;
}

float HOG::getClipping() const{
  return mClipping;
}

void HOG::setClipping(float clipping1){
  mClipping = clipping1;
}
}
