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

#include "ssiglib/descriptors/ofcm_features.hpp"

std::vector<int> splitTemporalScales(std::string str, char delimiter);

namespace ssig {

OFCM::OFCM() {
  // Default values
  this->nBinsMagnitude = 8;
  this->nBinsAngle = 8;
  this->distanceMagnitude = 1;
  this->distanceAngle = 1;
  this->cuboidLength = 10;
  this->maxMagnitude = 15;
  this->maxAngle = 361.0;
  // max val of Angle is 360. We sum 1 more to fit on nBinsAngle.
  // If 360 / (360 / 4) it will go to the bin 4, but it is from 0 to 3.
  // (int)floor(angle / (this->maxAngle / this->nBinsAngle));
  this->logQuantization = 1;
  this->movementFilter = 1;
  this->temporalScales.push_back(1);
  this->extractionType = ExtractionType::HaralickFeatures;  // default

  this->coocMagnitude = NULL;
  this->coocAngles = NULL;
  this->mapToOpticalFlows = NULL;
}

OFCM::OFCM(int nBinsMagnitude, int nBinsAngle, int distanceMagnitude,
  int distanceAngle, int cuboidLength, float maxMagnitude, int logQuantization,
  bool movementFilter, std::vector<int> temporalScales,
  ExtractionType extractionType) {
  this->nBinsMagnitude = nBinsMagnitude;
  this->nBinsAngle = nBinsAngle;
  this->distanceMagnitude = distanceMagnitude;
  this->distanceAngle = distanceAngle;
  this->cuboidLength = cuboidLength;
  this->movementFilter = movementFilter;
  this->extractionType = extractionType;

  if (logQuantization == 1) {
    this->logQuantization = logQuantization;
    this->maxMagnitude = 15;  // default
  }
  else
    this->maxMagnitude = maxMagnitude;

  for (auto v : temporalScales)
    this->temporalScales.push_back(v);

  this->maxAngle = 361.0;
  // max val of Angle is 360. We sum 1 more to fit on nBinsAngle.
  // If 360 / (360 / 4) it will go to the bin 4, but it is from 0 to 3.
  // (int)floor(angle / (this->maxAngle / this->nBinsAngle));
  // extractionType = 0;

  this->coocMagnitude = NULL;
  this->coocAngles = NULL;
  this->mapToOpticalFlows = NULL;
}

OFCM::~OFCM() {
  for (int i = 0; i < static_cast<int>(data.size()); i++) {
    this->data[i].first.release();
    this->data[i].second.release();
  }
  this->data.clear();

  if (this->coocMagnitude != NULL) {
    delete this->coocMagnitude;
    this->coocMagnitude = NULL;
  }
  if (this->coocAngles != NULL) {
    delete this->coocAngles;
    this->coocAngles = NULL;
  }
  if (this->mapToOpticalFlows != NULL) {
    for (int i = 0; i < numImgs; i++)
      delete[] this->mapToOpticalFlows[i];
    delete[] this->mapToOpticalFlows;
    this->mapToOpticalFlows = NULL;
  }
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
  bool hasMovement = !movementFilter;  // f. to eliminate pacthes w/out movement
  std::deque<ParMat> patches;
  patches = CreatePatch(cuboid, hasMovement);
  output.release();

  // verify sif there is any movement
  if (hasMovement) {
    for (int i = 0, k = 0; i < patches.size(); i++) {
      std::vector<cv::Mat> mMagnitude, mAngles;

      coocMagnitude->extractAllMatricesDirections(cv::Rect(0, 0, cuboid.w,
        cuboid.h),
        patches[i].second, mMagnitude);
      coocAngles->extractAllMatricesDirections(cv::Rect(0, 0, cuboid.w,
        cuboid.h),
        patches[i].first, mAngles);

      switch (this->extractionType) {
      case ExtractionType::HaralickFeatures:
        extractHaralickFeatures(mMagnitude, mAngles, output);
        break;
      case ExtractionType::VectorizedMatrices:
        extractVectorizedMatrices(mMagnitude, mAngles, output);
        break;
      case ExtractionType::ConcatVectorizedHaralick:
        extractConcatVectorizedHaralick(mMagnitude, mAngles, output);
        break;
      default:
        extractHaralickFeatures(mMagnitude, mAngles, output);
      }
    }
    output = output.reshape(0, 1);
  }
  patches.clear();
}

void OFCM::extractHaralickFeatures(std::vector<cv::Mat>& mMagnitude,
  std::vector<cv::Mat>& mAngles, cv::Mat& output) {
  for (cv::Mat &degreeMat : mMagnitude)
    output.push_back(Haralick::computeOld(degreeMat));

  for (cv::Mat &degreeMat : mAngles)
    output.push_back(Haralick::computeOld(degreeMat));
}

void OFCM::extractVectorizedMatrices(std::vector<cv::Mat>& mMagnitude,
  std::vector<cv::Mat>& mAngles, cv::Mat& output) {
  cv::Mat outputMag, outputAng, outputConcat;

  for (cv::Mat &degreeMat : mMagnitude)
    outputMag.push_back(degreeMat);

  for (cv::Mat &degreeMat : mAngles)
    outputAng.push_back(degreeMat);

  outputMag = outputMag.reshape(0, 1);
  outputAng = outputAng.reshape(0, 1);

  cv::hconcat(outputMag, outputAng, outputConcat);
  output.push_back(outputConcat.clone());
}

void OFCM::extractConcatVectorizedHaralick(std::vector<cv::Mat>& mMagnitude,
  std::vector<cv::Mat>& mAngles, cv::Mat& output) {
  cv::Mat outputHarFeat, outputVecMat, outputConcat;

  extractHaralickFeatures(mMagnitude, mAngles, outputHarFeat);
  extractVectorizedMatrices(mMagnitude, mAngles, outputVecMat);

  outputHarFeat = outputHarFeat.reshape(0, 1);
  cv::hconcat(outputHarFeat, outputVecMat, outputConcat);
  output.push_back(outputConcat.clone());
}

void OFCM::release() {
  mImages.clear();
  mIsPrepared = false;

  for (int i = 0; i < static_cast<int>(data.size()); i++) {
    this->data[i].first.release();
    this->data[i].second.release();
  }
  this->data.clear();

  if (this->coocMagnitude != NULL) {
    delete this->coocMagnitude;
    this->coocMagnitude = NULL;
  }
  if (this->coocAngles != NULL) {
    delete this->coocAngles;
    this->coocAngles = NULL;
  }
  if (this->mapToOpticalFlows != NULL) {
    for (int i = 0; i < numImgs; i++)
      delete[] this->mapToOpticalFlows[i];
    delete[] this->mapToOpticalFlows;
    this->mapToOpticalFlows = NULL;
  }
}

//////////////// Aditional Auxiliary Functions ////////////////
void OFCM::setOpticalFlowData() {
  data.clear();
  std::vector<cv::Point2f> points[2], basePoints;
  std::vector<uchar> status;
  std::vector<float> err;
  cv::Size winSize(31, 31);
  cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20,
    0.3);
  int rows, cols;

