#ifndef _SSF_CORE_CUBE_HPP_
#define _SSF_CORE_CUBE_HPP_

#include <type_traits>

#include "core/ssfdef.hpp"
#include "core/exception.hpp"
#include "core/point3d.hpp"

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class SSF_EXPORT Cube{

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

#endif // !_SSF_CORE_CUBE_HPP_