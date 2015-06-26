#include "cameras/ip_onvif_ptz.hpp"
#include "cameras/ip_video_camera_PTZ.hpp"
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "core/exception.hpp"
#include <boost/asio.hpp>

namespace ssf{

	OnvifPTZ::OnvifPTZ(const std::string& address)
		:IPVideoCameraPTZ(address){
		
		this->mMaxZoom = 0;

		if (this->mAddress.empty())
			throw Exception("The camera address does not be empty");

		this->mUrl = "http://" + this->mAddress + "/axis-cgi/com/ptz.cgi?";
	}

	OnvifPTZ::~OnvifPTZ(){
		//Destructor
	}

	OnvifPTZ::OnvifPTZ(const OnvifPTZ& rhs){
		this->mUrl = rhs.mUrl;

	}

	OnvifPTZ& OnvifPTZ::operator=(const OnvifPTZ& rhs){
		if (this != &rhs){
			this->mUrl = rhs.mUrl;
		}
	    return *this;
	}
	bool OnvifPTZ::setZoom(float angle){

		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET /axis-cgi/com/ptz.cgi?zoom=" << std::to_string(angle) << " HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		return true;
	}

	bool OnvifPTZ::setPAN(float angle){

		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET /axis-cgi/com/ptz.cgi?pan=" << std::to_string(angle) << " HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		return true;
	}

	bool OnvifPTZ::setTILT(float angle){


		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET /axis-cgi/com/ptz.cgi?tilt=" << std::to_string(angle) << " HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		return true;

	}
	void OnvifPTZ::getPosition(){


		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET /axis-cgi/com/ptz.cgi?query=position HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		response.commit(1000);

		std::istream is(&response);
		std::vector<std::string> page;
		std::string s;
		int i = 0 ;
		while (i < response.size()){
			is >> s;
			page.push_back(s);
			i++;
		}
		for (std::vector<std::string>::iterator it = page.begin(); it != page.end(); it++){
			
			
				std::cout << *it << std::endl;
 		}
		std::cout << std::atoi(page[7].data()) << "Aqui";
	}
}

