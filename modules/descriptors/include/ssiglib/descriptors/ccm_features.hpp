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

#ifndef _SSIG_DESCRIPTORS_CCM_FEATURES_HPP_
#define _SSIG_DESCRIPTORS_CCM_FEATURES_HPP_

#include <vector>

#include <opencv2/core.hpp>

#include "descriptor_2d.hpp"


namespace ssig {
class ColorCoOccurrence : public Descriptor2D {
 public:
    DESCRIPTORS_EXPORT explicit ColorCoOccurrence(const cv::Mat& input);
    DESCRIPTORS_EXPORT explicit ColorCoOccurrence(const cv::Mat& input,
      const ColorCoOccurrence& descriptor);
    DESCRIPTORS_EXPORT explicit ColorCoOccurrence(
      const ColorCoOccurrence& descriptor);

    DESCRIPTORS_EXPORT virtual ~ColorCoOccurrence(void) = default;


    DESCRIPTORS_EXPORT std::vector<int> getLevels() const;
    DESCRIPTORS_EXPORT void setLevels(const std::vector<int>& levels);
    DESCRIPTORS_EXPORT std::vector<int> getBins() const;
    DESCRIPTORS_EXPORT void setBins(const std::vector<int>& bins);

    // Set the direction to count the co-occurrence
    DESCRIPTORS_EXPORT void setDirection(int x, int y);

 protected:
    DESCRIPTORS_EXPORT void read(const cv::FileNode& fn) override;
    DESCRIPTORS_EXPORT void write(cv::FileStorage& fs) const override;
    DESCRIPTORS_EXPORT void beforeProcess() override;
    DESCRIPTORS_EXPORT void extractFeatures(const cv::Rect& patch,
      cv::Mat& output) override;

 private:
    // private members
    // the number of levels in each channel
    std::vector<int> mLevels;
    std::vector<int> mBins;

    int mDi = 0, mDj = 1;

    std::vector<cv::Mat> mChannels;
};
}  // namespace ssig
#endif  // !_SSIG_DESCRIPTORS_CCM_FEATURES_HPP_


