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

#include "ssiglib/descriptors/co_occurrence_general.hpp"

namespace ssig {
  CoOccurrenceGeneral::CoOccurrenceGeneral(int nbins, int distance) {
    // Constructor
    this->nbins = nbins;
    this->distance = distance;

    M0.create(this->nbins, this->nbins);
    M45.create(this->nbins, this->nbins);
    M90.create(this->nbins, this->nbins);
    M135.create(this->nbins, this->nbins);
  }

  CoOccurrenceGeneral::~CoOccurrenceGeneral() {
    // Destructor
  }

  CoOccurrenceGeneral::CoOccurrenceGeneral(const CoOccurrenceGeneral& descriptor) {
    // Constructor Copy
    this->nbins = descriptor.nbins;
    this->distance = descriptor.distance;

    M0 = descriptor.M0.clone();
    M45 = descriptor.M45.clone();
    M90 = descriptor.M90.clone();
    M135 = descriptor.M135.clone();
  }

  CoOccurrenceGeneral& CoOccurrenceGeneral::operator=(const CoOccurrenceGeneral& rhs) {
    if (this != &rhs) {
      // code here
    }
    return *this;
  }

  int CoOccurrenceGeneral::getnBins() const {
    return this->nbins;
  }

  int CoOccurrenceGeneral::getDistance() const {
    return this->distance;
  }

  int CoOccurrenceGeneral::getNFeatures() {
    return 4 * FEATURESCG;
  }


  void CoOccurrenceGeneral::setnBins(const int nbins) {
    this->nbins = nbins;

    M0.release();
    M0.create(this->nbins, this->nbins);
    M45.release();
    M45.create(this->nbins, this->nbins);
    M90.release();
    M90.create(this->nbins, this->nbins);
    M135.release();
    M135.create(this->nbins, this->nbins);
  }

  void CoOccurrenceGeneral::setDistance(const int distance) {
    this->distance = distance;
  }

  void CoOccurrenceGeneral::extractMatrix0(const cv::Rect& patch, cv::Mat_<int> &img, cv::Mat& output) {
    float R0 = 0.0f;
    int d, x, y;

    /* Inicializacoes */
    d = this->distance;

    /*Initializes the matrices*/
    M0 = cv::Mat::zeros(this->nbins, this->nbins, CV_32F);

    for (int row = patch.y; row < patch.height; row++) {
      for (int col = patch.x; col < patch.width; col++) {

        /* Calcula as matrizes */
        x = img(row, col);
        if (x == -1)
          continue;

        if (col + d < patch.width) {
          y = img(row, col + d);
          if (y == -1)
            continue;

          M0(y, x)++;
          M0(x, y)++;
          R0++;

        }

      }
    }

    if (R0 == 0.0f)
      R0 = 1.0f;

    M0 = M0 / R0;

    output = M0.clone();
  }

  void CoOccurrenceGeneral::extractMatrix45(const cv::Rect& patch, cv::Mat_<int> &img, cv::Mat& output) {
    float R45 = 0.0f;
    int d, x, y;

    /* Inicializacoes */
    d = this->distance;

    /* Initializes the matrices */
    M45 = cv::Mat::zeros(this->nbins, this->nbins, CV_32F);

    for (int row = patch.y; row < patch.height; row++) {
      for (int col = patch.x; col < patch.width; col++) {

        /* Calcula as matrizes */
        x = img(row, col);
        if (x == -1)
          continue;

        if (row + d < patch.height && col - d >= patch.x) {
          y = img(row + d, col - d);
          if (y == -1)
            continue;
          // y = direct->GetElement(col - d, row + d);

          M45(y, x)++;
          M45(x, y)++;
          R45++;

        }

      }
    }

    if (R45 == 0.0f)
      R45 = 1.0f;

    M45 = M45 / R45;

    output = M45.clone();
  }

  void CoOccurrenceGeneral::extractMatrix90(const cv::Rect& patch, cv::Mat_<int> &img, cv::Mat& output) {
    float R90 = 0.0f;
    int d, x, y;

    /* Inicializacoes */
    d = this->distance;

    /*Initializes the matrices*/
    M90 = cv::Mat::zeros(this->nbins, this->nbins, CV_32F);

    for (int row = patch.y; row < patch.height; row++) {
      for (int col = patch.x; col < patch.width; col++) {

        /* Calcula as matrizes */
        x = img(row, col);
        if (x == -1)
          continue;

        if (row + d < patch.height) {
          y = img(row + d, col);
          if (y == -1)
            continue;

          M90(y, x)++;
          M90(x, y)++;
          R90++;

        }

      }
    }

    if (R90 == 0.0f)
      R90 = 1.0f;

    M90 = M90 / R90;

    output = M90.clone();
  }

  void CoOccurrenceGeneral::extractMatrix135(const cv::Rect& patch, cv::Mat_<int> &img, cv::Mat& output) {
    float R135 = 0.0f;
    int d, x, y;

    /* Inicializacoes */
    d = this->distance;

    /*Initializes the matrices*/
    M135 = cv::Mat::zeros(this->nbins, this->nbins, CV_32F);

    for (int row = patch.y; row < patch.height; row++) {
      for (int col = patch.x; col < patch.width; col++) {

        /* Calcula as matrizes */
        x = img(row, col);
        if (x == -1)
          continue;

        if (row + d < patch.height && col + d < patch.width) {
          // y = direct->GetElement(col + d, row + d);
          y = img(row + d, col + d);
          if (y == -1)
            continue;

          M135(y, x)++;
          M135(x, y)++;
          R135++;

        }

      }
    }

    if (R135 == 0.0f)
      R135 = 1.0f;

    M135 = M135 / R135;

    output = M135.clone();
  }

  void CoOccurrenceGeneral::extractAllMatricesDirections(const cv::Rect& patch, cv::Mat_<int> &img, std::vector<cv::Mat>& output) {
    cv::Mat dummy;  // testar se vai precisar declarar o tamanho

    extractMatrix0(patch, img, dummy);
    extractMatrix45(patch, img, dummy);
    extractMatrix90(patch, img, dummy);
    extractMatrix135(patch, img, dummy);

    output.push_back(M0);
    output.push_back(M45);
    output.push_back(M90);
    output.push_back(M135);
  }

}  // namespace ssig
