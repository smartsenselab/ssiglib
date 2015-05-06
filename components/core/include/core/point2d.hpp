#ifndef _SSF_CORE_POINT2D_HPP_
#define _SSF_CORE_POINT2D_HPP_

#include "core/ssfdef.hpp"

namespace ssf{

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class SSF_EXPORT Point2D{

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

		inline T getX() const { return this->mX; }
		inline void setX(const T& x) { this->mX = x; }
		inline T getY() const { return this->mY; }
		void setY(const T& y) { this->mY = y; }

	private:
		T mX, mY;

	};

	typedef Point2D<int> Point2Di;
	typedef Point2D<float> Point2Df;
	typedef Point2D<double> Point2Dd;

}

#endif // !_SSF_CORE_POINT2D_HPP_