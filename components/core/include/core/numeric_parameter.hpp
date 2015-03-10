#ifndef _SSF_CORE_INT_PARAMETER_HPP_
#define _SSF_CORE_INT_PARAMETER_HPP_

#include "parameter.hpp"

namespace ssf{

	template<class ParamType>
	class NumericParameter : public Parameter < ParamType > {

	public:

		NumericParameter(const ParamType& defaultValue, const std::string& name = "",
			const std::string& description = "", const bool& required = false)
			: Parameter(defaultValue, name, description, required){
			this->mMinValue = std::make_shared<ParamType>(std::numeric_limits<ParamType>::min());
			this->mMaxValue = std::make_shared<ParamType>(std::numeric_limits<ParamType>::max());
		}

		virtual ~NumericParameter(void){
		}

		NumericParameter(const NumericParameter& rhs)
			:Parameter(rhs){
			this->mMinValue = rhs.mMinValue;
			this->mMaxValue = rhs.mMaxValue;
		}

		NumericParameter& operator=(const NumericParameter& rhs){
			if (this != &rhs){
				Parameter::operator=(rhs);
				this->mMinValue = rhs.mMinValue;
				this->mMaxValue = rhs.mMaxValue;
			}
			return *this;
		}

		void setValue(const ParamType& value) {
			if (value < *(this->mMinValue) || value > *(this->mMaxValue)){
				//std::string message = "The value must be between" + this->getMinValue() + " and " + this->getMaxValue();
				std::string message("teste");
				throw ParameterException(this->getName(), message);
			}
			*(this->mValue) = value;
			*(this->mChanged) = true;
		}

		ParamType getMaxValue() const { 
			return *(this->mMaxValue); 
		}

		void setMaxValue(const ParamType& maxValue) { 
			*(this->mMaxValue) = maxValue;
		}

		ParamType getMinValue() const { 
			return *(this->mMinValue);
		}

		void setMinValue(const ParamType& minValue) { 
			*(this->mMinValue) = minValue;
		}

	protected:
		std::shared_ptr<ParamType> mMaxValue;		
		std::shared_ptr<ParamType> mMinValue;

	};

	class IntegerParameter : public NumericParameter < long long > {

	public:
		IntegerParameter(const long long& defaultValue = 0, const std::string& name = "",
			const std::string& description = "", const bool& required = false);
		virtual ~IntegerParameter(void);
		IntegerParameter(const IntegerParameter& rhs);
		IntegerParameter& operator=(const IntegerParameter& rhs);

		ParamTypeID getParamType() const;

	};

	class RealParameter : public NumericParameter < double > {

	public:
		RealParameter(const double& defaultValue = 0.0, const std::string& name = "",
			const std::string& description = "", const bool& required = false);
		virtual ~RealParameter(void);
		RealParameter(const RealParameter& rhs);
		RealParameter& operator=(const RealParameter& rhs);

		ParamTypeID getParamType() const;

	};

}

#endif // !_SSF_CORE_INT_PARAMETER_HPP_