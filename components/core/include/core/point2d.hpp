/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                   Software License Agreement (BSD License)
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
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
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#ifndef _SSF_CORE_POINT2D_HPP_
#define _SSF_CORE_POINT2D_HPP_

#include <type_traits>
#include "core/core_defs.hpp"

namespace cv{
	template<typename _Tp> class Point_;
	typedef Point_<int> Point2i;
	typedef Point_<float> Point2f;
	typedef Point_<double> Point2d;
	typedef Point2i Point;
}

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Point2D{

	public:

		Point2D(T x = 0, T y = 0)
			: mX(x), mY(y){
		}

		virtual ~Point2D(void){
		}

		Point2D(const Point2D& rhs){
			this->mX = rhs.mX;
			this->mY = rhs.mY;
		}

		Point2D& operator=(const Point2D& rhs){
			if (this != &rhs){
				this->mX = rhs.mX;
				this->mY = rhs.mY;
			}
			return *this;
		}

		bool operator==(const Point2D<T>& rhs) {
			return this->getX() == rhs.getX() && this->getY() == rhs.getY();
		}

		bool operator!=(const Point2D<T>& rhs) {
			return !(*(this) == rhs);
		}

		inline T getX() const { return this->mX; }
		inline void setX(const T& x) { this->mX = x; }
		inline T getY() const { return this->mY; }
		void setY(const T& y) { this->mY = y; }

		virtual void set(const T& x, const T& y) { this->mX = x; this->mY = y; }

	protected:
		T mX, mY;

	};

	class CORE_EXPORT Point2Di : public Point2D < int > {
	public:
		Point2Di(void);
		Point2Di(const cv::Point& cvPoint);
		cv::Point toOpenCVPoint() const;
		void set(const int& x, const int& y);
		void set(const cv::Point& cvPoint);
	};

	class CORE_EXPORT Point2Df : public Point2D < float > {
	public:
		Point2Df(void);
		Point2Df(const cv::Point2f& cvPoint);
		cv::Point2f toOpenCVPoint() const;
		void set(const float& x, const float& y);
		void set(const cv::Point2f& cvPoint);
	};

	class CORE_EXPORT Point2Dd : public Point2D < double > {
	public:
		Point2Dd(void);
		Point2Dd(const cv::Point2d& cvPoint);
		cv::Point2d toOpenCVPoint() const;
		void set(const double& x, const double& y);
		void set(const cv::Point2d& cvPoint);
	};


}

#endif // !_SSF_CORE_POINT2D_HPP_PP_