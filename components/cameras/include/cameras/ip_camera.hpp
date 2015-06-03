#ifndef _SSF_CORE_IPCAMERA_HPP_
#define _SSF_CORE_IPCAMERA_HPP_

#include "cameras/cameras_defs.hpp"

namespace ssf{

	class IPCamera{
	
	public:
		CAMERAS_EXPORT IPCamera(void);
		CAMERAS_EXPORT virtual ~IPCamera(void);
		CAMERAS_EXPORT IPCamera(const IPCamera& rhs);
		CAMERAS_EXPORT IPCamera& operator=(const IPCamera& rhs);

	protected:
		bool mCheck = false;

	};

}

#endif // !_SSF_CORE_IPCAMERA_HPP_