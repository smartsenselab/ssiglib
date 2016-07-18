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

#include <gtest/gtest.h>
#include "ssiglib/ml/spectral_embedding.hpp"

TEST(SpectralEmbedding, SampleSpectralEmbedding) {
  // Automatically generated stub
  auto specEmbedding = ssig::SpectralEmbedding::create();
  cv::Mat_<float> output, X;

  X = cv::Mat::zeros(30, 10, CV_32FC1);
  cv::randn(X.rowRange(0, 15),
    cv::Mat::zeros(1, 1, CV_32F),
    cv::Mat::ones(1, 1, CV_32F));
  cv::randn(X.rowRange(15, 30),
    cv::Mat(1, 1, CV_32F, 10),
    cv::Mat::ones(1, 1, CV_32F));

  specEmbedding->learn(X, output);
  auto eiValues = specEmbedding->getEigenValues();
  /*
  *We have two Gaussians and therefore Two disconnected components,
  we expect that if the method is working, than the two first eigenValues 
  will be really close to zero.
  */
  EXPECT_LT(abs(eiValues.at<float>(0)), 1e-4);
  EXPECT_LT(abs(eiValues.at<float>(1)), 1e-4);
}
