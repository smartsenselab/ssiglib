#ifndef _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "cameras\video_camera_PTZ.hpp"

namespace ssf{

	class VideoCameraPTZTrendNet7865 : public VideoCameraPTZ{
	
		float constant;

	public:
		VideoCameraPTZTrendNet7865(const std::string& address = "localhost");
		virtual ~VideoCameraPTZTrendNet7865(void);
		VideoCameraPTZTrendNet7865(const VideoCameraPTZTrendNet7865& rhs);
		VideoCameraPTZTrendNet7865& operator=(const VideoCameraPTZTrendNet7865& rhs);

		virtual float getCurrentZoom(){ return 0; } //informa o atual Zoom da camera
		virtual float getCurrentPan(){ return 0; } //informa o atual Pan da camera
		virtual float getCurrentTilt(){ return 0; } //informa o atual Tilt da camera
						
		bool setZoom(float angle) { return 0 ; } //Envia o Zoom para a camera
		bool setPAN(float angle); //Envia o Pan para a camera
		bool setTILT(float angle); //Envia o Tilt para a camera

	private:
		boost::asio::ip::tcp::resolver::query go(std::string xpos, std::string ypos); 

	private:
		boost::asio::io_service io_service;
		std::string url;

	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_