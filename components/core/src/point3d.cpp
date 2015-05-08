#include "core/point3d.hpp"

#include <opencv/cv.h>

namespace ssf{

	Point3Di::Point3Di()
		: Point3D<int>(){
	}

	Point3Di::Point3Di(const cv::Point3i& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3i Point3Di::toOpenCVPoint() const{
		return cv::Point3i(this->mX, this->mY, this->mZ);
	}

	void Point3Di::set(const int& x, const int& y, const int& z){
		Point3D<int>::set(x, y, z);
	}

	void Point3Di::set(const cv::Point3i& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	//////////////////////////

	Point3Df::Point3Df()
		: Point3D<float>(){
	}

	Point3Df::Point3Df(const cv::Point3f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3f Point3Df::toOpenCVPoint() const{
		return cv::Point3f(this->mX, this->mY, this->mZ);
	}

	void Point3Df::set(const float& x, const float& y, const float& z){
		Point3D<float>::set(x, y, z);
	}

	void Point3Df::set(const cv::Point3f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	///////////////////////////

	Point3Dd::Point3Dd()
		: Point3D<double>(){
	}

	Point3Dd::Point3Dd(const cv::Point3d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

	cv::Point3d Point3Dd::toOpenCVPoint() const{
		return cv::Point3d(this->mX, this->mY, this->mZ);
	}

	void Point3Dd::set(const double& x, const double& y, const double& z){
		Point3D<double>::set(x, y, z);
	}

	void Point3Dd::set(const cv::Point3d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
		this->mZ = cvPoint.z;
	}

}

