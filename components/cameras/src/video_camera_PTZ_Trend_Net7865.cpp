
#include <iostream>
#include "cameras/video_camera_PTZ_Trend_Net7865.hpp"
#include <string>

#include <core\exception.hpp>

namespace ssf{

	VideoCameraPTZTrendNet7865::VideoCameraPTZTrendNet7865(const std::string& address)
		: VideoCameraPTZ(address){
		this->mMaxZoom = 0;//"enviar comando camera que pega o max zoom";
		
		if (this->mAddress.empty())
			throw Exception("The camera address does not be empty");

		this->url = "http://" + this->mAddress + "/cgi/ptdc.cgi?command=set_relative_";
	}

	VideoCameraPTZTrendNet7865::~VideoCameraPTZTrendNet7865(){
		//Destructor
	}

	VideoCameraPTZTrendNet7865::VideoCameraPTZTrendNet7865(const VideoCameraPTZTrendNet7865& rhs){
		//Constructor Copy
	}

	VideoCameraPTZTrendNet7865& VideoCameraPTZTrendNet7865::operator=(const VideoCameraPTZTrendNet7865& rhs){
		if (this != &rhs){
			//code here
		}
	    return *this;
	}

	boost::asio::ip::tcp::resolver::query VideoCameraPTZTrendNet7865::go(std::string xpos, std::string ypos) {

		boost::asio::ip::tcp::resolver resolver(io_service);
		std::string str = this->url + "pos&posX=" + xpos + "&posY=" + ypos;
		boost::asio::ip::tcp::resolver::query query(str, "http");
		boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
		return query;

	}
	
	
	bool VideoCameraPTZTrendNet7865::setPAN(float angle)	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go(std::to_string((angle*constant)), "0"));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}

	bool VideoCameraPTZTrendNet7865::setTILT(float angle) {
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go("0", std::to_string((-angle*constant))));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}


}

