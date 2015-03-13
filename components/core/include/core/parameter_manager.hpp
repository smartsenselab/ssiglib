#ifndef _SSF_CORE_PARAMETER_MANAGER_HPP_
#define _SSF_CORE_PARAMETER_MANAGER_HPP_

namespace ssf{

	class ParameterManager{
	
	public:
		ParameterManager(void);
		virtual ~ParameterManager(void);
		ParameterManager(const ParameterManager& rhs);
		ParameterManager& operator=(const ParameterManager& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_PARAMETER_MANAGER_HPP_