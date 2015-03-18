#include <gtest/gtest.h>

#include "core/parameter.hpp"
#include "core/parameter_manager.hpp"

class TestParameter : public ::testing::Test{
protected:

	virtual void SetUp(){
		intValue = 99;
		longValue = 99999;
		floatValue = float(99.88);
		doubleValue = 99999.88888888;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");

		EXPECT_NO_THROW(paramManager.registerParameter(paramInt, "paramInt", "description_test_int", true, intValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramLong, "paramLong", "description_test_long", true, longValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramFloat, "paramFloat", "description_test_float", true, floatValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramDouble, "paramDouble", "description_test_double", true, doubleValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramBool, "paramBool", "description_test_bool", true, boolValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramString, "paramString", "description_test_string", true, stringValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramFileHandle, "paramFile", "description_test_file", true, fileHandleValue));
		EXPECT_NO_THROW(paramManager.registerParameter(paramDirectoryHandle, "paramDirectory", "description_test_directory", true, directoryHandleValue));
	}

	int intValue;
	long longValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;

	ssf::Parameter<int> paramInt;
	ssf::Parameter<long> paramLong;
	ssf::Parameter<float> paramFloat;
	ssf::Parameter<double> paramDouble;
	ssf::Parameter<bool> paramBool;
	ssf::Parameter<std::string> paramString;
	ssf::Parameter<ssf::FileHandle> paramFileHandle;
	ssf::Parameter<ssf::DirectoryHandle> paramDirectoryHandle;

	ssf::ParameterManager paramManager;
};


TEST_F(TestParameter, invalidConstructor){
	int a = 0;
	EXPECT_ANY_THROW(ssf::Parameter<long long> testLongLong);
}


TEST_F(TestParameter, getValue){
	EXPECT_NO_THROW(paramInt.getValue());
	EXPECT_NO_THROW(paramLong.getValue());
	EXPECT_NO_THROW(paramFloat.getValue());
	EXPECT_NO_THROW(paramDouble.getValue());
	EXPECT_NO_THROW(paramBool.getValue());
	EXPECT_NO_THROW(paramString.getValue());
	EXPECT_NO_THROW(paramFileHandle.getValue());
	EXPECT_NO_THROW(paramDirectoryHandle.getValue());

	EXPECT_EQ(intValue, paramInt.getValue());
	EXPECT_EQ(longValue, paramLong.getValue());
	EXPECT_EQ(floatValue, paramFloat.getValue());
	EXPECT_EQ(doubleValue, paramDouble.getValue());
	EXPECT_TRUE(paramBool.getValue());
	EXPECT_STREQ(stringValue.c_str(), paramString.getValue().c_str());
	EXPECT_STREQ(fileHandleValue.getAbsoluteFileName().c_str(), paramFileHandle.getValue().getAbsoluteFileName().c_str());
	EXPECT_STREQ(directoryHandleValue.getAbsolutePath().c_str(), paramDirectoryHandle.getValue().getAbsolutePath().c_str());
}

TEST_F(TestParameter, getName){
	EXPECT_NO_THROW(paramInt.getName());
	EXPECT_NO_THROW(paramLong.getName());
	EXPECT_NO_THROW(paramFloat.getName());
	EXPECT_NO_THROW(paramDouble.getName());
	EXPECT_NO_THROW(paramBool.getName());
	EXPECT_NO_THROW(paramString.getName());
	EXPECT_NO_THROW(paramFileHandle.getName());
	EXPECT_NO_THROW(paramDirectoryHandle.getName());

	EXPECT_STREQ("paramInt", paramInt.getName().c_str());
	EXPECT_STREQ("paramLong", paramLong.getName().c_str());
	EXPECT_STREQ("paramFloat", paramFloat.getName().c_str());
	EXPECT_STREQ("paramDouble", paramDouble.getName().c_str());
	EXPECT_STREQ("paramBool", paramBool.getName().c_str());
	EXPECT_STREQ("paramString", paramString.getName().c_str());
	EXPECT_STREQ("paramFile", paramFileHandle.getName().c_str());
	EXPECT_STREQ("paramDirectory", paramDirectoryHandle.getName().c_str());
}

TEST_F(TestParameter, invalidRegisterParameter){
	//Parameter already registered
	EXPECT_ANY_THROW(paramManager.registerParameter(paramInt, "otherName", "description_test_int", true, 0));
	//Parameter name already exists
	EXPECT_ANY_THROW(paramManager.registerParameter(paramDouble, "paramInt", "description_test_double", true, 0.0));
}

TEST_F(TestParameter, setParameterValue){
	EXPECT_NO_THROW(paramManager.setValue("paramInt", intValue + 1));
	EXPECT_EQ(intValue + 1, paramInt.getValue());

	EXPECT_NO_THROW(paramManager.setValue("paramLong", longValue + 1));
	EXPECT_EQ(longValue + 1, paramLong.getValue());

	EXPECT_NO_THROW(paramManager.setValue("paramFloat", floatValue + 1));
	EXPECT_EQ(floatValue + 1, paramFloat.getValue());

	EXPECT_NO_THROW(paramManager.setValue("paramDouble", doubleValue + 1));
	EXPECT_EQ(doubleValue + 1, paramDouble.getValue());

	EXPECT_NO_THROW(paramManager.setValue("paramBool", !boolValue));
	EXPECT_FALSE(paramBool.getValue());

	EXPECT_NO_THROW(paramManager.setValue("paramString", stringValue + "new"));
	EXPECT_STREQ((stringValue + "new").c_str(), paramString.getValue().c_str());

	EXPECT_NO_THROW(paramManager.setValue("paramFile", ssf::FileHandle("test_file.txt")));
	EXPECT_STREQ(ssf::FileHandle("test_file.txt").getAbsoluteFileName().c_str(), paramFileHandle.getValue().getAbsoluteFileName().c_str());

	EXPECT_NO_THROW(paramManager.setValue("paramDirectory", ssf::DirectoryHandle("folder_test")));
	EXPECT_STREQ(ssf::DirectoryHandle("folder_test").getAbsolutePath().c_str(), paramDirectoryHandle.getValue().getAbsolutePath().c_str());

}

TEST_F(TestParameter, invalidSetParameterValue){
	EXPECT_ANY_THROW(paramManager.setValue("invalid_name", 0));
}