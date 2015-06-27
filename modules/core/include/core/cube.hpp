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

#ifndef _SSF_CORE_CUBE_HPP_
#define _SSF_CORE_CUBE_HPP_

#include <type_traits>

#include "core/core_defs.hpp"
#include "core/exception.hpp"
#include "core/point3d.hpp"

namespace ssf{

	/**
	 * @brief	Template class for 3D cubes.
	 *
	 * @tparam	T	Generic type for 3D cube.
	 */
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Cube{

	public:

		/**
		 * @brief	Initializes a new instance of the Cube class.
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	z	  	The z coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 * @param	length	The length.
		 */
		Cube(T x = 0, T y = 0, T z = 0, T width = 0, T height = 0, T length = 0)
			: mPosition(Point3D<T>(x, y, z)),
			mWidth(width), mHeight(height), mLength(length){
		}

		/**
		 * @brief	Finalizes an instance of the Cube class.
		 */
		virtual ~Cube(void){
		}

		/**
		 * @brief	Initializes a new instance of the Cube class.
		 *
		 * @param	rhs	The right hand side.
		 */
		Cube(const Cube& rhs){
			this->mPosition = rhs.mPosition;
			this->mWidth = rhs.mWidth;
			this->mHeight = rhs.mHeight;
			this->mLength = rhs.mLength;
		}

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		Cube& operator=(const Cube& rhs){
			if (this != &rhs){
				this->mPosition = rhs.mPosition;
				this->mWidth = rhs.mWidth;
				this->mHeight = rhs.mHeight;
				this->mLength = rhs.mLength;
			}
			return *this;
		}

		/**
		 * @brief	Gets the cube 3D position.
		 *
		 * @return	A Point3D&lt;T&gt;;
		 */
		Point3D<T> position() const { return this->mPosition; }

		/**
		 * @brief	Sets a position.
		 *
		 * @param	position	The 3D position.
		 */
		void setPosition(const Point3D<T>& position) { this->mPosition = position; }

		/**
		 * @brief	Gets the x coordinate.
		 *
		 * @return	The x coordinate.
		 */
		inline T x() const { return this->mPosition.x(); }

		/**
		 * @brief	Sets an x coordinate.
		 *
		 * @param	x	The x coordinate.
		 */
		inline void setX(const T& x) { this->mPosition.setX(x); }

		/**
		 * @brief	Gets the y coordinate.
		 *
		 * @return	The y coordinate.
		 */
		inline T y() const { return this->mPosition.y(); }

		/**
		 * @brief	Sets a y coordinate.
		 *
		 * @param	y	The y coordinate.
		 */
		void setY(const T& y) { this->mPosition.setY(y); }

		/**
		 * @brief	Gets the z coordinate.
		 *
		 * @return	The z coordinate.
		 */
		inline T z() const { return this->mPosition.z(); }

		/**
		 * @brief	Sets a z coordinate.
		 *
		 * @param	z	The z coordinate.
		 */
		void setZ(const T& z) { this->mPosition.setZ(z); }

		/**
		 * @brief	Gets the length.
		 *
		 * @return	The length.
		 */
		T length() const { return this->mLength; }

		/**
		 * @brief	Se length.
		 *
		 * @exception	Exception	If length is less than zero.
		 *
		 * @param	length	The length.
		 */
		void seLength(const T& length) {
			if (length < 0)
				throw Exception("The length value must be positive.");
			this->mLength = length;
		}

		/**
		 * @brief	Gets the height.
		 *
		 * @return	The height.
		 */
		T height() const { return this->mHeight; }

		/**
		 * @brief	Sets a height.
		 *
		 * @exception	Exception	If length is less than zero.
		 *
		 * @param	height	The height.
		 */
		void setHeight(const T& height) {
			if (height < 0)
				throw Exception("The height value must be positive.");
			this->mHeight = height;
		}

		/**
		 * @brief	Gets the width.
		 *
		 * @return	The width.
		 */
		T width() const { return this->mWidth; }

		/**
		 * @brief	Sets a width.
		 *
		 * @exception	Exception	If width is less than zero.
		 *
		 * @param	width	The width.
		 */
		void setWidth(const T& width) {
			if (width < 0)
				throw Exception("The width value must be positive.");
			this->mWidth = width;
		}

		/**
		 * @brief	Query if this Cube is valid.
		 * 			
		 * @detail	A Cube is valid if height, width and length is greater than zero.
		 *
		 * @return	true if valid, false if not.
		 */
		bool isValid() const { return (this->mHeight != 0 && this->mWidth != 0 && this->mLength != 0); }

		/**
		 * @brief	Resets this object (Invalidate it).
		 */
		void reset() { this->mHeight = 0; this->mWidth = 0; this->mLength = 0; }

	private:
		Point3D<T> mPosition;   ///< The cube position
		T mWidth;   ///< The width
		T mHeight;  ///< The height
		T mLength;  ///< The length

	};

}

#endif // !_SSF_CORE_CUBE_HPP_PP_