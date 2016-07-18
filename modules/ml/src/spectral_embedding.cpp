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

// opencv
#include <opencv2/flann/kdtree_index.h>
// ssiglib
#include "ssiglib/ml/spectral_embedding.hpp"

namespace ssig {

using KdTree = cv::flann::GenericIndex<cv::flann::L2<float>>;
using KdTreeParams = cvflann::KDTreeIndexParams;

SpectralEmbedding::SpectralEmbedding() {
  // Constructor
}

SpectralEmbedding::~SpectralEmbedding() {
  // Destructor
}

SpectralEmbedding::SpectralEmbedding(const SpectralEmbedding& rhs) {
  // Constructor Copy
}

SpectralEmbedding& SpectralEmbedding::operator=(const SpectralEmbedding& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void SpectralEmbedding::learn(
  cv::InputArray input,
  cv::OutputArray output) {
  cv::Mat inpMat = input.getMat();
  const int nSamples = inpMat.rows;

  auto indexParams = cvflann::AutotunedIndexParams();

#ifdef _WIN32
  mKdtree = std::make_unique<KdTree>(
                                     inpMat,
                                     indexParams);
#else
  mKdtree = std::unique_ptr<KdTree>(inpMat, kdTreeParams);
#endif

  // construct Matrix W
  cv::Mat indices(nSamples, mKnn, CV_32F), dists(nSamples, mKnn, CV_32F);
  mKdtree->knnSearch(inpMat, indices, dists, mKnn, *mSearchParams);
  cv::Mat W(nSamples, nSamples, CV_32F, 0.0f);

  for (int r = 0; r < nSamples; ++r) {
    for (int c = 0; c < mKnn; ++c) {
      int idx = indices.at<int>(r, c);
      if (idx == r)
        continue;

      W.at<float>(r, idx) = dists.at<float>(r, c);
      W.at<float>(idx, r) = dists.at<float>(r, c);
    }
  }
  // construct Matrix D (inside W)
  for (int r = 0; r < nSamples; ++r) {
    W.at<float>(r, r) = -static_cast<float>(cv::sum(W.row(r))[0]);
  }
  // construct Graph Laplacian (L =  D - W)
  W = -W;
  // extract eigenvectors of L
  cv::Mat eigenValues, eigenVectors;
  cv::eigen(W, eigenValues, eigenVectors);
  eigenVectors.colRange(0, mDimensions).copyTo(output);
  mEigenvectors = eigenVectors;
}

void SpectralEmbedding::read(const cv::FileNode& fn) {}

void SpectralEmbedding::write(cv::FileStorage& fs) const {}
}  // namespace ssig
