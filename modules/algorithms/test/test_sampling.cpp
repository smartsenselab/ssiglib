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

#include <gtest/gtest.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <algorithms/sampling_method.hpp>

TEST(ImageSampling, execution){

  auto samples = ssf::SamplingMethod::sampleImage(10, 10, 2, 2, 1.0f, 1.0f, 1, 1.0f, 1.0f);

  EXPECT_EQ(25, samples.size());
  EXPECT_EQ(cv::Rect(0, 0, 2, 2), samples[0]);
  EXPECT_EQ(cv::Rect(8, 8, 2, 2), samples.back());

  samples = ssf::SamplingMethod::sampleImage(500, 375, 80, 80, 1.0f, 2.0f, 7, 0.4f, 0.4f);
}

TEST(ImageSampling, FeatureDetection){
  auto img = cv::imread("000036.jpg", cv::IMREAD_GRAYSCALE);
  int maxPatches = 20;
  cv::Size winSize{ 80, 80 };

  auto samples = ssf::SamplingMethod::sampleImage(img,
    maxPatches,
    winSize);

}