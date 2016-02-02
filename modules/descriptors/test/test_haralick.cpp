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
#include <descriptors/haralick.hpp>

TEST(Haralick, compute_size8) {

  cv::FileStorage fs("haralick/haralick8.yml", cv::FileStorage::READ);

  for (int i = 1; i <= 50; i++){
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << i;
    std::string number = ss.str();

    cv::Mat mat;
    fs["matrix" + number] >> mat;

    cv::Mat feature;
    fs["feature" + number] >> feature;

    cv::Mat result;
    result = ssig::Haralick::compute(mat);

    EXPECT_FLOAT_EQ(feature.at<float>(0, 0), result.at<float>(0, 0));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 1), result.at<float>(0, 1));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 2), result.at<float>(0, 2));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 3), result.at<float>(0, 3));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 4), result.at<float>(0, 4));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 5), result.at<float>(0, 5));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 6), result.at<float>(0, 6));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 7), result.at<float>(0, 7));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 8), result.at<float>(0, 8));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 9), result.at<float>(0, 9));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 10), result.at<float>(0, 10));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 11), result.at<float>(0, 14));

  }
  fs.release();

}


TEST(Haralick, compute_size256) {

  cv::FileStorage fs("haralick/haralick256.yml", cv::FileStorage::READ);

  for (int i = 1; i <= 10; i++){
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << i;
    std::string number = ss.str();

    cv::Mat mat;
    fs["matrix" + number] >> mat;

    cv::Mat feature;
    fs["feature" + number] >> feature;

    cv::Mat result;
    result = ssig::Haralick::compute(mat);

    EXPECT_FLOAT_EQ(feature.at<float>(0, 0), result.at<float>(0, 0));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 1), result.at<float>(0, 1));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 2), result.at<float>(0, 2));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 3), result.at<float>(0, 3));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 4), result.at<float>(0, 4));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 5), result.at<float>(0, 5));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 6), result.at<float>(0, 6));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 7), result.at<float>(0, 7));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 8), result.at<float>(0, 8));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 9), result.at<float>(0, 9));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 10), result.at<float>(0, 10));
    EXPECT_FLOAT_EQ(feature.at<float>(0, 11), result.at<float>(0, 14));

  }
  fs.release();

}

