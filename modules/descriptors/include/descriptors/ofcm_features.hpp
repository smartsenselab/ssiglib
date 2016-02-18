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

#ifndef _SSIG_DESCRIPTORS_OFCM_FEATURES_HPP_
#define _SSIG_DESCRIPTORS_OFCM_FEATURES_HPP_

#include <deque>
#include <opencv2\video\tracking.hpp>

#include "core\exception.hpp"
#include "descriptor_temporal.hpp"
#include "descriptors\co_occurrence_general.hpp"

namespace ssig {

class OFCM : public DescriptorTemporal {

 typedef	std::pair<cv::Mat_<int>, cv::Mat_<int>> ParMat;

 public:
	DESCRIPTORS_EXPORT OFCM(void);
	DESCRIPTORS_EXPORT virtual ~OFCM(void);
	DESCRIPTORS_EXPORT OFCM(const OFCM& rhs);
	DESCRIPTORS_EXPORT OFCM& operator=(const OFCM& rhs);

protected:
	CORE_EXPORT void read(const cv::FileNode& fn) override {}
	CORE_EXPORT void write(cv::FileStorage& fs) const override {}

	DESCRIPTORS_EXPORT void beforeProcess() override;
	DESCRIPTORS_EXPORT void extractFeatures(const ssig::Cube& cuboid, cv::Mat& output) override;

private:
	bool movementFilter = true;

	int numImgs;
	int nBinsMagnitude;
	int nBinsAngle;
	int distanceMagnitude;
	int distanceAngle;
	int descriptorLength;
	int cuboidLength;
	int **mapToOpticalFlows;
	int numOpticalFlow = 0; //number of computed optical flows
	int logQuantization = 0;

	float maxAngle;
	float maxMagnitude;

	CoOccurrenceGeneral *coocMagnitude;
	CoOccurrenceGeneral *coocAngles;
	
	std::vector<ParMat> data;
	std::vector<int> temporalScales;

	std::string strTempScales;

	void setParameters();
	void setOpticalFlowData();
	int calcNumOptcialFlowPerCuboid();
	std::vector<int> splitTemporalScales(std::string str, char delimiter);

	inline std::deque<ParMat> CreatePatch(const ssig::Cube& cuboid, bool & hasMovement);
	inline void FillPoints(std::vector<cv::Point2f> &vecPoints, cv::Mat frameB, cv::Mat frameA, int thr = 30);
	inline void VecDesp2Mat(std::vector<cv::Point2f> &vecPoints, std::vector<cv::Point2f> &positions, OFCM::ParMat & AMmat);
	inline void allocateMapToOpticalFlowsMatrix();

};
}  // namespace ssig
#endif  // !_SSIG_DESCRIPTORS_OFCM_FEATURES_HPP_
