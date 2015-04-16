#include "core/log.hpp"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace ssf{


	void Log::init()
	{
		boost::log::add_file_log("test.log");
		boost::log::add_common_attributes();
	}

	//void setFilter(boost::log::trivial::filter){
	//	boost::log::core::get()->set_filter
	//		(
	//		boost::log::trivial::severity >= boost::log::trivial::filter
	//		);
	//}

	void Log::INFO(std::string message){
		BOOST_LOG_TRIVIAL(info) << message;
	}

	void Log::ERROR(std::string message){
		BOOST_LOG_TRIVIAL(error) << message;
	}

	void Log::DEBUG(std::string message){

		BOOST_LOG_TRIVIAL(debug) << message;

	}

	void Log::WARNING(std::string message){

		BOOST_LOG_TRIVIAL(warning) << message;

	}

}

