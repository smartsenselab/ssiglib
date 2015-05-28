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

#ifndef _SSF_CORE_CUBE_HPP_
#define _SSF_CORE_CUBE_HPP_

#include <type_traits>

#include "core/core_defs.hpp"
#include "core/exception.hpp"
#include "core/point3d.hpp"

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Cube{

	public:
		Cube(T x = 0, T y = 0, T z = 0, T width = 0, T height = 0, T length = 0)
			: mPosition(Point3D<T>(x, y, z)),
			mWidth(width), mHeight(height), mLength(length){
		}

		virtual ~Cube(void){
		}

		Cube(const Cube& rhs){
			this->mPosition = rhs.mPosition;
			this->mWidth = rhs.mWidth;
			this->mHeight = rhs.mHeight;
			this->mLength = rhs.mLength;
		}

		Cube& operator=(const Cube& rhs){
			if (this != &rhs){
				this->mPosition = rhs.mPosition;
				this->mWidth = rhs.mWidth;
				this->mHeight = rhs.mHeight;
				this->mLength = rhs.mLength;
			}
			return *this;
		}

		Point3D<T> getPosition() const { return this->mPosition; }
		void setPosition(const Point3D<T>& position) { this->mPosition = position; }

		inline T getPositionX() const { return this->mPosition.getX(); }
		inline void setPositionX(const T& x) { this->mPosition.setX(x); }
		inline T getPositionY() const { return this->mPosition.getY(); }
		void setPositionY(const T& y) { this->mPosition.setY(y); }
		inline T getPositionZ() const { return this->mPosition.getZ(); }
		void setPositionZ(const T& z) { this->mPosition.setZ(z); }

		T getLength() const { return this->mLength; }
		void seLength(const T& length) {
			if (length < 0)
				throw Exception("The length value must be positive.");
			this->mLength = length;
		}

		T getHeight() const { return this->mHeight; }
		void setHeight(const T& height) {
			if (height < 0)
				throw Exception("The height value must be positive.");
			this->mHeight = height;
		}

		T getWidth() const { return this->mWidth; }
		void setWidth(const T& width) {
			if (width < 0)
				throw Exception("The width value must be positive.");
			this->mWidth = width;
		}

		bool isValid() const { return (this->mHeight != 0 && this->mWidth != 0 && this->mLength != 0); }
		void reset() { this->mHeight = 0; this->mWidth = 0; this->mLength = 0; }

	private:
		Point3D<T> mPosition;
		T mWidth, mHeight, mLength;

	};

}

#endif // !_SSF_CORE_CUBE_HPP_PP_