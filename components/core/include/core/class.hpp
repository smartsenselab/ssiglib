#ifndef _SSF_CORE_CLASS_HPP_
#define _SSF_CORE_CLASS_HPP_

namespace ssf{

	class Class{
	
	public:
		Class(void);
		virtual ~Class(void);
		Class(const Class& other);
		Class& operator=(const Class& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_CLASS_HPP_