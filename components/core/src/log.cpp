/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                   Software License Agreement (BSD License)
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

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



