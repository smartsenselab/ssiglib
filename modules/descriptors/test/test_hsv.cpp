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
#include <descriptors/color_histogram_hsv.hpp>

TEST(HSV_Histogram, HSV_Simple) {
  cv::Mat img(1, 4, CV_8UC3);

  img.at<cv::Vec3b>(0, 0) = cv::Vec3b(255, 21, 0);
  img.at<cv::Vec3b>(0, 1) = cv::Vec3b(208, 255, 0);
  img.at<cv::Vec3b>(0, 2) = cv::Vec3b(0, 223, 255);
  img.at<cv::Vec3b>(0, 3) = cv::Vec3b(0, 0, 255);

  ssig::ColorHistogramHSV hsv(img);
  cv::Mat featVector;

  hsv.extract(featVector);
  int total = static_cast<int>(cv::sum(featVector)[0]);
  ASSERT_EQ(1, total);

  cv::Mat_<float> expected(1, 256, 0.f);
  expected[0][240] = .25f;
  expected[0][242] = .25f;
  expected[0][247] = .25f;
  expected[0][250] = .25f;

  cv::Mat comparison;
  cv::compare(featVector, expected, comparison, CV_CMP_EQ);

  int diff = static_cast<int>(cv::countNonZero(comparison));
  ASSERT_EQ(featVector.rows * featVector.cols, diff);
}

