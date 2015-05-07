#include "core/scale_info.hpp"

namespace ssf{

	ScaleInfo::ScaleInfo(){
		//Constructor
	}

	ScaleInfo::~ScaleInfo(){
		//Destructor
	}

	ScaleInfo::ScaleInfo(const ScaleInfo& rhs){
		//Constructor Copy
	}

	ScaleInfo& ScaleInfo::operator=(const ScaleInfo& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

	int ScaleInfo::getStrideY() const{
		return this->strideY;
	}

	void ScaleInfo::setStrideY(const int& strideY){
		this->strideY = strideY;
	}

	int ScaleInfo::getStrideX() const{
		return this->strideX;
	}

	void ScaleInfo::setStrideX(const int& stideX){
		this->strideX = stideX;
	}

	int ScaleInfo::getInterpolationMethod() const{
		return this->interpolationMethod;
	}

	void ScaleInfo::setInterpolationMethod(const int& interpolationMethod){
		this->interpolationMethod = interpolationMethod;
	}

	Rect<int> ScaleInfo::getObjectSize() const{
		return this->objectSize;
	}

	void ScaleInfo::setObjectSize(const Rect<int>& objectSize){
		this->objectSize = objectSize;
	}

	Rect<int> ScaleInfo::getDetWindowSize() const{
		return this->detWindowSize;
	}

	void ScaleInfo::setDetWindowSize(const Rect<int>& detWindowSize){
		this->detWindowSize = detWindowSize;
	}

}

