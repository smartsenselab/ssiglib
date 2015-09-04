#ifndef _SSF_CORE_IPVideoCamera_HPP_
#define _SSF_CORE_IPVideoCamera_HPP_


#include "cameras/ip_camera.hpp"
#include <iostream>


namespace ssf{

	class IPVideoCamera : public IPCamera{

	public:
		CAMERAS_EXPORT IPVideoCamera(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~IPVideoCamera(void);
		CAMERAS_EXPORT IPVideoCamera(const IPVideoCamera& rhs);
		CAMERAS_EXPORT IPVideoCamera& operator=(const IPVideoCamera& rhs);

		CAMERAS_EXPORT virtual int getFPS() = 0;
		//CAMERAS_EXPORT virtual Point2Di getResolution() = 0;

		CAMERAS_EXPORT virtual void setAddress(std::string IP);
		CAMERAS_EXPORT virtual std::string getAddress();

	protected:
		std::string mAddress;

	};

}

#endif // !_SSF_CORE_IPVideoCamera_HPP_