#include <gtest/gtest.h>

#include <core/exception.hpp>

TEST(Exception, throw_exception) {
	try{
		throw ssf::Exception("message");
	}catch (ssf::Exception& e){
		EXPECT_STREQ("message", e.what());
	}
}