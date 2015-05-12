#include "core/log.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace ssf{


	void Log::outputConsole(const bool& option){
		if (option == true){
			boost::log::add_console_log(std::cout);
			boost::log::add_common_attributes();
		}
	}

	void Log::outputFile(const bool& option, const std::string& fileName /*= "output.log"*/){
		if (option == true){
			boost::log::add_file_log(fileName);
			boost::log::add_common_attributes();
		}
	}

	void Log::setFilter(const LogFilter& filter){

		int filter_level;

		switch (filter){
		case LogFilter::DEBUG: filter_level = boost::log::trivial::debug;
			break;
		case LogFilter::INFO: filter_level = boost::log::trivial::info;
			break;
		case LogFilter::WARNING: filter_level = boost::log::trivial::warning;
			break;
		case LogFilter::ERROR: filter_level = boost::log::trivial::error;
			break;
		}

		boost::log::core::get()->set_filter
			(
			boost::log::trivial::severity >= filter_level
			);
	}

	void Log::INFO(const std::string& message){
		BOOST_LOG_TRIVIAL(info) << message;
	}

	void Log::ERROR(const std::string& message){
		BOOST_LOG_TRIVIAL(error) << message;
	}

	void Log::DEBUG(const std::string& message){
		BOOST_LOG_TRIVIAL(debug) << message;
	}

	void Log::WARNING(const std::string& message){
		BOOST_LOG_TRIVIAL(warning) << message;
	}

}

