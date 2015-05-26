#ifndef _SSF_CORE_VIDEOCAMERAPTZ_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZ_HPP_

#include "cameras\video_camera.hpp"
#include "cameras\video_camera_PTZ.hpp"

namespace ssf{

	class VideoCameraPTZ : public VideoCamera{
		
	public:

		CAMERAS_EXPORT VideoCameraPTZ(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~VideoCameraPTZ(void);
		CAMERAS_EXPORT VideoCameraPTZ(const VideoCameraPTZ& rhs);
		CAMERAS_EXPORT VideoCameraPTZ& operator=(const VideoCameraPTZ& rhs);

		CAMERAS_EXPORT virtual float getMaxZoom(); //informa o Zoom maximo atingido pela camera
		CAMERAS_EXPORT virtual float getMaxTilt(); //informa o Tilt maximo atingido pela camera
		CAMERAS_EXPORT virtual float getCurrentZoom() = 0; //informa o atual Zoom da camera
		CAMERAS_EXPORT virtual float getCurrentPan() = 0; //informa o atual Pan da camera
		CAMERAS_EXPORT virtual float getCurrentTilt() = 0; //informa o atual Tilt da camera

		CAMERAS_EXPORT virtual bool setZoom(float angle) = 0; //Envia o Zoom para a camera
		CAMERAS_EXPORT virtual bool setPAN(float angle) = 0; //Envia o Pan para a camera
		CAMERAS_EXPORT virtual bool setTILT(float angle) = 0; //Envia o Tilt para a camera

	

	protected:
		float mMaxZoom; 
		float mMaxTilt;
	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZ_HPP_