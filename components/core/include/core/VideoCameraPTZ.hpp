#ifndef _SSF_CORE_VIDEOCAMERAPTZ_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZ_HPP_

#include "VideoCamera.hpp"

namespace ssf{

	class VideoCameraPTZ : public VideoCamera{
		
		virtual float getMaxZoom() = 0;
		virtual float getCurrentPAN() = 0;
		virtual void setPAN(float angle) = 0;

	public:
		VideoCameraPTZ(void);
		virtual ~VideoCameraPTZ(void);
		VideoCameraPTZ(const VideoCameraPTZ& rhs);
		VideoCameraPTZ& operator=(const VideoCameraPTZ& rhs);

	private:
		//private members

	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZ_HPP_