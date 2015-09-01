#ifndef _SSF_CAMERAS_IP_ONVIF_PTZ_HPP_
#define _SSF_CAMERAS_IP_ONVIF_PTZ_HPP_

#include "cameras/ip_video_camera_PTZ.hpp"
#include <boost/asio.hpp>

namespace ssf{

	class OnvifPTZ : public IPVideoCameraPTZ{
	
	public:
		CAMERAS_EXPORT OnvifPTZ(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~OnvifPTZ(void);
		CAMERAS_EXPORT OnvifPTZ(const OnvifPTZ& rhs);
		CAMERAS_EXPORT OnvifPTZ& operator=(const OnvifPTZ& rhs);

		CAMERAS_EXPORT virtual int getFPS() { return 0; } //Reports actual status of the FPS camera
		//CAMERAS_EXPORT virtual Point2Di getResolution() { return Point2Di(); } //Reports actual status of the resolution camera

		CAMERAS_EXPORT virtual float getCurrentZoom(){ return 0; } //Reports actual status of the zoom camera.
		CAMERAS_EXPORT virtual float getCurrentPan(){ return 0; } //Reports actual status of the pan camera
		CAMERAS_EXPORT virtual float getCurrentTilt(){ return 0; } // Reports actual status of the tilt camera

		CAMERAS_EXPORT bool setZoom(float angle); //Send zoom for camera
		CAMERAS_EXPORT bool setPAN(float angle); //Send pan for camera
		CAMERAS_EXPORT bool setTILT(float angle); //Send tilt for camera
		CAMERAS_EXPORT void getPosition();
		CAMERAS_EXPORT void goHome(){};
				

	private:
		std::string mUrl; 

	};

}

#endif // !_SSF_CAMERAS_IP_ONVIF_PTZ_HPP_