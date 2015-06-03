#ifndef _SSF_CORE_IPVideoCameraPTZTrendNet7865_HPP_
#define _SSF_CORE_IPVideoCameraPTZTrendNet7865_HPP_

#include "cameras/ip_video_camera_PTZ.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>



namespace ssf{

	class IPVideoCameraPTZTrendNet7865 : public IPVideoCameraPTZ{
	
	
	public:
		CAMERAS_EXPORT IPVideoCameraPTZTrendNet7865(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~IPVideoCameraPTZTrendNet7865(void);
		CAMERAS_EXPORT IPVideoCameraPTZTrendNet7865(const IPVideoCameraPTZTrendNet7865& rhs);
		CAMERAS_EXPORT IPVideoCameraPTZTrendNet7865& operator=(const IPVideoCameraPTZTrendNet7865& rhs);

		CAMERAS_EXPORT virtual int getFPS() { return 0; } //Reports actual status of the FPS camera
		CAMERAS_EXPORT virtual Point2Di getResolution() { return Point2Di(); } //Reports actual status of the resolution camera

		CAMERAS_EXPORT virtual float getCurrentZoom(){ return 0; } //Reports actual status of the zoom camera.
		CAMERAS_EXPORT virtual float getCurrentPan(){ return 0; } //Reports actual status of the pan camera
		CAMERAS_EXPORT virtual float getCurrentTilt(){ return 0; } // Reports actual status of the tilt camera
						
		CAMERAS_EXPORT bool setZoom(float angle); //Send zoom for camera
		CAMERAS_EXPORT bool setPAN(float angle); //Send pan for camera
		CAMERAS_EXPORT bool setTILT(float angle); //Send tilt for camera
		CAMERAS_EXPORT bool checkCommand(boost::asio::streambuf *response); //Send tilt for camera
		CAMERAS_EXPORT void goHome(); //Send position initial
		CAMERAS_EXPORT bool check();

	private:
	
		std::string mUrl;

	};

}

#endif // !_SSF_CORE_IPVideoCameraPTZTrendNet7865_HPP_