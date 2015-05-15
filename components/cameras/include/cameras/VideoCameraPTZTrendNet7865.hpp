#ifndef _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_
#define _SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace ssf{

	class VideoCameraPTZTrendNet7865{
	
		//Colocar URLs
		//boost::asio::io_service curl;
		std::string url;
		std::string user;
		std::string pwd;
		double constant;

		inline boost::asio::ip::tcp::resolver::query &go(std::string xpos, std::string ypos) {
			
			std::string str = url + "pos&posX=" + xpos + "&posY=" + ypos;
			boost::asio::ip::tcp::resolver::query query(str, "http"); 
			return query;
			
		}
		
		inline boost::asio::ip::tcp::resolver::query &goZoom(std::string xpos) {
			std::string str = url + "zoom&zoom_mag=" + xpos;
			boost::asio::ip::tcp::resolver::query query(str, "http");
			return query;
		}

	protected:

		bool Left(int angle);
		bool Right(int angle);
		bool Up(int angle);
		bool Down(int angle);
		bool Zoom(int angle);

	public:
		VideoCameraPTZTrendNet7865(void);
		virtual ~VideoCameraPTZTrendNet7865(void);
		VideoCameraPTZTrendNet7865(const VideoCameraPTZTrendNet7865& rhs);
		VideoCameraPTZTrendNet7865& operator=(const VideoCameraPTZTrendNet7865& rhs);
		float VideoCameraPTZTrendNet7865::getMaxZoom();
		void VideoCameraPTZTrendNet7865::Setup(std::string ip);
	private:
		//private members

	};

}

#endif // !_SSF_CORE_VIDEOCAMERAPTZTRENDNET7865_HPP_