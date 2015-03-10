#include <gtest/gtest.h>

#include <core/numeric_parameter.hpp>

TEST(Parameter, constructor) {
	ssf::IntegerParameter integerParam(1, "int_param", "int_description", true);
	ssf::RealParameter realParam(1.1, "real_param", "real_description", true);
	
	EXPECT_EQ(1, integerParam.getValue());
	EXPECT_STREQ("int_param", integerParam.getName().c_str());
	EXPECT_STREQ("int_description", integerParam.getDescription().c_str());
	EXPECT_TRUE(integerParam.getRequired());

	EXPECT_EQ(1.1, realParam.getValue());
	EXPECT_STREQ("real_param", realParam.getName().c_str());
	EXPECT_STREQ("real_description", realParam.getDescription().c_str());
	EXPECT_TRUE(realParam.getRequired());
}

