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

#include "descriptors/haralick.hpp"

#include <vector>

namespace ssig {

cv::Mat Haralick::compute(const cv::Mat& mat) {
  cv::Mat output = cv::Mat::zeros(1, 15, CV_32F);

  output.at<float>(0, 0) = Haralick::f1ASM(mat);
  output.at<float>(0, 1) = Haralick::f2Contrast(mat);
  output.at<float>(0, 2) = Haralick::f3Correlation(mat);
  output.at<float>(0, 3) = Haralick::f4Variance(mat);
  output.at<float>(0, 4) = Haralick::f5IDM(mat);
  output.at<float>(0, 5) = Haralick::f6SumAverage(mat);
  output.at<float>(0, 6) = Haralick::f7SumVariance(mat);
  output.at<float>(0, 7) = Haralick::f8SumEntropy(mat);
  output.at<float>(0, 8) = Haralick::f9Entropy(mat);
  output.at<float>(0, 9) = Haralick::f10DifferenceVariance(mat);
  output.at<float>(0, 10) = Haralick::f11DifferenceEntropy(mat);
  output.at<float>(0, 11) = Haralick::f12InformationCorrelation01(mat);
  output.at<float>(0, 12) = Haralick::f13InformationCorrelation02(mat);
  output.at<float>(0, 13) = 0.0f;
  output.at<float>(0, 14) = Haralick::f15_Dierctionality(mat);

  for (int i = 0; i < 15; i++)
    if (isnan(output.at<float>(0, i))) output.at<float>(0, i) = 0.0f;

  return output;
}

cv::Mat Haralick::computeOld(const cv::Mat& mat) {
	//Compute just 12 features (old implementaion from William Schwartz)
	cv::Mat output = cv::Mat::zeros(1, 12, CV_32F);

	output.at<float>(0, 0) = Haralick::f1ASM(mat);
	output.at<float>(0, 1) = Haralick::f2Contrast(mat);
	output.at<float>(0, 2) = Haralick::f3Correlation(mat);
	output.at<float>(0, 3) = Haralick::f4Variance(mat);
	output.at<float>(0, 4) = Haralick::f5IDM(mat);
	output.at<float>(0, 5) = Haralick::f6SumAverage(mat);
	output.at<float>(0, 6) = Haralick::f7SumVariance(mat);
	output.at<float>(0, 7) = Haralick::f8SumEntropy(mat);
	output.at<float>(0, 8) = Haralick::f9Entropy(mat);
	output.at<float>(0, 9) = Haralick::f10DifferenceVariance(mat);
	output.at<float>(0, 10) = Haralick::f11DifferenceEntropy(mat);
	//output.at<float>(0, 11) = Haralick::f12InformationCorrelation01(mat);
	//output.at<float>(0, 12) = Haralick::f13InformationCorrelation02(mat);
	//output.at<float>(0, 13) = 0.0f;
	output.at<float>(0, 11) = Haralick::f15_Dierctionality(mat);

	for (int i = 0; i < 12; i++)
		if (isnan(output.at<float>(0, i))) output.at<float>(0, i) = 0.0f;

	return output;
}

float Haralick::f1ASM(const cv::Mat& mat) {
  float sum = 0.0;

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      sum += mat.at<float>(i, j) * mat.at<float>(i, j);

  return sum;
  /*
  * The angular second-moment feature (ASM) f1 is a measure of homogeneity
  * of the image. In a homogeneous image, there are very few dominant
  * gray-tone transitions. Hence the P matrix for such an image will have
  * fewer entries of large magnitude.
  */
}

float Haralick::f2Contrast(const cv::Mat& mat) {
  float sum = 0.0, bigsum = 0.0;

  for (auto k = 0; k < mat.rows; ++k) {
    for (auto i = 0; i < mat.cols; ++i)
      for (auto j = 0; j < mat.rows; ++j)
        if ((i - j) == k || (j - i) == k) sum += mat.at<float>(i, j);
    bigsum += k * k * sum;
    sum = 0;
  }
  return bigsum;
  /*
  * The contrast feature is a difference moment of the P matrix and is a
  * measure of the contrast or the amount of local variations present in an
  * image.
  */
}

float Haralick::f3Correlation(const cv::Mat& mat) {
  std::vector<float> px(mat.rows, 0);

  /*
  * px[i] is the (i-1)th entry in the marginal probability matrix obtained
  * by summing the rows of p[i][j]
  */
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) px[i] += mat.at<float>(i, j);