  rows = mImages[0].rows;
  cols = mImages[0].cols;

  this->numImgs = static_cast<int>(mImages.size());
  allocateMapToOpticalFlowsMatrix();

  for (int t : this->temporalScales) {
    for (int i = 0; i < static_cast<int>(mImages.size()); i++) {
      int j = i + t;  // image to process with i
      if (j < static_cast<int>(mImages.size())) {
        FillPoints(points[0], mImages[j], mImages[i]);

        ParMat angles_magni;
        angles_magni.first = cv::Mat(rows, cols, CV_16SC1, -1);  // angles
        angles_magni.second = cv::Mat(rows, cols, CV_16SC1, -1);  // magnitude

        if (points[0].size() > 0) {
          cv::calcOpticalFlowPyrLK(mImages[i], mImages[j], points[0], points[1],
            status, err, winSize, 3, termcrit, 0, 0.001);
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
  // 4 co-occurrence matrices (0, 45, 90, 135)
  int tamVecMagniMatrices = 4 * (this->nBinsMagnitude * this->nBinsMagnitude);
  // 4 co-occurrence matrices (0, 45, 90, 135)
  int tamVecAngleMatrices = 4 * (this->nBinsAngle * this->nBinsAngle);

  coocMagnitude = new CoOccurrenceGeneral(this->nBinsMagnitude,
    this->distanceMagnitude);
  coocAngles = new CoOccurrenceGeneral(this->nBinsAngle, this->distanceAngle);

  this->numOpticalFlow = calcNumOptcialFlowPerCuboid();

  // It is(4 direction matrices * 12 Haralick texture features) * 2,
  // because we have one magnitude matrix and one angle matrix,
  // *numOpticalFlow, the number of optical flow will depend on temporal scale.
  switch (this->extractionType) {
  case ExtractionType::HaralickFeatures:
    this->descriptorLength = ((4 * 12) + (4 * 12)) * this->numOpticalFlow;
    break;
  case ExtractionType::VectorizedMatrices:
    this->descriptorLength = (tamVecMagniMatrices + tamVecAngleMatrices) *
      this->numOpticalFlow;
    break;
  case ExtractionType::ConcatVectorizedHaralick:
    this->descriptorLength = (tamVecMagniMatrices + tamVecAngleMatrices +
      (4 * 12) + (4 * 12)) * this->numOpticalFlow;
    break;
  default:
    this->extractionType = ExtractionType::HaralickFeatures;
    this->descriptorLength = ((4 * 12) + (4 * 12)) * this->numOpticalFlow;
  }
}

inline void OFCM::FillPoints(std::vector<cv::Point2f> &vecPoints, cv::Mat
  frameB, cv::Mat frameA, int thr) {
  vecPoints.clear();
  cvtColor(frameB, frameB, CV_BGR2GRAY);
  cvtColor(frameA, frameA, CV_BGR2GRAY);

  cv::Mat frameDif = cv::abs(frameB - frameA);
  for (int i = 0; i < frameDif.rows; ++i) {
    for (int j = 0; j< frameDif.cols; ++j) {
      if (frameDif.at<uchar>(i, j) > thr)
        vecPoints.push_back(cv::Point2f(static_cast<float>(j),
        static_cast<float>(i)));
    }
  }
}

int OFCM::calcNumOptcialFlowPerCuboid() {
  int numOpticalFlow = 0;
  for (size_t i = 0; i < this->cuboidLength; i++) {
    for (size_t j : this->temporalScales) {
      size_t k = i + j;  // image to process with i
      if (k < this->cuboidLength)  // if (k >= 0)
        numOpticalFlow++;
      else
        break;
    }
  }
  return numOpticalFlow;
}

inline void OFCM::VecDesp2Mat(std::vector<cv::Point2f> &vecPoints,
  std::vector<cv::Point2f> &positions, OFCM::ParMat & AMmat) {
  int x, y, valAngle, valMagnitude;
  float magnitude, angle, catetoOposto, catetoAdjacente;

  for (int i = 0; i < static_cast<int>(positions.size()); ++i) {
    catetoOposto = vecPoints[i].y - positions[i].y;
    catetoAdjacente = vecPoints[i].x - positions[i].x;

    magnitude = sqrt((catetoAdjacente * catetoAdjacente) + (catetoOposto *
      catetoOposto));

    angle = static_cast<float> (atan2f(catetoOposto, catetoAdjacente) * 180 /
      CV_PI);
    if (angle < 0)
      angle += 360;

    valAngle = static_cast<float>(floor(angle / (this->maxAngle /
      this->nBinsAngle)));

    if (logQuantization == 1)
      valMagnitude = static_cast<int>(floor(log2(magnitude)));
    else
      valMagnitude = static_cast<int>(floor(magnitude / (this->maxMagnitude /
      this->nBinsMagnitude)));

    if (valMagnitude < 0)  // e.g., log2(0)
      valMagnitude = 0;  // send to the first bin

    if (valMagnitude >= this->nBinsMagnitude)
      valMagnitude = this->nBinsMagnitude - 1;  // send to the last bin

    y = static_cast<int>(positions[i].y);
    x = static_cast<int>(positions[i].x);

    AMmat.first(y, x) = valAngle;
    AMmat.second(y, x) = valMagnitude;
  }
}

inline void OFCM::allocateMapToOpticalFlowsMatrix() {
  this->mapToOpticalFlows = new int*[this->numImgs];
  for (int i = 0; i < this->numImgs; i++) {
    this->mapToOpticalFlows[i] = new int[this->numImgs];
    memset(this->mapToOpticalFlows[i], 0, sizeof(int) * this->numImgs);
  }
}

inline std::deque<OFCM::ParMat> OFCM::CreatePatch(const ssig::Cube& cuboid,
  bool & hasMovement) {
  std::deque<ParMat> patches;
  cv::Mat patchAngles, patchMagni;
  int thr = 1;  // it's already quantized so zero is a movement from "bin 0"

  int t1 = cuboid.l + cuboid.t0 - 1;

  for (size_t ts : this->temporalScales) {
    for (size_t i = cuboid.t0; i < t1; i++) {
      size_t f = i + ts;  // image to process with i
      // if (f >= t0)
      if (f <= t1) {
        int optFlowPos = this->mapToOpticalFlows[i][f];
        ParMat angles_magni;

        // on "first" we have the angles
        patchAngles = cv::Mat(this->data[optFlowPos].first,
          cv::Rect(cuboid.x0, cuboid.y0, cuboid.w, cuboid.h));
        // on "second" we have the magnitudes
        patchMagni = cv::Mat(this->data[optFlowPos].second,
          cv::Rect(cuboid.x0, cuboid.y0, cuboid.w, cuboid.h));

        angles_magni.first = patchAngles.clone();
        angles_magni.second = patchMagni.clone();

        patches.push_back(angles_magni);

        // if movement was not detected yet
        if (!hasMovement) {
          for (int j = 0; j < patchMagni.rows; ++j)
            for (int k = 0; k < patchMagni.cols; ++k)
              if (patchMagni.at<int>(j, k) >= thr) {
                hasMovement = true;
                k = patchMagni.cols; j = patchMagni.rows;
              }
        }
      }
      else
        break;
    }
  }

  return patches;
}
/////////////////////////////////////////////////////

//////////////// Getters and Setters ////////////////
bool OFCM::getMovementFilter() { return movementFilter; }
int OFCM::getnBinsMagnitude() {	return nBinsMagnitude; }
int OFCM::getnBinsAngle() {	return nBinsAngle; }
int OFCM::getDistanceMagnitude() { return distanceMagnitude; }
int OFCM::getDistanceAngle() { return distanceAngle; }
int OFCM::getCuboidLength() { return cuboidLength; }
int OFCM::getLogQuantization() { return logQuantization; }
float OFCM::getMaxMagnitude() { return maxMagnitude; }
float OFCM::getMaxAngle() { return maxAngle; }
int OFCM::getDescriptorLength() { return descriptorLength; }
int OFCM::getNumOpticalFlow() { return numOpticalFlow; }
std::vector<int> OFCM::getTemporalScales() { return temporalScales; }
int OFCM::getDescriptorDataType() { return CV_32F; }

void OFCM::setMovementFilter(bool movementFilter)
{ this->movementFilter = movementFilter; }
void OFCM::setnBinsMagnitude(int nBinsMagnitude)
{ this->nBinsMagnitude = nBinsMagnitude; }
void OFCM::setnBinsAngle(int nBinsAngle)
{ this->nBinsAngle = nBinsAngle;}
void OFCM::setDistanceMagnitude(int distanceMagnitude)
{ this->distanceMagnitude = distanceMagnitude; }
void OFCM::setDistanceAngle(int distanceAngle)
{ this->distanceAngle = distanceAngle; }
void OFCM::setCuboidLength(int cuboidLength)
{ this->cuboidLength = cuboidLength; }
void OFCM::setLogQuantization(int logQuantization)
{ this->logQuantization = logQuantization; }
void OFCM::setMaxMagnitude(float maxMagnitude)
{ this->maxMagnitude = maxMagnitude; }
void OFCM::setTemporalScales(std::vector<int> temporalScales) {
  this->temporalScales.clear();
  for (auto v : temporalScales)
    this->temporalScales.push_back(v);
}
/////////////////////////////////////////////////////

}  // namespace ssig
