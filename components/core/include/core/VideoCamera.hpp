#ifndef _SSF_CORE_VIDEOCAMERA_HPP_
#define _SSF_CORE_VIDEOCAMERA_HPP_

#include <iostream>
#include "Camera.hpp"

namespace ssf{

	class VideoCamera : public Camera{

			virtual int getFPS() = 0;
			virtual std::pair<int, int> getResolution() = 0;
			
			virtual void setIP(std::string IP){
				this->mIP = IP;
			}

			virtual std::string getIP(){
				return this->mIP;
			}

	private:
		std::string mIP;


	public:
		VideoCamera(void);
		virtual ~VideoCamera(void);
		VideoCamera(const VideoCamera& rhs);
		VideoCamera& operator=(const VideoCamera& rhs);

	private:
		//private members
//	std::string mIP;

	};

}

#endif // !_SSF_CORE_VIDEOCAMERA_HPP_