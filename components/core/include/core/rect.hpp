#ifndef _SSF_CORE_RECT_HPP_
#define _SSF_CORE_RECT_HPP_

#include <type_traits>

#include "core/base.hpp"
#include "core/exception.hpp"
#include "core/point2d.hpp"

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class SSF_EXPORT Rect{

	public:
		Rect(T x = 0, T y = 0, T width = 0, T height = 0)
			: mPosition(Point2D<T>(x, y)),
			mWidth(width), mHeight(height){
		}

		virtual ~Rect(void){
		}

		Rect(const Rect& rhs){
			this->mPosition = rhs.mPosition;
			this->mWidth = rhs.mWidth;
			this->mHeight = rhs.mHeight;
		}

		Rect& operator=(const Rect& rhs){
			if (this != &rhs){
				this->mPosition = rhs.mPosition;
				this->mWidth = rhs.mWidth;
				this->mHeight = rhs.mHeight;
			}
			return *this;
		}

		Point2D<T> getPosition() const { return this->mPosition; }
		void setPosition(const Point2D<T>& position) { this->mPosition = position; }

		inline T getPositionX() const { return this->mPosition.getX(); }
		inline void setPositionX(const T& x) { this->mPosition.setX(x); }
		inline T getPositionY() const { return this->mPosition.getY(); }
		void setPositionY(const T& y) { this->mPosition.setY(y); }


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

		bool isValid() const { return (this->mHeight != 0 && this->mWidth != 0); }
		void reset() { this->mHeight = 0; this->mWidth = 0; }

	private:
		Point2D<T> mPosition;
		T mWidth, mHeight;

	};

}

#endif // !_SSF_CORE_RECT_HPP_