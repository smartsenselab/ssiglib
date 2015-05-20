#ifndef _SSF_CORE_CAMERA_HPP_
#define _SSF_CORE_CAMERA_HPP_

#include "cameras/cameras_defs.hpp"

namespace ssf{

	class Camera{
	
	public:
		CAMERAS_EXPORT Camera(void);
		CAMERAS_EXPORT virtual ~Camera(void);
		CAMERAS_EXPORT Camera(const Camera& rhs);
		CAMERAS_EXPORT Camera& operator=(const Camera& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_CAMERA_HPP_