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

#include "ssiglib/video/video.hpp"

#include <iostream>
#include <vector>
#include <string>

#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

namespace ssig {

  void readVideo(const std::string& videoname,
    const bool convert2BW,
    std::vector<cv::Mat>& frames,
    int& fps) {
  cv::VideoCapture capture;

  capture.open(videoname);
  if (!capture.isOpened()) {
    std::cout << "Error opening video!" << std::endl;
    exit(1);
  }

  int totalFrames = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_COUNT));
  fps = static_cast<int>(capture.get(cv::CAP_PROP_FPS));
  capture.set(cv::CAP_PROP_CONVERT_RGB, 1);

  frames.resize(totalFrames);
  cv::Mat frame;
  for (int i = 0; i < totalFrames; ++i) {
    int errorCode = capture.read(frame);
    if (convert2BW) {
      cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
    }
    frame.copyTo(frames[i]);
  }
}

}  // namespace ssig


