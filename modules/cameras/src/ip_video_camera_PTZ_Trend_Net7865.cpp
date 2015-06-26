
#include "cameras/ip_video_camera_PTZ_Trend_Net7865.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <core/exception.hpp>

namespace ssf{

	IPVideoCameraPTZTrendNet7865::IPVideoCameraPTZTrendNet7865(const std::string& address)
		: IPVideoCameraPTZ(address){
		this->mMaxZoom = 0;
		
		if (this->mAddress.empty())
			throw Exception("The camera address does not be empty");

		this->mUrl = "http://" + this->mAddress + "/cgi/ptdc.cgi?command=set_relative_";

	}

	IPVideoCameraPTZTrendNet7865::~IPVideoCameraPTZTrendNet7865(){
		//Destructor
	}

	IPVideoCameraPTZTrendNet7865::IPVideoCameraPTZTrendNet7865(const IPVideoCameraPTZTrendNet7865& rhs){
		this->mUrl = rhs.mUrl;
	}

	IPVideoCameraPTZTrendNet7865& IPVideoCameraPTZTrendNet7865::operator=(const IPVideoCameraPTZTrendNet7865& rhs){
		if (this != &rhs){
			this->mUrl = rhs.mUrl;
		}
		return *this;
	}


	bool IPVideoCameraPTZTrendNet7865::setPAN(float angle) {
				
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
			request_stream << "GET /cgi/ptdc.cgi?command=set_relative_pos&posX="<< std::to_string(angle) << "&posY=0" << " HTTP/1.0\r\n";
			request_stream << "Host: "<< this->mAddress << "\r\n";
			request_stream << "Connection: close\r\n\r\n";
		
			// Send the request.
			boost::asio::write(socket, request);

			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");
			
			if (this->mCheck){
	
				checkCommand(&response);
			}

			return true;
	}

	bool IPVideoCameraPTZTrendNet7865::setTILT(float angle) {
		
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
		request_stream << "GET /cgi/ptdc.cgi?command=set_relative_pos&posY="<< std::to_string(angle) <<  "&posX=0" << " HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		if (this->mCheck){

			checkCommand(&response);
		}

		return true;
	}
	
	void IPVideoCameraPTZTrendNet7865::goHome(){

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
		request_stream << "GET /cgi/ptdc.cgi?command=go_home HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		if (this->mCheck){

			checkCommand(&response);
		}


	}

	bool IPVideoCameraPTZTrendNet7865::setZoom(float angle){


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
		request_stream << "GET /cgi/ptdc.cgi?command=set_relative_zoom&zoom_mag=" << std::to_string(angle) << " HTTP/1.1\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		if (this->mCheck){

			checkCommand(&response);
		}

		return true;
	}

	bool IPVideoCameraPTZTrendNet7865::checkCommand(boost::asio::streambuf *response){

		std::istream response_stream(response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			throw Exception("Invalid response\n");
			return false;
		}
		else
			return true;

	}
	bool IPVideoCameraPTZTrendNet7865::check(){
		return this->mCheck = true;
	}
}
