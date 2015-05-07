#ifndef _SSF_CORE_POINT3D_HPP_
#define _SSF_CORE_POINT3D_HPP_

#include <type_traits>
#include "core/ssfdef.hpp"

namespace cv{
	template<typename _Tp> class Point3_;
	typedef Point3_<int> Point3i;
	typedef Point3_<float> Point3f;
	typedef Point3_<double> Point3d;
}

namespace ssf{

	template<typename T>//, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class SSF_EXPORT Point3D{

	public:

		Point3D(T x = 0, T y = 0, T z = 0)
			: mX(x), mY(y), mZ(z){
		}

		virtual ~Point3D(void){
		}

		Point3D(const Point3D& rhs){
			this->mX = rhs.mX;
			this->mY = rhs.mY;
			this->mZ = rhs.mZ;
		}

		Point3D& operator=(const Point3D& rhs){
			if (this != &rhs){
				this->mX = rhs.mX;
				this->mY = rhs.mY;
				this->mZ = rhs.mZ;
			}
			return *this;
		}

		inline T getX() const { return this->mX; }
		inline void setX(const T& x) { this->mX = x; }
		inline T getY() const { return this->mY; }
		void setY(const T& y) { this->mY = y; }
		inline T getZ() const { return this->mZ; }
		void setZ(const T& z) { this->mZ = z; }

		void set(const T& x, const T& y, const T& z){ this->mX = x; this->mY = y; this->mZ = z; }

	protected:
		T mX, mY, mZ;

	};

	class SSF_EXPORT Point3Di : public Point3D < int > {
	public:
		Point3Di(void);
		Point3Di(const cv::Point3i& cvPoint);
		cv::Point3i toOpenCVPoint() const;
		void set(const int& x, const int& y, const int& z);
		void set(const cv::Point3i& cvPoint);
	};

	class SSF_EXPORT Point3Df : public Point3D < float > {
	public:
		Point3Df(void);
		Point3Df(const cv::Point3f& cvPoint);
		cv::Point3f toOpenCVPoint() const;
		void set(const float& x, const float& y, const float& z);
		void set(const cv::Point3f& cvPoint);
	};

	class SSF_EXPORT Point3Dd : public Point3D < double > {
	public:
		Point3Dd(void);
		Point3Dd(const cv::Point3d& cvPoint);
		cv::Point3d toOpenCVPoint() const;
		void set(const double& x, const double& y, const double& z);
		void set(const cv::Point3d& cvPoint);
	};

}

#endif // !_SSF_CORE_POINT3D_HPP_