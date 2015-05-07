


#include <iostream>
#include "core/VideoCameraPTZTrendNet7865.hpp"
#include <string>

namespace ssf{

	VideoCameraPTZTrendNet7865::VideoCameraPTZTrendNet7865(){
		//Constructor
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

	bool VideoCameraPTZTrendNet7865::Left(int angle)	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go(std::to_string((-angle*constant)), "0"));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}
	bool VideoCameraPTZTrendNet7865::Right(int angle) {
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go(std::to_string((angle*constant)), "0"));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}
	bool VideoCameraPTZTrendNet7865::Up(int angle) {
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go("0", std::to_string((-angle*constant))));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}

	bool VideoCameraPTZTrendNet7865::Down(int angle) {
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::iterator code = resolver.resolve(go("0",std::to_string((angle*constant))));
		if (code->endpoint().size() == 0)
			return false;
		return true;
	}

	void VideoCameraPTZTrendNet7865::Setup(std::string ip) {
		
		if (ip.empty())
		 std::cout << "IP adress not set." ;

		url = "http://" + ip + "/cgi/ptdc.cgi?command=set_relative_";

		std::cout << "IP Camera IP_IP607 (%s) ready to receive commands." << ip.c_str();
	}

}

