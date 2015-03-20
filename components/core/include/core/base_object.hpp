#ifndef _SSF_CORE_BASE_OBJECT_HPP_
#define _SSF_CORE_BASE_OBJECT_HPP_

namespace ssf{

	class BaseObject{
	
	public:
		BaseObject(void);
		virtual ~BaseObject(void);
		BaseObject(const BaseObject& rhs);
		BaseObject& operator=(const BaseObject& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_BASE_OBJECT_HPP_