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

#include "descriptors/ofcm_features.hpp"

std::vector<int> splitTemporalScales(std::string str, char delimiter);

namespace ssig {

OFCM::OFCM() {
  // Constructor
}

OFCM::~OFCM() {

	for (int i = 0; i < (int)data.size(); i++)
	{
		this->data[i].first.release();
		this->data[i].second.release();
	}
	this->data.clear();

	if (this->coocMagnitude != NULL)
		delete this->coocMagnitude;

	if (this->coocAngles != NULL)
		delete this->coocAngles;

	for (int i = 0; i < numImgs; i++)
		delete[] this->mapToOpticalFlows[i];
	delete[] this->mapToOpticalFlows;

}

OFCM::OFCM(const OFCM& rhs) {
  // Constructor Copy
}

OFCM& OFCM::operator=(const OFCM& rhs) {
  if (this != &rhs) {
    // code here
  }
  return *this;
}

void OFCM::beforeProcess() {
	if (mImages.empty())
		throw Exception("Images must be inserted first");

	setParameters();
	setOpticalFlowData();
}

void OFCM::extractFeatures(const ssig::Cube& cuboid, cv::Mat& output) {
	bool is_verbose = false;
	bool hasMovement = !movementFilter; //false to eliminate pacthes without movement
	std::deque<ParMat> patches;
	patches = CreatePatch(cuboid, hasMovement);
	output.release();

	if (hasMovement) //verificar se tem movimento
	{
		output.create(1, this->descriptorLength, CV_32FC1);

		for (int i = 0, k = 0; i < patches.size(); i++)
		{
			std::vector<cv::Mat> mMagnitude, mAngles;

			coocMagnitude->extractAllMatricesDirections(cv::Rect(0, 0, cuboid.w, cuboid.h), patches[i].second, mMagnitude);
			coocAngles->extractAllMatricesDirections(cv::Rect(0, 0, cuboid.w, cuboid.h), patches[i].first, mAngles);

			//TODO: implementar chamada das Haralicks


			//TODO: implementar a combinação das deatures.
			/*
			for (int j = 0; j < coocMagnitude->getNFeatures(); j++, k++)
			{
				float feat = mMagnitude.at<float>(0, j);
				output.at<float>(0, k) = static_cast<float>(feat);
			}
			for (int j = 0; j < coocAngles->getNFeatures(); j++, k++)
			{
				float feat = mAngles.at<float>(0, j);
				output.at<float>(0, k) = static_cast<float>(feat);
			}
			*/
		}
	}
	patches.clear();

}

/////////////////////////////////Aditional Auxiliary Functions//////////////////////////////////////
void OFCM::setOpticalFlowData() {
	data.clear();
	std::vector<cv::Point2f> points[2], basePoints;
	std::vector<uchar> status;
	std::vector<float> err;
	cv::Size winSize(31, 31);
	cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.3);
	int rows, cols;

	rows = mImages[0].rows;
	cols = mImages[0].cols;

	this->numImgs = static_cast<int>(mImages.size());
	allocateMapToOpticalFlowsMatrix();

	for (int t : this->temporalScales)
	{
		for (int i = 0; i < static_cast<int>(mImages.size()); i++)
		{
			int j = i + t; //image to process with i
			if (j < (int)mImages.size())
			{
				FillPoints(points[0], mImages[j], mImages[i]);

				ParMat angles_magni;
				angles_magni.first = cv::Mat(rows, cols, CV_16SC1, -1); //angles
				angles_magni.second = cv::Mat(rows, cols, CV_16SC1, -1); //magnitude

				if (points[0].size() > 0)
				{
					calcOpticalFlowPyrLK(mImages[i], mImages[j], points[0], points[1], status, err, winSize, 3, termcrit, 0, 0.001);
					VecDesp2Mat(points[1], points[0], angles_magni);
				}

				this->data.push_back(angles_magni);
				this->mapToOpticalFlows[i][j] = static_cast<int>(this->data.size()) - 1;
				this->mapToOpticalFlows[j][i] = static_cast<int>(this->data.size()) - 1;
			}
			else
				break;
		}
	}
}

void OFCM::setParameters() {

	int tamVecMagniMatrices = 4 * (this->nBinsMagnitude * this->nBinsMagnitude); // 4 co-occurrence matrices (0, 45, 90, 135)
	int tamVecAngleMatrices = 4 * (this->nBinsAngle * this->nBinsAngle); // 4 co-occurrence matrices (0, 45, 90, 135)

	this->temporalScales = splitTemporalScales(strTempScales, ',');

	coocMagnitude = new CoOccurrenceGeneral(this->nBinsMagnitude, this->distanceMagnitude);
	coocAngles = new CoOccurrenceGeneral(this->nBinsAngle, this->distanceAngle);

	this->numOpticalFlow = calcNumOptcialFlowPerCuboid();

	// It is(4 direction matrices * 12 Haralick texture features) * 2, because we have one magnitude matrix and one angle matrix, *numOpticalFlow, the number of optical flow will depend on temporal scale.
	this->descriptorLength = ((4 * 12) + (4 * 12)) * this->numOpticalFlow;
}

