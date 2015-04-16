#include <gtest/gtest.h>
#include <fstream>

#include <core/log.hpp>

TEST(Log, messages) {
	ssf::Log::init();
	ssf::Log::INFO("message info");
	ssf::Log::ERROR("message error");
	ssf::Log::DEBUG("message debug");
	ssf::Log::WARNING("message warning");
}