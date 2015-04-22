#include "param_temp/param_temp.hpp"

namespace ssf{

    template <class T>
	ParamTemp<T>::ParamTemp(const T& value){
        this->value = value;
	}
    
    template <class T>
	ParamTemp<T>::~ParamTemp(){
	}

    template <class T>
	ParamTemp<T>::ParamTemp(const ParamTemp& rhs){
		//Constructor Copy
	}

    template <class T>
	T& ParamTemp<T>::operator=(const ParamTemp& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}
    
    template<class T>
    T ParamTemp<T>::getValue(){
        return this->value;
    }

}