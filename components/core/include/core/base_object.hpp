#ifndef _SSF_CORE_BASE_OBJECT_HPP_
#define _SSF_CORE_BASE_OBJECT_HPP_

#include "core/core_defs.hpp"

namespace ssf{

	class BaseObject{
	
	public:

		CORE_EXPORT BaseObject(void);
		CORE_EXPORT virtual ~BaseObject(void);
		CORE_EXPORT BaseObject(const BaseObject& rhs);
		CORE_EXPORT BaseObject& operator=(const BaseObject& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_BASE_OBJECT_HPP_