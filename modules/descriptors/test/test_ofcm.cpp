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
#include <opencv2/opencv.hpp>
#include "ssiglib/descriptors/descriptor_temporal.hpp"
#include "ssiglib/descriptors/ofcm_features.hpp"

TEST(OFCM, ConstructorOFCM) {
  ssig::OFCM *desc = new ssig::OFCM();

  EXPECT_EQ(desc->getnBinsMagnitude(), 8);
  EXPECT_EQ(desc->getnBinsAngle(), 8);
  EXPECT_EQ(desc->getDistanceMagnitude(), 1);
  EXPECT_EQ(desc->getDistanceAngle(), 1);
  EXPECT_EQ(desc->getCuboidLength(), 10);
  EXPECT_NEAR(desc->getMaxMagnitude(), 15, 0.001);
  EXPECT_NEAR(desc->getMaxAngle(), 361, 0.001);
  EXPECT_EQ(desc->getLogQuantization(), 1);
  EXPECT_EQ(desc->getMovementFilter(), true);
  EXPECT_EQ(desc->getTemporalScales().size(), 1);

  for (size_t i = 0; i < desc->getTemporalScales().size(); i++)
    EXPECT_EQ(desc->getTemporalScales()[0], 1);
}


TEST(OFCM, GettersOFCM) {
  int nBinsMagnitude = 4;
  int nBinsAngle = 6;
  int distanceMagnitude = 2;
  int distanceAngle = 3;
  int cuboidLength = 5;
  float maxMagnitude = 20;
  int logQuantization = 0;
  bool movementFilter = false;
  std::vector<int> tempScales;
  tempScales.push_back(1); tempScales.push_back(2);

  ssig::OFCM *desc = new ssig::OFCM(nBinsMagnitude, nBinsAngle, distanceMagnitude, distanceAngle,
                                    cuboidLength, maxMagnitude, logQuantization, movementFilter, tempScales);

  EXPECT_EQ(desc->getnBinsMagnitude(), nBinsMagnitude);
  EXPECT_EQ(desc->getnBinsAngle(), nBinsAngle);
  EXPECT_EQ(desc->getDistanceMagnitude(), distanceMagnitude);
  EXPECT_EQ(desc->getDistanceAngle(), distanceAngle);
  EXPECT_EQ(desc->getCuboidLength(), cuboidLength);
  EXPECT_NEAR(desc->getMaxMagnitude(), maxMagnitude, 0.001);
  EXPECT_EQ(desc->getLogQuantization(), logQuantization);
  EXPECT_EQ(desc->getMovementFilter(), movementFilter);

  for (size_t i = 0; i < tempScales.size(); i++)
    EXPECT_EQ(desc->getTemporalScales()[i], tempScales[i]);
}

TEST(OFCM, SettersOFCM) {
  int nBinsMagnitude = 4;
  int nBinsAngle = 6;
  int distanceMagnitude = 2;
  int distanceAngle = 3;
  int cuboidLength = 5;
  float maxMagnitude = 20;
  int logQuantization = 0;
  bool movementFilter = false;
  std::vector<int> tempScales;
  tempScales.push_back(1); tempScales.push_back(2);

  ssig::OFCM *desc = new ssig::OFCM();

  desc->setnBinsMagnitude(nBinsMagnitude);
  desc->setnBinsAngle(nBinsAngle);
  desc->setDistanceMagnitude(distanceMagnitude);
  desc->setDistanceAngle(distanceAngle);
  desc->setCuboidLength(cuboidLength);
  desc->setMaxMagnitude(maxMagnitude);
  desc->setLogQuantization(logQuantization);
  desc->setMovementFilter(movementFilter);
  desc->setTemporalScales(tempScales);

  EXPECT_EQ(desc->getnBinsMagnitude(), nBinsMagnitude);
  EXPECT_EQ(desc->getnBinsAngle(), nBinsAngle);
  EXPECT_EQ(desc->getDistanceMagnitude(), distanceMagnitude);
  EXPECT_EQ(desc->getDistanceAngle(), distanceAngle);
  EXPECT_EQ(desc->getCuboidLength(), cuboidLength);
  EXPECT_NEAR(desc->getMaxMagnitude(), maxMagnitude, 0.001);
  EXPECT_EQ(desc->getLogQuantization(), logQuantization);
  EXPECT_EQ(desc->getMovementFilter(), movementFilter);
  EXPECT_EQ(desc->getTemporalScales().size(), 2);

  for (size_t i = 0; i < tempScales.size(); i++)
    EXPECT_EQ(desc->getTemporalScales()[i], tempScales[i]);
}

TEST(OFCM, SampleOFCM) {
  int64 videoLength, videoWidth, videoHeight;
  int sampleX, sampleY, sampleL, strideX, strideY, strideL, step;
  cv::Mat image, output, loadedFeatures;
  std::vector<cv::Mat> video;
  std::vector<ssig::Cube> cuboids;
  cv::VideoCapture capture;
  std::string path;
  cv::FileStorage storageMatrix;
  cv::FileNode node, n1;


  /////////////////////////////////////////// Video Reading /////////////////////////////////////////////////
  step = 5;
  path = "person23_running_d4_uncomp.avi";
  capture.open(path);
  if (!capture.isOpened())
    std::cerr << "Error processing file. Can't read video " << path;
  videoLength = static_cast<int64>(capture.get(CV_CAP_PROP_FRAME_COUNT));
  videoWidth = static_cast<int64>(capture.get(CV_CAP_PROP_FRAME_WIDTH));
  videoHeight = static_cast<int64>(capture.get(CV_CAP_PROP_FRAME_HEIGHT));

  for (int64 frameStep = 0; frameStep < videoLength; frameStep += step) {
    capture.set(CV_CAP_PROP_POS_FRAMES, frameStep);
    capture.read((image));
    if (image.empty())
      std::cerr << "Error processing file. Can't read frame " << frameStep << "from video %s" << path;
    video.push_back(image.clone());
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////// Create cube vector (dense sampling) ////////////////////////////
  sampleX = 48;	sampleY = 48;	sampleL = 10;
  strideX = 24;	strideY = 24;	strideL = 5;
  for (int t = 0; t <= static_cast<int>(0 + video.size() - sampleL); t += strideL)  // video.size() instead of videoLength since we used a frameStep different from 1
    for (int y = 0; y <= static_cast<int>(0 + videoHeight - sampleY); y += strideY)
      for (int x = 0; x <= static_cast<int>(0 + videoWidth - sampleX); x += strideX)
        cuboids.push_back(ssig::Cube(x, y, t, sampleX, sampleY, sampleL));
  ////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////// OFCM feature computing //////////////////////////////////
  ssig::DescriptorTemporal *desc = new ssig::OFCM();
  desc->setData(video);
  desc->extract(cuboids, output);
  ////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////// Loading pre-computed OFCM features ////////////////////////////
  path = "OFCM_person23_running_d4_uncomp.yml";
  storageMatrix.open(path, cv::FileStorage::READ);
  node = storageMatrix.root();
  n1 = node["ActionRecognitionFeatures"];
  n1["Features"] >> loadedFeatures;
  ////////////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(output.cols, loadedFeatures.cols);
  EXPECT_EQ(output.rows, loadedFeatures.rows);

  for (int i = 0; i < loadedFeatures.rows; i++)
    for (int j = 0; j < loadedFeatures.cols; j++)
      EXPECT_NEAR(loadedFeatures.at<float>(i, j), output.at<float>(i, j), 0.001);  // if (loadedFeatures.at<float>(i, j) == output.at<float>(i, j))

  output.release();
  delete desc;
}
