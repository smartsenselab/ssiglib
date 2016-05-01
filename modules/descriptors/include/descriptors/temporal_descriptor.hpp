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

#ifndef _SSIG_DESCRIPTORS_TEMPORAL_DESCRIPTOR_HPP_
#define _SSIG_DESCRIPTORS_TEMPORAL_DESCRIPTOR_HPP_

#include <descriptors/descriptor.hpp>

namespace ssig {
class TemporalDescriptors : Descriptor {
public:
  TemporalDescriptors(void);
  virtual ~TemporalDescriptors(void);
  TemporalDescriptors(const TemporalDescriptors& rhs);
  TemporalDescriptors& operator=(const TemporalDescriptors& rhs);

  /**
  On the first call to this function it returns the feature vector
  of the mat set up in the constructor call.

  @param out The matrix that will contain the feature vector for the current
  patch.
  */
  DESCRIPTORS_EXPORT void extract(cv::Mat& out);
  DESCRIPTORS_EXPORT void extract(const std::vector<cv::Rect>& windows,
    cv::Mat& output);
  DESCRIPTORS_EXPORT void extract(const std::vector<int>& depths,
    cv::Mat& output);
  DESCRIPTORS_EXPORT void extract(const std::vector<cv::Rect>& windows,
    const std::vector<int>& depths,
    cv::Mat& output);

  DESCRIPTORS_EXPORT void setData(const std::vector<cv::Mat>& data);


protected:
  DESCRIPTORS_EXPORT void read(const cv::FileNode& fn) override = 0;
  DESCRIPTORS_EXPORT void write(cv::FileStorage& fs) const override = 0;

  DESCRIPTORS_EXPORT virtual void beforeProcess() = 0;
  DESCRIPTORS_EXPORT virtual void extractFeatures(
    const cv::Rect& patch,
    const int depth,
    cv::Mat& output) = 0;

  void load(const std::string& filename, const std::string& nodename) override;
  void save(const std::string& filename, const std::string& nodename) const override;
private:
  // private members
  std::vector<cv::Rect> mWindows;
  std::vector<int> mdepths;
  std::vector<cv::Mat> mData;
  bool mIsPrepared = false;
  int mWidth, mHeight;
};
} // namespace ssig
#endif // !_SSIG_DESCRIPTORS_TEMPORAL_DESCRIPTOR_HPP_


