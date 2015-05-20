#ifndef _SSF_CORE_VIDEOCAMERA_HPP_
#define _SSF_CORE_VIDEOCAMERA_HPP_

#include <iostream>
#include <core/point2d.hpp>

#include "cameras/camera.hpp"

namespace ssf{

	class VideoCamera : public Camera{

	public:
		CAMERAS_EXPORT VideoCamera(const std::string& address = "localhost");
		CAMERAS_EXPORT virtual ~VideoCamera(void);
		CAMERAS_EXPORT VideoCamera(const VideoCamera& rhs);
		CAMERAS_EXPORT VideoCamera& operator=(const VideoCamera& rhs);

		CAMERAS_EXPORT virtual int getFPS() = 0;
		CAMERAS_EXPORT virtual Point2Di getResolution() = 0;

		CAMERAS_EXPORT virtual void setAddress(std::string IP);
		CAMERAS_EXPORT virtual std::string getAddress();

	protected:
		std::string mAddress;

	};

}

#endif // !_SSF_CORE_VIDEOCAMERA_HPP_