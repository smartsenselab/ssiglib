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

#include "core/image.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace ssf{

	Image::Image(){
		this->mData = std::make_shared<cv::Mat>();
	}

	Image::Image(std::string filename, ImgLoadType loadImgType /*= ImgLoadType::UNCHANGED*/){
		this->mData = std::make_shared<cv::Mat>();
		if (loadImgType == ImgLoadType::UNCHANGED)
			*(this->mData) = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
		else if (loadImgType == ImgLoadType::COLOR)
			*(this->mData) = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
		else
			*(this->mData) = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	}

	Image::Image(cv::Mat data){
		*(this->mData) = data.clone();
	}

	Image::~Image(){
		//Destructor
	}

	Image::Image(const Image& rhs){
		*(this->mData) = *(rhs.mData);
	}

	Image& Image::operator=(const Image& rhs){
		if (this != &rhs){
			*(this->mData) = *(rhs.mData);
		}
		return *this;
	}

	cv::Mat Image::data(){
		return *(this->mData);
	}

	Image Image::clone(){
		Image retImage;
		*(retImage.mData) = this->mData->clone();
		return retImage;
	}

	size_t Image::cols() const{
		return this->mData->cols;
	}

	size_t Image::rows() const{
		return this->mData->rows;
	}
}

