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
#include <opencv2/objdetect.hpp>
#include "algorithms/hog_features.hpp"
#include <opencv2/imgproc.hpp>

namespace ssf{

DescriptorInterface* HOG::clone() const{
  auto copy = new HOG;

  copy->setBlockConfiguration(getBlockConfiguration());
  copy->setCellConfiguration(getCellConfiguration());
  copy->setNumberOfBins(getNumberOfBins());

  return copy;
}

void HOG::extract(const cv::Mat& img, cv::Mat& out){ }

bool HOG::hasVisualization(){
  return true;
}

void HOG::extract(const cv::Mat& img, cv::Mat& out, cv::Mat& visualization){
  cv::Mat gradImg, angleOfs;

  auto integralImages = getIntegralGradientImage(img);
  const int blocksPerRows = img.rows / mBlockConfiguration.height;
  const int blocksPerCols = img.cols / mBlockConfiguration.width;
  const int nblocks = blocksPerCols * blocksPerRows;
  const int nCellsPerBlock = mCellConfiguration.area();
  const int dimensionsPerBlock = mNumberOfBins * nCellsPerBlock;
  out.create(1, dimensionsPerBlock * nblocks, CV_32F);
  out = 0;
  visualization.create(img.rows, img.cols, CV_8UC1);
  int blockNumber = 0;
  for(int row = 0; row < img.rows; row += mBlockConfiguration.height){
    for(int col = 0; col < img.cols; col += mBlockConfiguration.width){
      cv::Mat_<float> cellDescriptor;
      getCellDescriptor(row, col, integralImages, cellDescriptor);

      auto blockFeat = out(
        cv::Range(0, 1),
        cv::Range(
          blockNumber * dimensionsPerBlock,
          (blockNumber + 1) * dimensionsPerBlock));
      cellDescriptor.copyTo(blockFeat);
      ++blockNumber;

      cv::Mat blockVisualization = visualization(
        cv::Rect(col, row, mBlockConfiguration.width, mBlockConfiguration.height));
      generateBlockVisualization(blockFeat, blockVisualization);
    }
  }
}

std::vector<cv::Mat_<float>> HOG::getIntegralGradientImage(const cv::Mat& img) const{
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
    intImage.convertTo(integralImages[bin], CV_32F);
  }
  return integralImages;
}

void HOG::getCellDescriptor(int rowOffset, int colOffset, const std::vector<cv::Mat_<float>>& integralImages, cv::Mat_<float>& out){
  const int blockWidth = mBlockConfiguration.width;
  const int blockHeight = mBlockConfiguration.height;
  int ncells_cols = mCellConfiguration.width, ncells_rows = mCellConfiguration.height;

  const int cellWidth = static_cast<int>(blockWidth / static_cast<float>(ncells_cols));
  const int cellHeight = static_cast<int>(blockHeight / static_cast<float>(ncells_rows));

  cv::Mat_<float> ans;
  ans = cv::Mat_<float>::zeros(1, mNumberOfBins * ncells_cols * ncells_rows);
  for(int cellRow = 0; cellRow < ncells_rows; ++cellRow){
    for(int cellCol = 0; cellCol < ncells_cols; ++cellCol){
      const int binOffset = ncells_rows * cellRow + cellCol;
      const int a = rowOffset + cellRow * cellWidth;
      const int b = colOffset + cellHeight * cellCol;
      const int w = cellWidth;
      const int h = cellHeight;

      for(int bin = 0; bin < mNumberOfBins; ++bin){
        auto integralImage = integralImages[bin];
        ans[0][bin + (binOffset * mNumberOfBins)] =
          integralImage[a][b] + integralImage[a + h][b + w] - (integralImage[a][b + w] + integralImage[a + h][b]);
      }
    }
  }
  float l2norm = static_cast<float>(cv::norm(ans, cv::NORM_L2));
  ans = ans / (l2norm + FLT_EPSILON);
  cv::checkRange(ans, false);
  out = ans;
}

void HOG::generateBlockVisualization(const cv::Mat_<float>& blockFeatures, cv::Mat& visualization){
  visualization = 0;
  const float PI = 3.14159265f;
  cv::Mat_<float> vector(1, mNumberOfBins);
  vector = 0;
  for(int d = 0; d < blockFeatures.cols; ++d){
    int col = d % mNumberOfBins;
    vector[0][col] += blockFeatures[0][d];
  }

  for(int d = 0; d < mNumberOfBins; ++d){
    float r = vector[0][d] * (visualization.rows / 2);

    float theta = static_cast<float>(d * PI) / mNumberOfBins;

    const int x1 = static_cast<int>(visualization.cols / 2 + r * cos(theta));
    const int y1 = static_cast<int>(visualization.rows / 2 + r * sin(theta));
    const int x2 = static_cast<int>(visualization.cols / 2 + r * cos(theta + PI));
    const int y2 = static_cast<int>(visualization.rows / 2 + r * sin(theta + PI));

    if(r > 0){
      cv::line(visualization,
               cv::Point(x1, y1),
               cv::Point(x2, y2),
               cv::Scalar(255, 255, 255),
               1);
    }

  }
}


//getter setters
cv::Size HOG::getBlockConfiguration() const{
  return mBlockConfiguration;
}

void HOG::setBlockConfiguration(const cv::Size& blockConfiguration){
  mBlockConfiguration = blockConfiguration;
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
}
