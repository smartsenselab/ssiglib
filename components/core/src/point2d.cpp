#include "core/point2d.hpp"

#include <opencv/cv.h>

namespace ssf{

	Point2Di::Point2Di()
		: Point2D<int>(){
	}

	Point2Di::Point2Di(const cv::Point& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}

	cv::Point Point2Di::toOpenCVPoint() const{
		return cv::Point(this->mX, this->mY);
	}

	void Point2Di::set(const int& x, const int& y){
		Point2D<int>::set(x, y);
	}

	void Point2Di::set(const cv::Point& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}

	//////////////////////////

	Point2Df::Point2Df()
		: Point2D<float>(){
	}

	Point2Df::Point2Df(const cv::Point2f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}

	cv::Point2f Point2Df::toOpenCVPoint() const{
		return cv::Point2f(this->mX, this->mY);
	}

	void Point2Df::set(const float& x, const float& y){
		Point2D<float>::set(x, y);
	}

	void Point2Df::set(const cv::Point2f& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}

	///////////////////////////

	Point2Dd::Point2Dd()
		: Point2D<double>(){
	}

	Point2Dd::Point2Dd(const cv::Point2d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}

	cv::Point2d Point2Dd::toOpenCVPoint() const{
		return cv::Point2d(this->mX, this->mY);
	}

	void Point2Dd::set(const double& x, const double& y){
		Point2D<double>::set(x, y);
	}

	void Point2Dd::set(const cv::Point2d& cvPoint){
		this->mX = cvPoint.x;
		this->mY = cvPoint.y;
	}


}

