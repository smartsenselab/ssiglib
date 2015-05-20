#ifndef _SSF_CORE_VIDEOCAMERAPTZ_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZ_HPP_

#include "video_camera.hpp"
#include "video_camera_PTZ.hpp"

namespace ssf{

	class VideoCameraPTZ : public VideoCamera{
		
	public:

		VideoCameraPTZ(const std::string& address = "localhost");
		virtual ~VideoCameraPTZ(void);
		VideoCameraPTZ(const VideoCameraPTZ& rhs);
		VideoCameraPTZ& operator=(const VideoCameraPTZ& rhs);

		virtual float getMaxZoom(); //informa o Zoom maximo atingido pela camera
		virtual float getMaxTilt(); //informa o Tilt maximo atingido pela camera
		virtual float getCurrentZoom() = 0; //informa o atual Zoom da camera
		virtual float getCurrentPan() = 0; //informa o atual Pan da camera
		virtual float getCurrentTilt() = 0; //informa o atual Tilt da camera

		virtual bool setZoom(float angle) = 0; //Envia o Zoom para a camera
		virtual bool setPAN(float angle) = 0; //Envia o Pan para a camera
		virtual bool setTILT(float angle) = 0; //Envia o Tilt para a camera

	

	protected:
		float mMaxZoom; 
		float mMaxTilt;
	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZ_HPP_