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

#ifndef _SSF_CORE_POINT3D_HPP_
#define _SSF_CORE_POINT3D_HPP_

#include <type_traits>
#include "core/core_defs.hpp"

namespace cv{
	template<typename _Tp> class Point3_;
	typedef Point3_<int> Point3i;
	typedef Point3_<float> Point3f;
	typedef Point3_<double> Point3d;
}

namespace ssf{

	/**
	 * @brief	Template class for 3D points specified by its coordinates `x`, 'y' and `z`.
	 *
	 * @tparam	T	Generic type for 2D point.
	 */
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Point3D{

	public:

		/**
		 * @brief	Initializes a new instance of the Point3D class.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 */
		Point3D(T x = 0, T y = 0, T z = 0)
			: mX(x), mY(y), mZ(z){
		}

		/**
		 * @brief	Finalizes an instance of the Point3D class.
		 */
		virtual ~Point3D(void){
		}

		/**
		 * @brief	Initializes a new instance of the Point3D class.
		 *
		 * @param	rhs	The right hand side.
		 */
		Point3D(const Point3D& rhs){
			this->mX = rhs.mX;
			this->mY = rhs.mY;
			this->mZ = rhs.mZ;
		}

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		Point3D& operator=(const Point3D& rhs){
			if (this != &rhs){
				this->mX = rhs.mX;
				this->mY = rhs.mY;
				this->mZ = rhs.mZ;
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
		bool operator==(const Point3D<T>& rhs) {
			return this->x() == rhs.x() && this->y() == rhs.y() && this->z() == rhs.z();
		}

		/**
		* @brief	Inequality operator.
		*
		* @param	rhs	The right hand side.
		*
		* @return	true if the parameters are not considered equivalent.
		*/
		bool operator!=(const Point3D<T>& rhs) {
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
		* @brief	Gets the z coordinate.
		*
		* @return	The z value as T.
		*/
		inline T z() const { return this->mZ; }

		/**
		* @brief	Sets a z coordinate.
		*
		* @param	z	The z value as T.
		*/
		void setZ(const T& z) { this->mZ = z; }

		/**
		 * @brief	Sets x, y and z coordinates
		 *
		 * @param	x	The x value as T.
		 * @param	y	The y value as T.
		 * @param	z	The z value as T.
		 */
		void set(const T& x, const T& y, const T& z){ this->mX = x; this->mY = y; this->mZ = z; }

	protected:

		/**
		 * @brief	Gets the m z coordinate.
		 *
		 * @return	The m z coordinate.
		 */
		T mX, mY, mZ;

	};

	/**
	* @brief	A int specialization of generic Point3D.
	*
	* @sa	Point3D
	*/
	class CORE_EXPORT Point3Di : public Point3D < int > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point3Di class.
		 */
		Point3Di(void);

		/**
		 * @brief	Initializes a new instance of the Point3Di class with a OpenCV point.
		 *
		 * @param	cvPoint	A OpenCV point.
		 */
		explicit Point3Di(const cv::Point3i& cvPoint);

		/**
		 * @brief	Converts this object to an OpenCV point.
		 *
		 * @return	This Point3Di as a cv::Point3i.
		 */
		cv::Point3i toOpenCVPoint() const;

		/**
		 * @brief	Sets x, y and z coordinates
		 *
		 * @param	x	The x value as int.
		 * @param	y	The y value as int.
		 * @param	z	The z value as int.
		 */
		void set(const int& x, const int& y, const int& z);

		/**
		 * @brief	Sets x and y coordinates by OpenCV point.
		 *
		 * @param	cvPoint	The OpenCV point to set.
		 */
		void set(const cv::Point3i& cvPoint);
	};

	/**
	* @brief	A float specialization of generic Point3D.
	*
	* @sa	Point3D
	*/
	class CORE_EXPORT Point3Df : public Point3D < float > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point3Df class.
		 */
		Point3Df(void);

		/**
		* @brief	Initializes a new instance of the Point3Df class with a OpenCV point.
		*
		* @param	cv::Point3f	A OpenCV point.
		*/
		Point3Df(const cv::Point3f& cvPoint);

		/**
		* @brief	Converts this object to an OpenCV point.
		*
		* @return	This Point3Df as a cv::Point3f.
		*/
		cv::Point3f toOpenCVPoint() const;

		/**
		* @brief	Sets x, y and z coordinates
		*
		* @param	x	The x value as float.
		* @param	y	The y value as float.
		* @param	z	The z value as float.
		*/
		void set(const float& x, const float& y, const float& z);

		/**
		 * @brief	Sets the given cv point.
		 *
		 * @param	cvPoint	The cv point to set.
		 */
		void set(const cv::Point3f& cvPoint);
	};

	/**
	* @brief	A double specialization of generic Point3D.
	*
	* @sa	Point3D
	*/
	class CORE_EXPORT Point3Dd : public Point3D < double > {
	public:

		/**
		 * @brief	Initializes a new instance of the Point3Dd class.
		 */
		Point3Dd(void);

		/**
		* @brief	Initializes a new instance of the Point3Dd class with a OpenCV point.
		*
		* @param	cv::Point3d	A OpenCV point.
		*/
		Point3Dd(const cv::Point3d& cvPoint);

		/**
		* @brief	Converts this object to an OpenCV point.
		*
		* @return	This Point3Dd as a cv::Point3d.
		*/
		cv::Point3d toOpenCVPoint() const;

		/**
		* @brief	Sets x, y and z coordinates
		*
		* @param	x	The x value as double.
		* @param	y	The y value as double.
		* @param	z	The z value as double.
		*/
		void set(const double& x, const double& y, const double& z);

		/**
		* @brief	Sets the given cv point.
		*
		* @param	cvPoint	The cv point to set.
		*/
		void set(const cv::Point3d& cvPoint);
	};

}

#endif // !_SSF_CORE_POINT3D_HPP_PP_