#ifndef _SSF_CORE_BASE_OBJECT_HPP_
#define _SSF_CORE_BASE_OBJECT_HPP_

#include "core/base.hpp"

namespace ssf{

	class BaseObject{
	
	public:
		SSF_EXPORT BaseObject(void);
		SSF_EXPORT virtual ~BaseObject(void);
		SSF_EXPORT BaseObject(const BaseObject& rhs);
		SSF_EXPORT BaseObject& operator=(const BaseObject& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_BASE_OBJECT_HPP_