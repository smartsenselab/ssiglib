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

#ifndef _SSF_ALGORITHMS_HOG_FEATURES_HPP_
#define _SSF_ALGORITHMS_HOG_FEATURES_HPP_
#include "descriptor_interface.hpp"

namespace ssf{

class HOG : public DescriptorInterface{
  cv::Size mBlockConfiguration;
  cv::Size mCellConfiguration;
  cv::Size mBlockStride;
  int mNumberOfBins;
  float mClipping = 0.2f;

  std::vector<cv::Mat_<float>> mIntegralImages;
public:
  ALG_EXPORT HOG() = default;
  ALG_EXPORT virtual ~HOG(void) = default;

  ALG_EXPORT virtual DescriptorInterface* clone() const override;
  ALG_EXPORT virtual void setup(const cv::Mat& img) override;
  ALG_EXPORT virtual void extract(const cv::Rect& patch, cv::Mat& out) override;
  ALG_EXPORT virtual bool hasVisualization() override;
  ALG_EXPORT static void getVisualization(const cv::Mat_<float> feat,
                                          const int nBins,
                                          const cv::Size& blockSize,
                                          const cv::Size& blockStride,
                                          const cv::Size& cellSize,
                                          const cv::Size& imgSize,
                                          cv::Mat& vis);


  ALG_EXPORT cv::Size getBlockConfiguration() const;

  ALG_EXPORT void setBlockConfiguration(const cv::Size& blockConfiguration);

  ALG_EXPORT cv::Size getBlockStride() const{
    return mBlockStride;
  }

  ALG_EXPORT void setBlockStride(const cv::Size& blockStride){
    mBlockStride = blockStride;
  }

  ALG_EXPORT cv::Size getCellConfiguration() const;

  ALG_EXPORT void setCellConfiguration(const cv::Size& cellConfiguration);

  ALG_EXPORT int getNumberOfBins() const;

  ALG_EXPORT void setNumberOfBins(int numberOfBins);

  ALG_EXPORT float getClipping() const{
    return mClipping;
  }

  ALG_EXPORT void setClipping(float clipping1){
    mClipping = clipping1;
  }


private:
  //private members

  std::vector<cv::Mat_<float>> getIntegralGradientImage(const cv::Mat& img) const;

  void getBlockDescriptor(int x, int y, const std::vector<cv::Mat_<float>>& integralImages, cv::Mat_<float>& out);

  static void generateBlockVisualization(const cv::Mat_<float>& blockFeatures,
                                         const int nBins,
                                         cv::Mat& visualization);

};

}

#endif // !_SSF_ALGORITHMS_HOG_FEATURES_HPP_

