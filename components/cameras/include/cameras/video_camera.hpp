#ifndef _SSF_CORE_VIDEOCAMERA_HPP_
#define _SSF_CORE_VIDEOCAMERA_HPP_

#include <iostream>
#include <core/point2d.hpp>

#include "cameras/camera.hpp"

namespace ssf{

	class VideoCamera : public Camera{

	public:
		VideoCamera(void);
		virtual ~VideoCamera(void);
		VideoCamera(const VideoCamera& rhs);
		VideoCamera& operator=(const VideoCamera& rhs);

		virtual int getFPS() = 0;
		virtual Point2Di getResolution() = 0;

		virtual void setAddress(std::string IP);
		virtual std::string getAddress();

	private:
		std::string mAddress;

	};

}

#endif // !_SSF_CORE_VIDEOCAMERA_HPP_