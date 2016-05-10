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
#include <opencv2/highgui.hpp>
#include "ssiglib/descriptors/dalal_mbh.hpp"
#include "ssiglib/video/optical_flow_farneback.hpp"
#include "ssiglib/video/video.hpp"

/*
TEST(HOF, SampleHOF) {
  // Automatically generated stub

  std::vector<cv::Mat> frames;
  ssig::readVideo("d:/Downloads/aw7z4Wx_460sv.mp4",
                                       frames, true);
  ssig::DalalMBH mbh(frames);
  mbh.setFrameCombination(ssig::FrameCombination::MAX_POOL);
  auto of = cv::createOptFlow_DualTVL1();
  
  auto of = ssig::OpticalFlowFarneback::create();
  mbh.setOpticalFlowMethod(of);
  cv::Mat out;
  mbh.extract(out);
  EXPECT_EQ(2, 2 + 2);
}
*/
/*
of->setGamma(0.5);
of->setInnerIterations(10);
of->setScalesNumber(4);
of->setOuterIterations(10);
of->setLambda(1);
of->setMedianFiltering(3);
*/
