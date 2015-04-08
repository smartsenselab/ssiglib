#ifndef _SSF_CORE_LOG_HPP_
#define _SSF_CORE_LOG_HPP_

namespace ssf{

	class Log{
	
	public:
		Log(void);
		virtual ~Log(void);
		Log(const Log& rhs);
		Log& operator=(const Log& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_LOG_HPP_