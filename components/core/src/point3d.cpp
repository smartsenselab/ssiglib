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

#include "core/point3d.hpp"

#include <opencv/cv.h>

namespace ssf{

	Point3Di::Point3Di()
		: Point3D<int>(){
	}

	Point3Di::Point3Di(const cv::Point3i& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3i Point3Di::toOpenCVPoint() const{
		return cv::Point3i(this->mX, this->mY, this->mZ);
	}

	void Point3Di::set(const int& x, const int& y, const int& z){
		Point3D<int>::set(x, y, z);
	}

	void Point3Di::set(const cv::Point3i& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	//////////////////////////

	Point3Df::Point3Df()
		: Point3D<float>(){
	}

	Point3Df::Point3Df(const cv::Point3f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3f Point3Df::toOpenCVPoint() const{
		return cv::Point3f(this->mX, this->mY, this->mZ);
	}

	void Point3Df::set(const float& x, const float& y, const float& z){
		Point3D<float>::set(x, y, z);
	}

	void Point3Df::set(const cv::Point3f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	///////////////////////////

	Point3Dd::Point3Dd()
		: Point3D<double>(){
	}

	Point3Dd::Point3Dd(const cv::Point3d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3d Point3Dd::toOpenCVPoint() const{
		return cv::Point3d(this->mX, this->mY, this->mZ);
	}

	void Point3Dd::set(const double& x, const double& y, const double& z){
		Point3D<double>::set(x, y, z);
	}

	void Point3Dd::set(const cv::Point3d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

}



