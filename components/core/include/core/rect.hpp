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

#ifndef _SSF_CORE_RECT_HPP_
#define _SSF_CORE_RECT_HPP_

#include <type_traits>

#include "core/core_defs.hpp"
#include "core/exception.hpp"
#include "core/point2d.hpp"

namespace ssf{

	/**
	 * @brief	Template class for 2D rectangles.
	 *
	 * @tparam	T	Generic type for 2D rectangles.
	 */
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class CORE_EXPORT Rect{

	public:

		/**
		 * @brief	Initializes a new instance of the Rect class.
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		Rect(T x = 0, T y = 0, T width = 0, T height = 0)
			: mPosition(Point2D<T>(x, y)),
			mWidth(width), mHeight(height){
		}

		/**
		 * @brief	Finalizes an instance of the Rect class.
		 */
		virtual ~Rect(void){
		}

		/**
		 * @brief	Initializes a new instance of the Rect class.
		 *
		 * @param	rhs	The right hand side.
		 */
		Rect(const Rect& rhs){
			this->mPosition = rhs.mPosition;
			this->mWidth = rhs.mWidth;
			this->mHeight = rhs.mHeight;
		}

		/**
		 * @brief	Assignment operator.
		 *
		 * @param	rhs	The right hand side.
		 *
		 * @return	A shallow copy of this object.
		 */
		Rect& operator=(const Rect& rhs){
			if (this != &rhs){
				this->mPosition = rhs.mPosition;
				this->mWidth = rhs.mWidth;
				this->mHeight = rhs.mHeight;
			}
			return *this;
		}

		/**
		 * @brief	Gets the position.
		 *
		 * @return	A Point2D&lt;T&gt;;
		 */
		Point2D<T> getPosition() const { return this->mPosition; }

		/**
		 * @brief	Sets a position.
		 *
		 * @param	position	The 2D position.
		 */
		void setPosition(const Point2D<T>& position) { this->mPosition = position; }

		/**
		 * @brief	Gets position x coordinate.
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
		 * @brief	Gets position y coordinate.
		 *
		 * @return	The position y coordinate.
		 */
		inline T y() const { return this->mPosition.y(); }

		/**
		 * @brief	Sets position y coordinate.
		 *
		 * @param	y	The y coordinate.
		 */
		void setY(const T& y) { this->mPosition.setY(y); }

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
		 * @brief	Query if this Rect is valid.
		 * 			
		 * @detail	A Rect is valid if height and width is greater than zero.
		 *
		 * @return	true if valid, false if not.
		 */
		bool isValid() const { return (this->mHeight != 0 && this->mWidth != 0); }

		/**
		* @brief	Resets this object (Invalidate it).
		*/
		void reset() { this->mHeight = 0; this->mWidth = 0; }

	private:
		Point2D<T> mPosition;   ///< The position
		T mWidth;   ///< The width
		T mHeight;  ///< The height

	};

}

#endif // !_SSF_CORE_RECT_HPP_PP_