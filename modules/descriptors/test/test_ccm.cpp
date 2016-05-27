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

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "ssiglib/descriptors/ccm_features.hpp"

TEST(ColorCoOccurrence, SimpleColorCoOccurrence) {
  cv::Mat img = cv::imread("glcm.png");
  ASSERT_FALSE(img.empty());
  ssig::ColorCoOccurrence ccm(img);
  cv::Mat out;

  ccm.setBins({4, 4, 4});
  ccm.setLevels({256, 256, 256});

  ccm.extract(out);

  /*cv::Mat_<float> expected = (cv::Mat_<float>(1, 16) <<
    235, 0, 0, 1,
    2, 0, 0, 0,
    0, 0, 0, 0,
    0, 2, 0, 0);

  cv::Mat diff = cv::abs(out - expected);
  cv::Mat epsilon(diff.rows, diff.cols, CV_32FC1);
  epsilon = 4 * FLT_EPSILON;
  cv::Mat cmpson;
  cv::compare(diff, epsilon, cmpson, cv::CMP_LT);
  int diffSum = cv::countNonZero(cmpson);
  EXPECT_EQ(16, diffSum);*/
}

TEST(CCM, CCM_Vert) {
  cv::Mat red = (cv::Mat_<int>(2, 2) <<
        1 , 1 ,
            0 , 0),
      green = (cv::Mat_<int>(2, 2) <<
        0 , 0 ,
            1 , 1),
      blue = (cv::Mat_<int>(2, 2) <<
        1 , 1 ,
            0 , 0);
  cv::Mat img;
  std::vector<cv::Mat> channels = {blue, green, red};
  cv::merge(channels, img);
  ASSERT_FALSE(img.empty());
  ssig::ColorCoOccurrence ccm(img);
  cv::Mat out;

  ccm.setBins({2, 2, 2});
  ccm.setLevels({2, 2, 2});
  ccm.setDirection(0, 1);
  ccm.extract(out);

  cv::Mat_<float> expected = (cv::Mat_<float>(1, 24) <<
    0 , 0 , 2 , 0 ,
        0 , 0 , 0 , 2 ,
        0 , 0 , 2 , 0 ,
        0 , 2 , 0 , 0 ,
        2 , 0 , 0 , 0 ,
        0 , 0 , 2 , 0);

  cv::Mat diff = cv::abs(out - expected);
  cv::Mat epsilon(diff.rows, diff.cols, CV_32FC1);
  epsilon = 4 * FLT_EPSILON;
  cv::Mat cmpson;
  cv::compare(diff, epsilon, cmpson, cv::CMP_LT);
  int diffSum = cv::countNonZero(cmpson);
  EXPECT_EQ(24, diffSum);
}
