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
// c++
#include <algorithm>
#include <vector>
// opencv
#include <opencv2/imgproc.hpp>
// ssiglib
#include "ssiglib/ml/stacked_pls.hpp"
#include "ssiglib/ml/pls_classifier.hpp"
#include "ssiglib/ml/pls_embedding.hpp"

typedef std::vector<cv::Mat> ImgCollection;

namespace ssig {
cv::Ptr<StackedPLS> StackedPLS::create() {
  return cv::Ptr<StackedPLS>(new StackedPLS());
}

StackedPLS::~StackedPLS() {
  // Destructor
}

StackedPLS::StackedPLS(const StackedPLS& rhs) {
  // Constructor Copy
}

StackedPLS& StackedPLS::operator=(const StackedPLS& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

StackedPLS::StackedPLS() {
  mNumFactors = {9, 6};
  mConvolutionSize = {5, 4};
  mPoolingSize = {2, 3};
  mCanonicalSize = {{28, 28}};
  mFilters.resize(2);
}

void StackedPLS::read(const cv::FileNode& fn) {
  // TODO(Ricardo):
}

void StackedPLS::write(cv::FileStorage& fs) const {
  // TODO(Ricardo):
}

void StackedPLS::learn(
  const std::vector<cv::Mat>& input,
  const cv::Mat& labels) {
  std::vector<std::vector<ImgCollection>> inputs(mNumLayers);
  std::vector<cv::Size> canonicalSizes(mNumLayers);
  canonicalSizes[0] = mCanonicalSize;

  std::vector<std::vector<ImgCollection>> layerOutputs(mNumLayers);

  const int nImages = static_cast<int>(input.size());
  verboseLog("nImages[%d]\n", nImages);
  std::vector<cv::Mat> resized(nImages);
  for (int imgIt = 0; imgIt < nImages; ++imgIt) {
    resize(input[imgIt],
           mCanonicalSize.width,
           mCanonicalSize.height,
           resized[imgIt]);
  }
  inputs[0] = {resized};
  ImgCollection outAccumulator(nImages);
  /**
  * Make a pass on each layer where the input of the
   next layer is the output of the last layer.
  **/
  for (int layerNum = 0; layerNum < mNumLayers;) {
    verboseLog("Layer [%d]\n", layerNum);
    int nextLayer = layerNum + 1;
    for (int i = 0; i < inputs[layerNum].size(); ++i) {
      std::vector<ImgCollection> out;
      std::vector<cv::Mat> filters;
      ///////////////////////////////
      pass(inputs[layerNum][i],
           labels,
           mConvolutionSize[layerNum],
           mPoolingSize[layerNum],
           mNumFactors[layerNum],
           filters,
           out);
      //////////////////////////////
      mFilters[layerNum].insert(
                                mFilters[layerNum].begin(),
                                filters.begin(),
                                filters.end());
      layerOutputs[layerNum].insert(
                                    layerOutputs[layerNum].begin(),
                                    out.begin(),
                                    out.end());
      if (nextLayer < mNumLayers) {
        inputs[nextLayer].insert(
                                 inputs[nextLayer].begin(),
                                 out.begin(),
                                 out.end());
      } else {
        // last layer
        verboseLog("[Last Layer Cuboid [%d]]\n", i);
        for (int k = 0; k < nImages; ++k) {
          for (int j = 0; j < mNumFactors[layerNum]; ++j) {
            outAccumulator[k].push_back(out[j][k]);
          }
        }
      }
    }
    layerNum = nextLayer;
  }
  for (int i = 0; i < nImages; ++i) {
    mTrainOut.push_back(outAccumulator[i].reshape(1, 1));
  }
}

void StackedPLS::extract(
  const cv::Mat& input,
  cv::Mat& output) {
  cv::Mat resized;
  resize(input,
         mCanonicalSize.width,
         mCanonicalSize.height,
         resized);
  verboseLog("NumLayers [%d]\n", mNumLayers);
  std::vector<ImgCollection> inputs(mNumLayers + 1);
  inputs[0] = {resized};
  for (int layerNum = 0; layerNum < mNumLayers;) {
    verboseLog("layer order[%d]\n", layerNum);
    int nextLayer = layerNum + 1;
    const int numInputs = static_cast<int>(inputs[layerNum].size());
    // convolution
    verboseLog("Convolution\n");
    std::vector<cv::Mat> convolveds(mNumFactors[layerNum]);;
    for (int i = 0; i < numInputs; ++i) {
      const int C = mNumFactors[layerNum];
      for (int c = 0; c < C; ++c) {
        cv::Mat filter = mFilters[layerNum][i * C + c];
        cv::filter2D(inputs[layerNum][i],
                     convolveds[c],
                     CV_32F, filter);
      }
      // END Convolution
      verboseLog("pooling\n");
      ///////////
      std::vector<cv::Mat> pooleds(mNumFactors[layerNum]);;
      pool(convolveds, mPoolingSize[layerNum], pooleds);
      verboseLog("Normalize\n");
      normalize(pooleds, convolveds);

      inputs[nextLayer].insert(
        inputs[nextLayer].end(),
        convolveds.begin(),
        convolveds.end());
    }
    layerNum = nextLayer;
  }
  verboseLog("inputs size[%d]\n", inputs[mNumLayers].size());
  for (const auto& mat : inputs[mNumLayers]) {
    output.push_back(mat);
  }
  output = output.reshape(1, 1);
}

void StackedPLS::pass(
  const std::vector<cv::Mat>& input,
  cv::Mat labelMat,
  const int convSize,
  const int poolSize,
  const int numFactors,
  std::vector<cv::Mat>& filters,
  std::vector<std::vector<cv::Mat>>& out) const {
  const int nImages = static_cast<int>(input.size());
  std::vector<cv::Mat> unpackeds(nImages);

#ifdef _OPENMP
  #pragma omp parallel for num_threads(2)
#endif
  for (int imgIt = 0; imgIt < nImages; ++imgIt) {
    unpack(input[imgIt], convSize, unpackeds[imgIt]);
  }

  filters.resize(numFactors);
  // compute filters
  computeLayer(unpackeds,
               labelMat,
               convSize,
               numFactors,
               filters);
  // convolve
  std::vector<std::vector<cv::Mat>> convolveds(numFactors);
  for (int i = 0; i < numFactors; ++i) {
    convolveds[i].resize(nImages);
  }
  for (int i = 0; i < nImages; ++i) {
    for (int c = 0; c < numFactors; ++c) {
      cv::filter2D(input[i],
                   convolveds[c][i],
                   CV_32F,
                   filters[c]);
    }
  }
  // pool
  std::vector<std::vector<cv::Mat>> pooled(numFactors);
  for (int c = 0; c < numFactors; ++c) {
    pool(convolveds[c],
         poolSize,
         pooled[c]);
  }
  // normalize
  // instead of using another vec_vec_mat we reuse convolveds
  for (int c = 0; c < numFactors; ++c) {
    normalize(pooled[c],
              convolveds[c]);
  }
  out = std::move(convolveds);
}

void StackedPLS::resize(
  const cv::Mat& imageMat,
  const int canWidth,
  const int canHeight,
  cv::Mat& out) const {
  cv::Mat image = imageMat;
  cv::Mat resized;
  int iRows = image.rows,
      iCols = image.cols;
  int rowPadding = 0,
      colPadding = 0;
  float ratio = 1.f;
  if (iRows > canHeight || iCols > canWidth) {
    if (iRows < iCols) {
      ratio = static_cast<float>(canWidth) / iCols;
    } else {
      ratio = static_cast<float>(canHeight) / iRows;
    }
  }
  if (ratio != 1.f) {
    cv::Size sz = image.size();
    sz = cv::Size(
                  static_cast<int>(ratio * sz.width),
                  static_cast<int>(ratio * sz.height));
    cv::resize(image, resized, sz);
    verboseLog("Resized image to canonical size\n");
    iRows = resized.rows;
    iCols = resized.cols;
  }

  if (iRows < canHeight) {
    rowPadding = canHeight - iRows;
    verboseLog("Padded image to canonical size\n");
  }
  if (iCols < canWidth) {
    colPadding = canWidth - iCols;
    verboseLog("Padded image to canonical size\n");
  }
  cv::copyMakeBorder(image, resized,
                     0, rowPadding,
                     0, colPadding,
                     cv::BORDER_CONSTANT, 0);
  resized.copyTo(out);
}

void StackedPLS::unpack(
  const cv::Mat& input,
  const int S,
  cv::Mat& unpacked) const {
  cv::Mat image;
  input.convertTo(image, CV_32F);

  const int width = image.cols,
      height = image.rows;

  const int NumElements = S * S;
  const int NumBlocks = static_cast<int>(floor(width / S) * floor(height / S));
  cv::Mat_<float> unpackedX(
                            NumBlocks,
                            NumElements,
                            0.f);
  int nBlocks = 0;
  for (int r = 0; r <= height - S; r += S) {
    for (int c = 0; c <= width - S; c += S) {
      int nElements = 0;
      for (int sR = 0; sR < S; ++sR) {
        for (int sC = 0; sC < S; ++sC) {
          unpackedX.at<float>(nBlocks, nElements) =
              image.at<float>(r + sR, c + sC);
          ++nElements;
        }
      }
      ++nBlocks;
    }
  }
  unpackedX.copyTo(unpacked);
}

void StackedPLS::computeLayer(
  const std::vector<cv::Mat>& _input,
  const cv::Mat& _Y,
  const int S,
  const int numFactors,
  std::vector<cv::Mat>& filters) const {
  const int nImages = static_cast<int>(_input.size());
  // unpack the convolution points to a new sample
  cv::Mat_<float> wholeX, wholeY;
  cv::Mat Y = _Y;

  for (int imgIt = 0; imgIt < nImages; ++imgIt) {
    cv::Mat m = _input[imgIt];
    cv::Mat unpackedY;
    cv::repeat(Y.row(imgIt), m.rows, 1, unpackedY);
    wholeY.push_back(unpackedY);
    wholeX.push_back(m);
  }

  auto pls = ssig::PLSEmbedding::create(numFactors, wholeY);
  pls->learn(wholeX);
  cv::Mat Wstar = pls->getWstarMat();
  for (int c = 0; c < Wstar.cols; ++c) {
    cv::Mat filter = Wstar.col(c);
    filter = filter.t();
    filter = filter.reshape(1, S);
    filter.copyTo(filters[c]);
  }
}

void StackedPLS::normalize(
  const std::vector<cv::Mat>& inp,
  std::vector<cv::Mat>& normalized) const {
  normalized.resize(inp.size());
  /* COMMENTED OUT
   for (int i = 0; i < inp.size(); ++i) {
    normalized[i] = cv::Mat_<float>(inp[i].size(), 0.0f);
  }
  */

  for (int i = 0; i < inp.size(); ++i) {
    /* COMMENTED OUT
    cv::exp(-inp[i], normalized[i]);
    normalized[0] = normalized[i] + 1.f;
    normalized[i] = 1.f / normalized[i];
    */
    /* COMMENTED OUT
    const int rows = inp[i].rows,
    cols = inp[i].cols;
    normalized[i] = inp[i].clone();
    for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
    float value = inp[i].at<float>(r, c);
    normalized[i].at<float>(r, c) = 1 / (1 + exp(-value));
    }
    }*/
    cv::normalize(inp[i], normalized[i], 1, 0, cv::NORM_MINMAX);
  }
}

void StackedPLS::pool(
  const std::vector<cv::Mat>& convolved,
  const int poolingSize,
  std::vector<cv::Mat>& pooled) const {
  pooled.resize(convolved.size());
  for (int i = 0; i < convolved.size(); ++i) {
    cv::Mat mat = convolved[i];
    const int rows = mat.rows,
        cols = mat.cols;
    pooled[i] = cv::Mat(rows / poolingSize, cols / poolingSize, CV_32F);

    for (int r = 0; r <= rows - poolingSize; r += poolingSize) {
      int ridx = r / poolingSize;
      for (int c = 0; c <= cols - poolingSize; c += poolingSize) {
        int cidx = c / poolingSize;
        float max = -FLT_MAX;
        for (int rr = 0; rr < poolingSize; ++rr) {
          for (int cc = 0; cc < poolingSize; ++cc) {
            float value = convolved[i].at<float>(r + rr, c + cc);
            value = std::abs(value);
            max = std::max(max, value);
          }
        }
        pooled[i].at<float>(ridx, cidx) = max;
      }
    }
  }
}


std::vector<int> StackedPLS::getNumFactors() const {
  return mNumFactors;
}

void StackedPLS::setNumFactors(const std::vector<int>& numFactors) {
  mNumFactors = numFactors;
}

std::vector<int> StackedPLS::getConvolutionSize() const {
  return mConvolutionSize;
}

void StackedPLS::setConvolutionSize(const std::vector<int>& convolutionSize) {
  mConvolutionSize = convolutionSize;
}

std::vector<int> StackedPLS::getPoolingSize() const {
  return mPoolingSize;
}

void StackedPLS::setPoolingSize(const std::vector<int>& poolingSize) {
  mPoolingSize = poolingSize;
}

cv::Size StackedPLS::getCanonicalSize() const {
  return mCanonicalSize;
}

void StackedPLS::setCanonicalSize(const cv::Size& canonicalSize) {
  mCanonicalSize = canonicalSize;
}

std::vector<std::vector<cv::Mat>> StackedPLS::getFilters() const {
  return mFilters;
}

void StackedPLS::setFilters(const std::vector<std::vector<cv::Mat>>& filters) {
  mFilters = filters;
}

void StackedPLS::getTrainingOutput(cv::Mat& trainSamplesOut) const {
  mTrainOut.copyTo(trainSamplesOut);
}
}  // namespace ssig