  /* Now calculate the means and standard deviations of px and py */
  /*- fix supplied by J. Michael Christensen, 21 Jun 1991 */
  /*- further modified by James Darrell McCauley, 16 Aug 1991
  *     after realizing that meanx=meany and stddevx=stddevy
  */
  float meanX = 0.0, sumSqrX = 0.0;
  for (auto i = 0; i < mat.rows; ++i) {
    meanX += px[i] * i;
    sumSqrX += px[i] * i * i;
  }

  auto meanY = meanX;  // Because matrix is simetric
  auto stdDevX = sqrt(sumSqrX - (meanX * meanX));
  stdDevX += static_cast<float>(static_cast<float>(HARALICK_EPSILON));
  auto stdDevY = stdDevX;

  /* Finally, the correlation ... */
  float sum = 0.0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) sum += i * j * mat.at<float>(i, j);

  return (sum - meanX * meanY) / (stdDevX * stdDevY);
  /*
  * This correlation feature is a measure of gray-tone linear-dependencies
  * in the image.
  */
}

float Haralick::f4Variance(const cv::Mat& mat) {
  float mean = 0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) mean += i * mat.at<float>(i, j);

  float variance = 0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      variance += (i + 1 - mean) * (i + 1 - mean) * mat.at<float>(i, j);

  return variance;
}

float Haralick::f5IDM(const cv::Mat& mat) {
  float idm = 0.0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      idm += mat.at<float>(i, j) / (1 + (i - j) * (i - j));

  return idm;
  /* Inverse Difference Moment */
}

float Haralick::f6SumAverage(const cv::Mat& mat) {
  std::vector<float> pXY(mat.rows + mat.cols + 1, 0);

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) pXY[i + j + 2] += mat.at<float>(i, j);

  float sumAvg = 0;
  for (auto i = 2; i <= mat.rows + mat.cols; ++i) {
    sumAvg += i * pXY[i];
  }

  return sumAvg;
  /* Sum Average */
}

float Haralick::f7SumVariance(const cv::Mat& mat) {
  std::vector<float> pXY(mat.rows + mat.cols + 1, 0);

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) pXY[i + j + 2] += mat.at<float>(i, j);

  float f6SumAvg = 0.0;
  for (auto i = 2; i <= mat.rows + mat.cols; ++i) {
    f6SumAvg += i * pXY[i];
  }

  float sumVariance = 0.0;
  for (auto i = 2; i <= mat.rows + mat.cols; ++i) {
    sumVariance += (i - f6SumAvg) * (i - f6SumAvg) * pXY[i];
  }

  return sumVariance;
  /* Sum Variance */
}

float Haralick::f8SumEntropy(const cv::Mat& mat) {
  std::vector<float> pXY(mat.rows + mat.cols + 1, 0);

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) pXY[i + j + 2] += mat.at<float>(i, j);

  float sumEntropy = 0.0;
  for (auto i = 2; i <= mat.rows + mat.cols; ++i) {
    sumEntropy += pXY[i] * log10(pXY[i] + static_cast<float>(HARALICK_EPSILON));
  }

  return -sumEntropy;
  /* Sum Entropy */
}

float Haralick::f9Entropy(const cv::Mat& mat) {
  float entropy = 0.0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      entropy +=
          mat.at<float>(i, j) *
          log10(mat.at<float>(i, j) + static_cast<float>(HARALICK_EPSILON));

  return -entropy;
  /* Entropy */
}

float Haralick::f10DifferenceVariance(const cv::Mat& mat) {
  std::vector<float> pXY(mat.rows + mat.cols + 1, 0);

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      pXY[std::abs(i - j)] += mat.at<float>(i, j);

  /* Now calculate the variance of Pxpy (Px-y) */
  float sum = 0.0;
  float sumSqr = 0.0;
  for (auto i = 0; i < mat.rows; ++i) {
    sum += pXY[i];
    sumSqr += pXY[i] * pXY[i];
  }
  float tmp = static_cast<float>(mat.rows * mat.cols);
  float diffVar = ((tmp * sumSqr) - (sum * sum)) / (tmp * tmp);

  return diffVar;
  /* Difference Variance */
}

