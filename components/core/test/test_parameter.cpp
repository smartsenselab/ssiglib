#include <gtest/gtest.h>

#include "core/parameter.hpp"

class TestParameter : public ::testing::Test{
protected:
	TestParameter(){

	}

	virtual void SetUp(){

	}

	ssf::Parameter<int> paramInt;
	ssf::Parameter<long> paramLong;
	ssf::Parameter<float> paramFloat;
	ssf::Parameter<double> paramDouble;
	ssf::Parameter<bool> paramBool;
	ssf::Parameter<std::string> paramString;
	ssf::Parameter<ssf::FileHandle> paramFileHandle;
	ssf::Parameter<ssf::DirectoryHandle> paramDirectoryHandle;

};


TEST_F(TestParameter, constructor){
	EXPECT_NO_THROW(ssf::Parameter<int> testInt);
	EXPECT_NO_THROW(ssf::Parameter<long> testLong);
	EXPECT_NO_THROW(ssf::Parameter<float> testFloat);
	EXPECT_NO_THROW(ssf::Parameter<double> testDouble);
	EXPECT_NO_THROW(ssf::Parameter<bool> testBool);
	EXPECT_NO_THROW(ssf::Parameter<std::string> testString);
	EXPECT_NO_THROW(ssf::Parameter<ssf::FileHandle> tesFileHandle);
	EXPECT_NO_THROW(ssf::Parameter<ssf::DirectoryHandle> testDirectoryHandle);
	EXPECT_ANY_THROW(ssf::Parameter<long long> testLongLong);
}


TEST_F(TestParameter, getValue){
	EXPECT_ANY_THROW(paramInt.getValue());
	EXPECT_ANY_THROW(paramLong.getValue());
	EXPECT_ANY_THROW(paramFloat.getValue());
	EXPECT_ANY_THROW(paramDouble.getValue());
	EXPECT_ANY_THROW(paramBool.getValue());
	EXPECT_ANY_THROW(paramString.getValue());
	EXPECT_ANY_THROW(paramFileHandle.getValue());
	EXPECT_ANY_THROW(paramDirectoryHandle.getValue());
}

TEST_F(TestParameter, getName){
	EXPECT_ANY_THROW(paramInt.getName());
	EXPECT_ANY_THROW(paramLong.getName());
	EXPECT_ANY_THROW(paramFloat.getName());
	EXPECT_ANY_THROW(paramDouble.getName());
	EXPECT_ANY_THROW(paramBool.getName());
	EXPECT_ANY_THROW(paramString.getName());
	EXPECT_ANY_THROW(paramFileHandle.getName());
	EXPECT_ANY_THROW(paramDirectoryHandle.getName());
}