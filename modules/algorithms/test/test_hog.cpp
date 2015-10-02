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
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include "algorithms/hog_features.hpp"

TEST(HOG, HogTest){
  ssf::HOG hog;

  cv::Mat img;
  cv::Mat_<float> out;
  cv::Mat_<float> cvOut;
  std::vector<float> descriptors;


  hog.setBlockConfiguration({8, 8});
  hog.setCellConfiguration({1, 1});
  hog.setNumberOfBins(9);

  img = cv::imread("diag2.png");
  hog.setup(img);
  hog.extract({0, 0, img.cols, img.rows}, out);

  cv::HOGDescriptor cvHogDiag({512, 512}, {8, 8}, {8, 8}, {8, 8}, 9);
  cvHogDiag.compute(img, descriptors);
  cvOut = cv::Mat_<float>(1, static_cast<int>(descriptors.size()), descriptors.data());
  auto sim = cvOut.dot(out) / (cv::norm(cvOut) * cv::norm(out));
  ASSERT_GE(sim, 0.8f);

  hog.setBlockConfiguration({16, 16});
  hog.setCellConfiguration({2, 2});
  hog.setNumberOfBins(9);

  img = cv::imread("Lena_bw.png");
  hog.setup(img);
  hog.extract({0, 0, img.cols, img.rows}, out);

  cv::HOGDescriptor cvHog({512, 512}, {16, 16}, {16, 16}, {8, 8}, 9);
  cvHog.compute(img, descriptors);
  cvOut = cv::Mat_<float>(1, static_cast<int>(descriptors.size()), descriptors.data());
  sim = cvOut.dot(out) / (cv::norm(cvOut) * cv::norm(out));

  ASSERT_GE(sim, 0.70f);
}
