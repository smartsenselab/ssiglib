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

#include <stdexcept>
#include "algorithms/sampling_method.hpp"

namespace ssf{

SamplingMethod::SamplingMethod(){
  //Constructor
}

SamplingMethod::~SamplingMethod(){
  //Destructor
}

SamplingMethod::SamplingMethod(const SamplingMethod& rhs){
  //Constructor Copy
}

SamplingMethod& SamplingMethod::operator=(const SamplingMethod& rhs){
  if(this != &rhs){
    //code here
  }
  return *this;
}

std::vector<cv::Rect> SamplingMethod::sampleImage(const int width,
                                                  const int height,
                                                  const int winWidth,
                                                  const int winHeight,
                                                  const float minScale,
                                                  const float maxScale,
                                                  const int nScales,
                                                  const float strideX,
                                                  const float strideY){
  if(width <= 0)
    throw std::invalid_argument("Width must be greater than 0");
  if(height <= 0)
    throw std::invalid_argument("height must be greater than 0");
  if(minScale > maxScale)
    throw std::invalid_argument("minScale must be greater than maxScale");

  float deltaScale = pow((maxScale / minScale), 1 / static_cast<float>(nScales));
  //int samples = ((height / winHeight)*(width / winWidth)) / (80 * 80)*nScales;
  std::vector<cv::Rect> rects;
  for(float scale = minScale; scale < maxScale; scale *= deltaScale){
    int h = static_cast<int>(winHeight * scale),
      w = static_cast<int>(winWidth * scale);
    for(int y = 0; y < height - h; y += static_cast<int>(strideY * h)){
      for(int x = 0; x < width - w; x += static_cast<int>(strideX * w)){
        cv::Rect rect(x, y, w, h);
        rects.push_back(rect);
      }
    }
  }
  if(rects.size() <= 0)
    throw std::runtime_error("No Rect produced for the set scales");
  return rects;
}

std::vector<cv::Rect> SamplingMethod::sampleImage(const int width,
                                                  const int height,
                                                  const int winWidth,
                                                  const int winHeight,
                                                  const float minScale,
                                                  const float maxScale,
                                                  const float deltaScale,
                                                  const float strideX,
                                                  const float strideY){
  if(width <= 0)
    throw std::invalid_argument("Width must be greater than 0");
  if(height <= 0)
    throw std::invalid_argument("height must be greater than 0");
  if(deltaScale <= 1){
    throw std::invalid_argument("delta Scale must be greater than 1 or it will enter infinite loop");
  }
  if(minScale > maxScale)
    throw std::invalid_argument("minScale must be greater than maxScale");

  std::vector<cv::Rect> rects;
  for(float scale = minScale; scale < maxScale; scale *= deltaScale){
    int h = static_cast<int>(winHeight * scale),
      w = static_cast<int>(winWidth * scale);
    for(int y = 0; y < height - h; y += static_cast<int>(strideY * h)){
      for(int x = 0; x < width - w; x += static_cast<int>(strideX * w)){
        cv::Rect rect(x, y, w, h);
        rects.push_back(rect);
      }
    }
  }
  if(rects.size() <= 0)
    throw std::runtime_error("No Rect produced for the scales set");
  return rects;
}

}
