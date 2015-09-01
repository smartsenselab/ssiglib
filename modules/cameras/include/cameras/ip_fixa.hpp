#ifndef _SSF_CAMERAS_IP_FIXA_HPP_
#define _SSF_CAMERAS_IP_FIXA_HPP_

#include "cameras/ip_video_camera.hpp"
#include "boost/asio.hpp"

namespace ssf{

	class CameraFixa : public IPVideoCamera{
	
	public:
		CAMERAS_EXPORT CameraFixa();
		CAMERAS_EXPORT virtual ~CameraFixa(void);
		CAMERAS_EXPORT CameraFixa(const CameraFixa& rhs);
		CAMERAS_EXPORT CameraFixa& operator=(const CameraFixa& rhs);

		CAMERAS_EXPORT  virtual int getFPS() = 0; //Reports actual status of the FPS camera
		//CAMERAS_EXPORT  virtual Point2Di getResolution() = 0; //Reports actual status of the resolution camera
		

	private:

	};

}

#endif // !_SSF_CAMERAS_IP_FIXA_HPP_