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
#include "ssiglib/descriptors/co_occurrence_general.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>

TEST(CoOccurrenceGeneral, SampleCoOccurrenceGeneral) {
  cv::Mat_<int>img;
  std::vector<cv::Mat> mat;
  ssig::CoOccurrenceGeneral *cooc = new ssig::CoOccurrenceGeneral(255, 1);

  img = cv::imread("cooc_img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  ASSERT_FALSE(img.empty());
  cv::Rect patch(0, 0, img.cols, img.rows);

  cooc->extractAllMatricesDirections(patch, img, mat);

  std::vector<cv::Mat> loadedMat;
  cv::FileStorage storageMatrix;
  cv::FileNode node, n1;

  // Loading pre-computed matrices
  for (int degree = 0; degree <= 136; degree += 45) {
    cv::Mat tempMat;
    std::stringstream number;
    number << std::setw(4) << std::setfill('0') << degree;
    std::string path = "cooc_matrix" + number.str() + ".yml";
    storageMatrix.open(path, cv::FileStorage::READ);

    node = storageMatrix.root();
    n1 = node["ActionRecognitionFeatures"];
    n1["Matrix"] >> tempMat;

    loadedMat.push_back(tempMat.clone());
  }

  // Comparing matrices
  for (int matrix = 0; matrix < loadedMat.size(); matrix++)
    for (int i = 0; i < loadedMat[matrix].rows; i++)
      for (int j = 0; j < loadedMat[matrix].cols; j++)
        EXPECT_NEAR(loadedMat[matrix].at<float>(i, j), mat[matrix].at<float>(i, j), 0.001);  // if (loadedMat[matrix].at<float>(i, j) == mat[matrix].at<float>(i, j))					
}
