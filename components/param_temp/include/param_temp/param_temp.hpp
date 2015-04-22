#ifndef _SSF_PARAM_TEMP_PARAM_TEMP_HPP_
#define _SSF_PARAM_TEMP_PARAM_TEMP_HPP_

namespace ssf{

    template <class T>
	class ParamTemp{
	
	public:
		ParamTemp(const T& value);
		virtual ~ParamTemp(void);
		ParamTemp(const ParamTemp& rhs);
		T& operator=(const ParamTemp& rhs);
        
        T getValue();

	private:
        T value;

	};

}

#endif // !_SSF_PARAM_TEMP_PARAM_TEMP_HPP_