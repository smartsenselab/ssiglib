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

	/**
	 * @brief	Template class for 2D points specified by its coordinates `x` and `y`.
	 *
	 * @tparam	T	Generic type for 2D point.
	 */
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Point2D{

	public:

		/**
		 * @brief	Initializes a new instance of the Point2D class.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		Point2D(T x = 0, T y = 0)
			: mX(x), mY(y){
		}

		/**
		 * @brief	Finalizes an instance of the Point2D class.
		 */
		virtual ~Point2D(void){
		}

		/**
		 * @brief	Initializes a new instance of the Point2D class.
		 *
		 * @param	rhs	The right hand side.
		 */
		Point2D(const Point2D& rhs){
			this->mX = rhs.mX;
			this->mY = rhs.mY;
		}

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		Point2D& operator=(const Point2D& rhs){
			if (this != &rhs){
				this->mX = rhs.mX;
				this->mY = rhs.mY;
			}
			return *this;
		}

		/**
		 * @brief	Equality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are considered equivalent.
		 */
		bool operator==(const Point2D<T>& rhs) {
			return this->x() == rhs.x() && this->y() == rhs.y();
		}

		/**
		 * @brief	Inequality operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	true if the parameters are not considered equivalent.
		 */
		bool operator!=(const Point2D<T>& rhs) {
			return !(*(this) == rhs);
		}

		/**
		 * @brief	Gets the x coordinate.
		 *
		 * @return	The x value as T.
		 */
		inline T x() const { return this->mX; }

		/**
		 * @brief	Sets an x coordinate.
		 *
		 * @param	x	The x value as T.
		 */
		inline void setX(const T& x) { this->mX = x; }

		/**
		 * @brief	Gets the y coordinate.
		 *
		 * @return	The y value as T.
		 */
		inline T y() const { return this->mY; }

		/**
		 * @brief	Sets a y coordinate.
		 *
		 * @param	y	The y value as T.
		 */
		void setY(const T& y) { this->mY = y; }

		/**
		 * @brief	Sets x and y coordinates.
		 *
		 * @param	x	The x value as T.
		 * @param	y	The y value as T.
		 */
		virtual void set(const T& x, const T& y) { this->mX = x; this->mY = y; }

	protected:
		T mX;   ///< The x coordinate
		T mY;   ///< The y coordinate

	};

	/**
	 * @brief	A int specialization of generic Point2D.
	 *
	 * @sa	Point2D
	 */
	class CORE_EXPORT Point2Di : public Point2D < int > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point2Di class.
		 */
		Point2Di(void);

		/**
		 * @brief	Initializes a new instance of the Point2Di class with a OpenCV point.
		 *
		 * @param	cv::Point	A OpenCV point.
		 */
		explicit Point2Di(const cv::Point& cvPoint);

		/**
		 * @brief	Converts this object to an OpenCV point.
		 *
		 * @return	This Point2Di as a cv::Point.
		 */
		cv::Point toOpenCVPoint() const;

		/**
		 * @brief	Sets x and y coordinates.
		 *
		 * @param	x	The x value as int.
		 * @param	y	The y value as int.
		 */
		virtual void set(const int& x, const int& y) override;

		/**
		 * @brief	Sets x and y coordinates by OpenCV point.
		 *
		 * @param	cvPoint	The OpenCV point to set.
		 */
		void set(const cv::Point& cvPoint);
	};

	/**
	 * @brief	A float specialization of generic Point2D.
	 *
	 * @sa	Point2D
	 */
	class CORE_EXPORT Point2Df : public Point2D < float > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point2Df class.
		 */
		Point2Df(void);

		/**
		 * @brief	Initializes a new instance of the Point2DF class with a OpenCV point.
		 *
		 * @param	cv::Point2f	A OpenCV point.
		 */
		explicit Point2Df(const cv::Point2f& cvPoint);

		/**
		 * @brief	Converts this object to an OpenCV point.
		 *
		 * @return	This Point2Df as a cv::Point.
		 */
		cv::Point2f toOpenCVPoint() const;

		/**
		 * @brief	Sets x and y coordinates.
		 *
		 * @param	x	The x value as float.
		 * @param	y	The y value as float.
		 */
		virtual void set(const float& x, const float& y) override;

		/**
		 * @brief	Sets x and y coordinates by OpenCV point.
		 *
		 * @param	cvPoint	The OpenCV point to set.
		 */
		void set(const cv::Point2f& cvPoint);
	}; 

	/**
	 * @brief	A double specialization of generic Point2D.
	 *
	 * @sa	Point2D
	 */
	class CORE_EXPORT Point2Dd : public Point2D < double > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point2Dd class.
		 */
		Point2Dd(void);

		/**
		 * @brief	Initializes a new instance of the Point2Dd class with a OpenCV point.
		 *
		 * @param	cv::Point2d	A OpenCV point.
		 */
		explicit Point2Dd(const cv::Point2d& cvPoint);

		/**
		 * @brief	Converts this object to an OpenCV point.
		 *
		 * @return	This object as a cv::Point2d.
		 */
		cv::Point2d toOpenCVPoint() const;

		/**
		 * @brief	Sets x and y coordinates.
		 *
		 * @param	x	The x coordinate as double.
		 * @param	y	The y coordinate as double.
		 */
		virtual void set(const double& x, const double& y) override;

		/**
		 * @brief	Sets x and y coordinates by OpenCV point.
		 *
		 * @param	cvPoint	The OpenCV point to set.
		 */
		void set(const cv::Point2d& cvPoint);
	};


}

#endif // !_SSF_CORE_POINT2D_HPP_PP_