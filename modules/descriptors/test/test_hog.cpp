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
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>

#include "descriptors/hog_features.hpp"

// TEST(HOG, HogTest) {
//  cv::Mat img;
//  cv::Mat_<float> out;
//  cv::Mat_<float> cvOut;
//  std::vector<float> descriptors;
//
//  img = cv::imread("diag2.png");
//
//  ssig::HOG hog(img);
//  hog.setBlockConfiguration({16, 16});
//  hog.setBlockStride({16, 16});
//  hog.setCellConfiguration({2, 2});
//  hog.setNumberOfBins(9);
//  hog.nextFeatureVector(out);
//
//  /*cv::Mat vis;
//  ssig::HOG::computeVisualization(out, 9, { 16, 16 }, { 16, 16 }, { 2, 2 }, {
//  img.cols, img.rows }, vis);*/
//
//  cv::HOGDescriptor cvHog({512, 512}, {16, 16}, {16, 16}, {8, 8}, 9);
//  cvHog.compute(img, descriptors);
//  cvOut = cv::Mat_<float>(1, static_cast<int>(descriptors.size()),
//                          descriptors.data());
//  auto sim =
//      static_cast<float>(cvOut.dot(out) / (cv::norm(cvOut) * cv::norm(out)));
//  EXPECT_GE(sim, 0.7f);
//}
//
// TEST(HOG, LenaTest) {
//  cv::Mat img;
//  cv::Mat_<float> out;
//  cv::Mat_<float> cvOut;
//  std::vector<float> descriptors;
//
//  img = cv::imread("Lena_bw.png");
//  ssig::HOG hog(img);
//  hog.setBlockConfiguration({16, 16});
//  hog.setBlockStride({16, 16});
//  hog.setCellConfiguration({2, 2});
//  hog.setNumberOfBins(9);
//  hog.nextFeatureVector(out);
//
//  /*cv::Mat vis;
//  ssig::HOG::computeVisualization(out, 9, { 16, 16 }, { 16, 16 }, { 2, 2 }, {
//  img.cols, img.rows }, vis);*/
//
//  cv::HOGDescriptor cvHog({512, 512}, {16, 16}, {16, 16}, {8, 8}, 9);
//  cvHog.compute(img, descriptors);
//  cvOut = cv::Mat_<float>(1, static_cast<int>(descriptors.size()),
//                          descriptors.data());
//
//  /*ssig::HOG::computeVisualization(out, 9, { 16, 16 }, { 16, 16 }, { 2, 2 },
//  {
//   * img.cols, img.rows }, vis);*/
//
//  float sim =
//      static_cast<float>(cvOut.dot(out) / (cv::norm(cvOut) * cv::norm(out)));
//
//  EXPECT_GE(sim, 0.70f);
//}
