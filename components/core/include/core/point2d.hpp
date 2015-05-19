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

#endif // !_SSF_CORE_POINT2D_HPP_