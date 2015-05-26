#ifndef _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "cameras\video_camera_PTZ.hpp"

namespace ssf{

	class VideoCameraPTZTrendNet7865 : public VideoCameraPTZ{
	
	
	public:
		CAMERAS_EXPORT VideoCameraPTZTrendNet7865(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~VideoCameraPTZTrendNet7865(void);
		CAMERAS_EXPORT VideoCameraPTZTrendNet7865(const VideoCameraPTZTrendNet7865& rhs);
		CAMERAS_EXPORT VideoCameraPTZTrendNet7865& operator=(const VideoCameraPTZTrendNet7865& rhs);

		CAMERAS_EXPORT virtual int getFPS() { return 0; }
		CAMERAS_EXPORT virtual Point2Di getResolution() { return Point2Di(); }

		CAMERAS_EXPORT virtual float getCurrentZoom(){ return 0; } //informa o atual Zoom da camera
		CAMERAS_EXPORT virtual float getCurrentPan(){ return 0; } //informa o atual Pan da camera
		CAMERAS_EXPORT virtual float getCurrentTilt(){ return 0; } //informa o atual Tilt da camera
						
		CAMERAS_EXPORT bool setZoom(float angle) { return 0; } //Envia o Zoom para a camera
		CAMERAS_EXPORT bool setPAN(float angle); //Envia o Pan para a camera
		CAMERAS_EXPORT bool setTILT(float angle); //Envia o Tilt para a camera

	private:
	//	boost::asio::io_service VideoCameraPTZTrendNet7865::go(std::string xpos, std::string ypos);

	private:
	
		std::string url;

	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_