inline void OFCM::FillPoints(std::vector<cv::Point2f> &vecPoints, cv::Mat frameB, cv::Mat frameA, int thr)
{
	vecPoints.clear();
	cvtColor(frameB, frameB, CV_BGR2GRAY);
	cvtColor(frameA, frameA, CV_BGR2GRAY);

	cv::Mat frameDif = cv::abs(frameB - frameA);
	for (int i = 0; i < frameDif.rows; ++i)
	{
		for (int j = 0; j< frameDif.cols; ++j)
		{
			if (frameDif.at<uchar>(i, j) > thr)
				vecPoints.push_back(cv::Point2f((float)j, (float)i));
		}
	}
}

int OFCM::calcNumOptcialFlowPerCuboid() {
	int numOpticalFlow = 0;
	for (size_t i = 0; i < this->cuboidLength; i++) //for (int i = 1; i < this->cuboidLength; i++)
	{
		for (size_t j : this->temporalScales) //for (int j = 1; j <= this->temporalScale; j++)
		{
			size_t k = i + j; //image to process with i
			if (k < this->cuboidLength) //if (k >= 0)
				numOpticalFlow++;
			else
				break;
		}
	}
	return numOpticalFlow;
}

inline void OFCM::VecDesp2Mat(std::vector<cv::Point2f> &vecPoints, std::vector<cv::Point2f> &positions, OFCM::ParMat & AMmat)
{
	int x, y, valAngle, valMagnitude;
	float magnitude, angle, catetoOposto, catetoAdjacente;

	for (int i = 0; i < static_cast<int>(positions.size()); ++i)
	{
		catetoOposto = vecPoints[i].y - positions[i].y;
		catetoAdjacente = vecPoints[i].x - positions[i].x;

		magnitude = sqrt((catetoAdjacente * catetoAdjacente) + (catetoOposto * catetoOposto));

		angle = static_cast<float> (atan2f(catetoOposto, catetoAdjacente) * 180 / CV_PI);
		if (angle < 0)
			angle += 360;

		valAngle = (int)floor(angle / (this->maxAngle / this->nBinsAngle));

		if (logQuantization == 1)
			valMagnitude = (int)floor(log2(magnitude));
		else
			valMagnitude = (int)floor(magnitude / (this->maxMagnitude / this->nBinsMagnitude));

		if (valMagnitude < 0) // e.g., log2(0)
			valMagnitude = 0; //send to the first bin

		if (valMagnitude >= this->nBinsMagnitude)
			valMagnitude = this->nBinsMagnitude - 1; //send to the last bin

		y = static_cast<int>(positions[i].y);
		x = static_cast<int>(positions[i].x);

		AMmat.first(y, x) = valAngle;
		AMmat.second(y, x) = valMagnitude;
	}
}

inline void OFCM::allocateMapToOpticalFlowsMatrix()
{
	this->mapToOpticalFlows = new int*[this->numImgs];
	for (int i = 0; i < this->numImgs; i++)
	{
		this->mapToOpticalFlows[i] = new int[this->numImgs];
		memset(this->mapToOpticalFlows[i], 0, sizeof(int) * this->numImgs);
	}
}

std::vector<int> OFCM::splitTemporalScales(std::string str, char delimiter)
{
	std::vector<int> internal;
	std::stringstream ss(str);
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		int ts = atoi(tok.c_str());
		internal.push_back(ts);
	}

	return internal;
}

inline std::deque<OFCM::ParMat> OFCM::CreatePatch(const ssig::Cube& cuboid, bool & hasMovement)
{
	std::deque<ParMat> patches;
	cv::Mat patchAngles, patchMagni;

	int thr = 1;
	int t1 = cuboid.l + cuboid.t0 - 1;

	for (size_t ts : this->temporalScales) //for (int ts = 1; ts <= this->temporalScale; ts++)
	{
		for (size_t i = cuboid.t0; i < t1; i++)//for (size_t i = t0+1; i <= t1; i++) //it starts from frame 1 to compare with frame 0
		{
			size_t f = i + ts; //image to process with i
			if (f <= t1) //if (f >= t0)
			{
				int optFlowPos = this->mapToOpticalFlows[i][f];
				ParMat angles_magni;

				patchAngles = cv::Mat(this->data[optFlowPos].first, cv::Rect(cuboid.x0, cuboid.y0, cuboid.w, cuboid.h)); //on "first" we have the angles
				patchMagni = cv::Mat(this->data[optFlowPos].second, cv::Rect(cuboid.x0, cuboid.y0, cuboid.w, cuboid.h)); //on "second" we have the magnitudes

				angles_magni.first = patchAngles.clone();
				angles_magni.second = patchMagni.clone();

				patches.push_back(angles_magni);

				if (!hasMovement) //if movement was not detected yet
				{
					for (int j = 0; j < patchMagni.rows; ++j)
						for (int k = 0; k < patchMagni.cols; ++k)
							if (patchMagni.at<int>(j, k) >= thr)
							{
						hasMovement = true;
						k = patchMagni.cols; j = patchMagni.rows; // just to get out of this 2 loops
							}
				}
			}
			else
				break;
		}
	}

	return patches;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace ssig
