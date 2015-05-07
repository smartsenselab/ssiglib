#ifndef _SSF_CORE_SMDATA_HPP_
#define _SSF_CORE_SMDATA_HPP_

namespace ssf{

	class SMData{
	
	public:
		SMData(void);
		virtual ~SMData(void);
		SMData(const SMData& rhs);
		SMData& operator=(const SMData& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_SMDATA_HPP_