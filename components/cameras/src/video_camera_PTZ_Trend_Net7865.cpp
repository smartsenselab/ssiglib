
#include <iostream>
#include "cameras/video_camera_PTZ_Trend_Net7865.hpp"
#include <string>
#include <boost/asio.hpp>
#include <istream>
#include <ostream>


#include <core\exception.hpp>

namespace ssf{

	VideoCameraPTZTrendNet7865::VideoCameraPTZTrendNet7865(const std::string& address)
		: VideoCameraPTZ(address){
		this->mMaxZoom = 0;//"enviar comando camera que pega o max zoom";
		//this->io_service = NULL; 
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


	bool VideoCameraPTZTrendNet7865::setPAN(float angle) {
				
			boost::asio::io_service io_service;
			
			// Get a list of endpoints corresponding to the server name.
			boost::asio::ip::tcp::resolver resolver(io_service);
			boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

			// Try each endpoint until we successfully establish a connection.
			boost::asio::ip::tcp::socket socket(io_service);
			boost::asio::connect(socket, endpoint_iterator);

			// Form the request. We specify the "Connection: close" header so that the
			// server will close the socket after transmitting the response. This will
			// allow us to treat all data up until the EOF as the content.
			
			boost::asio::streambuf request;
			std::ostream request_stream(&request);
			request_stream << "GET /cgi/ptdc.cgi?command=set_relative_pos&posX="<< std::to_string(angle) << "&posY=0" << " HTTP/1.0\r\n";
			request_stream << "Host: "<< this->mAddress << "\r\n";
			request_stream << "Connection: close\r\n\r\n";
		
			// Send the request.
			boost::asio::write(socket, request);

			// Read the response status line. The response streambuf will automatically
			// grow to accommodate the entire line. The growth may be limited by passing
			// a maximum size to the streambuf constructor.
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");

			// Check that response is OK.
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
				
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				std::cout << "Invalid response\n";
				return 1;
			}
			if (status_code != 200)
			{
				std::cout << "Response returned with status code " << status_code << "\n";
				return 1;
			}
			
			// Read the response headers, which are terminated by a blank line.
			boost::asio::read_until(socket, response, "\r\n\r\n");

			// Process the response headers.
			std::string header;
			while (std::getline(response_stream, header) && header != "\r")
				std::cout << header << "\n";
			std::cout << "\n";

			// Write whatever content we already have to output.
			if (response.size() > 0)
				std::cout << &response;

			// Read until EOF, writing data to output as we go.
			boost::system::error_code error;
			while (boost::asio::read(socket, response,
				boost::asio::transfer_at_least(1), error))
				std::cout << &response;
			if (error != boost::asio::error::eof)
				throw boost::system::system_error(error);
		
			return true;
	}

	bool VideoCameraPTZTrendNet7865::setTILT(float angle) {
		
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(this->mAddress, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.

		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET /cgi/ptdc.cgi?command=set_relative_pos&posY="<< std::to_string(angle) <<  "&posX=0" << " HTTP/1.0\r\n";
		request_stream << "Host: " << this->mAddress << "\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);

		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return 1;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			return 1;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
			std::cout << &response;

		// Read until EOF, writing data to output as we go.
		boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
			std::cout << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		return true;
	}
}
