#include <gtest/gtest.h>
#include <fstream>

#include <core/log.hpp>

TEST(Log, messages) {
	//ssf::Log::init();// if 1, you add your log to a file, if not, a log in the console appears.
	ssf::Log::outputConsole(true);
	ssf::Log::outputFile(true);
	ssf::Log::INFO("message info");
	ssf::Log::ERROR("message error");
	ssf::Log::DEBUG("message debug");
	ssf::Log::WARNING("message warning");
}