float Haralick::f11DifferenceEntropy(const cv::Mat& mat) {
  std::vector<float> pXY(mat.rows + mat.cols + 1, 0);

  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j)
      pXY[std::abs(i - j)] += mat.at<float>(i, j);

  float sum = 0.0;
  for (auto i = 0; i < mat.rows; ++i)
    sum += pXY[i] * log10(pXY[i] + static_cast<float>(HARALICK_EPSILON));

  return -sum;

  /* Difference Entropy */
}

float Haralick::f12InformationCorrelation01(const cv::Mat& mat) {
  std::vector<float> pX(mat.rows, 0);
  std::vector<float> pY(mat.cols, 0);

  /*
  * px[i] is the (i-1)th entry in the marginal probability matrix obtained
  * by summing the rows of p[i][j]
  */
  for (auto i = 0; i < mat.rows; ++i) {
    for (auto j = 0; j < mat.cols; ++j) {
      pX[i] += mat.at<float>(i, j);
      pY[j] += mat.at<float>(i, j);
    }
  }

  float hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) {
      hxy1 -= mat.at<float>(i, j) *
              log10(pX[i] * pY[j] + static_cast<float>(HARALICK_EPSILON));
      hxy2 -= pX[i] * pY[j] *
              log10(pX[i] * pY[j] + static_cast<float>(HARALICK_EPSILON));
      hxy -= mat.at<float>(i, j) *
             log10(mat.at<float>(i, j) + static_cast<float>(HARALICK_EPSILON));
    }

  /* Calculate entropies of px and py - is this right? */
  for (auto i = 0; i < mat.rows; ++i) {
    hx -= pX[i] * log10(pX[i] + static_cast<float>(HARALICK_EPSILON));
    hy -= pY[i] * log10(pY[i] + static_cast<float>(HARALICK_EPSILON));
  }

  /* fprintf(stderr,"hxy1=%f\thxy=%f\thx=%f\thy=%f\n",hxy1,hxy,hx,hy); */
  return ((hxy - hxy1) / (hx > hy ? hx : hy));
}

float Haralick::f13InformationCorrelation02(const cv::Mat& mat) {
  std::vector<float> pX(mat.rows, 0);
  std::vector<float> pY(mat.cols, 0);

  /*
  * px[i] is the (i-1)th entry in the marginal probability matrix obtained
  * by summing the rows of p[i][j]
  */
  for (auto i = 0; i < mat.rows; ++i) {
    for (auto j = 0; j < mat.cols; ++j) {
      pX[i] += mat.at<float>(i, j);
      pY[j] += mat.at<float>(i, j);
    }
  }

  float hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;
  for (auto i = 0; i < mat.rows; ++i)
    for (auto j = 0; j < mat.cols; ++j) {
      hxy1 -= mat.at<float>(i, j) *
              log10(pY[i] * pY[j] + static_cast<float>(HARALICK_EPSILON));
      hxy2 -= pX[i] * pY[j] *
              log10(pX[i] * pY[j] + static_cast<float>(HARALICK_EPSILON));
      hxy -= mat.at<float>(i, j) *
             log10(mat.at<float>(i, j) + static_cast<float>(HARALICK_EPSILON));
    }

  /* Calculate entropies of px and py */
  for (auto i = 0; i < mat.rows; ++i) {
    hx -= pX[i] * log10(pX[i] + static_cast<float>(HARALICK_EPSILON));
    hy -= pY[i] * log10(pY[i] + static_cast<float>(HARALICK_EPSILON));
  }

  /* fprintf(stderr,"hx=%f\thxy2=%f\n",hx,hxy2); */
  return static_cast<float>(sqrt(abs(1 - exp(-2.0 * (hxy2 - hxy)))));

  /* Information Measures of Correlation */
}

float Haralick::f15_Dierctionality(const cv::Mat& mat) {
  float sum = 0.0;
  for (auto i = 0; i < mat.rows; ++i) {
    sum += mat.at<float>(i, i);
  }

  return sum;
}

}  // namespace ssig
