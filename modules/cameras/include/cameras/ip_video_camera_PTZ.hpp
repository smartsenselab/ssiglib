#ifndef _SSF_CORE_IPVideoCameraPTZ_HPP_
#define _SSF_CORE_IPVideoCameraPTZ_HPP_

#include "cameras/ip_video_camera.hpp"
#include "cameras/ip_video_camera_PTZ.hpp"

namespace ssf{

	class IPVideoCameraPTZ : public IPVideoCamera{
		
	public:

		CAMERAS_EXPORT IPVideoCameraPTZ(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~IPVideoCameraPTZ(void);
		CAMERAS_EXPORT IPVideoCameraPTZ(const IPVideoCameraPTZ& rhs);
		CAMERAS_EXPORT IPVideoCameraPTZ& operator=(const IPVideoCameraPTZ& rhs);

		CAMERAS_EXPORT virtual float getMaxZoom(); //Reports actual status of the FPS camera
		CAMERAS_EXPORT virtual float getMaxTilt(); //Reports actual status of the resolution camera
		CAMERAS_EXPORT virtual float getCurrentZoom() = 0; //Reports actual status of the zoom camera.
		CAMERAS_EXPORT virtual float getCurrentPan() = 0; //Reports actual status of the pan camera
		CAMERAS_EXPORT virtual float getCurrentTilt() = 0; //Reports actual status of the tilt camera

		CAMERAS_EXPORT virtual bool setZoom(float angle) = 0; //Send zoom for camera
		CAMERAS_EXPORT virtual bool setPAN(float angle) = 0;  //Send pan for camera
		CAMERAS_EXPORT virtual bool setTILT(float angle) = 0; //Send tilt for camera
		CAMERAS_EXPORT virtual void goHome() = 0; //Send position initial
	

	protected:
		float mMaxZoom; 
		float mMaxTilt;
	};

}

#endif // !_SSF_CORE_IPVideoCameraPTZ_HPP_