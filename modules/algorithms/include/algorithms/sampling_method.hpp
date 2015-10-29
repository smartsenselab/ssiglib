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

#ifndef _SSF_ALGORITHMS_SAMPLING_METHOD_HPP_
#define _SSF_ALGORITHMS_SAMPLING_METHOD_HPP_
#include <opencv2/core.hpp>
#include "alg_defs.hpp"

namespace ssf{

class SamplingMethod{

public:
  SamplingMethod(void);
  virtual ~SamplingMethod(void);
  SamplingMethod(const SamplingMethod& rhs);
  SamplingMethod& operator=(const SamplingMethod& rhs);

  ALG_EXPORT static std::vector<cv::Rect> sampleImage(const cv::Mat& img, 
    const int maxPatches, 
    const cv::Size& winSize);

  /**
  This method extracts sample windows from a specified Width and Height.

  @param width The width of the image to sample.
  @param height The height of the image to sample.
  @param winWidth The Width of the sampling window.
  @param winHeight The Height of the Sampling Window.
  @param strideX The horizontal stride the sampling window will slide. Range should be in [0,1].
  @param strideY The vertical stride the sampling window will slide. Range should be in [0,1].

  @return A vector of cv::Rects. Each Rect is a sample of the image.
  */
  ALG_EXPORT static std::vector<cv::Rect> sampleImage(
    const int width,
    const int height,
    const int winWidth,
    const int winHeight,
    const float strideX,
    const float strideY);

  /**
  This method extracts sample windows from a specified Width and Height.

  @param width The width of the image to sample.
  @param height The height of the image to sample.
  @param winWidth The Width of the sampling window.
  @param winHeight The Height of the Sampling Window.
  @param minScale The minimum scale of the sampling window.
  @param maxScale The maximum scale of the sampling window.
  @param nScales The number of different scales desired.
  @param strideX The horizontal stride the sampling window will slide. Range should be in [0,1].
  @param strideY The vertical stride the sampling window will slide. Range should be in [0,1].

  @return A vector of cv::Rects. Each Rect is a sample of the image.
  */
  ALG_EXPORT static std::vector<cv::Rect> sampleImage(const int width,
                                                      const int height,
                                                      const int winWidth,
                                                      const int winHeight,
                                                      const float minScale,
                                                      const float maxScale,
                                                      const int nScales,
                                                      const float strideX,
                                                      const float strideY);

  /**
  @param width The width of the image to sample.
  @param height The height of the image to sample.
  @param winWidth The Width of the sampling window.
  @param winHeight The Height of the Sampling Window.
  @param minScale The minimum scale of the sampling window.
  @param maxScale The maximum scale of the sampling window.
  @param deltaScale The increment in the minScale per iteration. Should be in Range (1, +inf].
  @param strideX The horizontal stride the sampling window will slide. Range should be in [0,1].
  @param strideY The vertical stride the sampling window will slide. Range should be in [0,1].

  @return A vector of cv::Rects. Each Rect is a sample of the image.
  */
  ALG_EXPORT static std::vector<cv::Rect> sampleImage(const int width,
                                                      const int height,
                                                      const int winWidth,
                                                      const int winHeight,
                                                      const float minScale,
                                                      const float maxScale,
                                                      const float deltaScale,
                                                      const float strideX,
                                                      const float strideY);

  //TODO: unimplemented
  /*std::vector<cv::Rect> sampleImage(const int width,
                                    const int height,
                                    const int winWidth,
                                    const int winHeight,
                                    const float minScale,
                                    const float maxScale,
                                    float deltaScale,
                                    const int nSamples,
                                    const float strideX,
                                    const float strideY) const;*/

private:
  //private members

};

}

#endif // !_SSF_ALGORITHMS_SAMPLING_METHOD_HPP_

