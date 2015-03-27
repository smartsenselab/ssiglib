#include "core/class_test.hpp"

namespace ssf{

	ClassTest::ClassTest(){
		//Constructor
	}

	ClassTest::~ClassTest(){
		//Destructor
	}

	ClassTest::ClassTest(const ClassTest& rhs){
		//Constructor Copy
	}

	ClassTest& ClassTest::operator=(const ClassTest& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

}

