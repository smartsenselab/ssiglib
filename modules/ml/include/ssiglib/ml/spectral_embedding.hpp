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

#ifndef _SSIG_ML_SPECTRAL_EMBEDDING_HPP_
#define _SSIG_ML_SPECTRAL_EMBEDDING_HPP_

// c++
#include <memory>
// opencv
#include <opencv2/core.hpp>
// ssiglib
#include "embedding.hpp"
// flann
#include <flann/flann.hpp>


namespace ssig {
class SpectralEmbedding : public ssig::Algorithm {
 public:
  ML_EXPORT static cv::Ptr<SpectralEmbedding> create();
  ML_EXPORT virtual ~SpectralEmbedding(void);
  ML_EXPORT SpectralEmbedding(const SpectralEmbedding& rhs);
  ML_EXPORT SpectralEmbedding& operator=(const SpectralEmbedding& rhs);

  ML_EXPORT void learn(
    cv::InputArray input,
    cv::OutputArray output);

  ML_EXPORT cv::Mat getEigenValues() const;
  ML_EXPORT void setEigenValues(const cv::Mat& eigenValues);
  ML_EXPORT cv::Mat getEigenvectors() const;
  ML_EXPORT void setEigenvectors(const cv::Mat& eigenvectors);


  ML_EXPORT int getKnn() const;
  ML_EXPORT void setKnn(const int knn);
  ML_EXPORT int getDimensions() const;
  ML_EXPORT void setDimensions(const int dimensions);

 protected:
  ML_EXPORT SpectralEmbedding(void);
  ML_EXPORT void read(const cv::FileNode& fn) override;
  ML_EXPORT void write(cv::FileStorage& fs) const override;

 private:
  // private members
  int mKnn = 5;
  int mDimensions = 2;

  cv::Mat mEigenVectors;
  cv::Mat mEigenValues;
};
}  // namespace ssig
#endif  // !_SSIG_ML_SPECTRAL_EMBEDDING_HPP_
