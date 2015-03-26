#include <gtest/gtest.h>

#include "core/param.hpp"

class TestParam : public ::testing::Test{
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

		EXPECT_NO_THROW(paramInt = ssf::Param(ssf::ParamType::INT, "paramInt", "description_test_int"));
		EXPECT_NO_THROW(paramLong = ssf::Param(ssf::ParamType::LONG, "paramLong", "description_test_long"));
		EXPECT_NO_THROW(paramFloat = ssf::Param(ssf::ParamType::FLOAT, "paramFloat", "description_test_float"));
		EXPECT_NO_THROW(paramDouble = ssf::Param(ssf::ParamType::DOUBLE, "paramDouble", "description_test_double"));
		EXPECT_NO_THROW(paramBool = ssf::Param(ssf::ParamType::BOOL, "paramBool", "description_test_bool"));
		EXPECT_NO_THROW(paramString = ssf::Param(ssf::ParamType::STRING, "paramString", "description_test_string"));
		EXPECT_NO_THROW(paramFile = ssf::Param(ssf::ParamType::FILE_HANDLE, "paramFile", "description_test_file"));
		EXPECT_NO_THROW(paramDirectory = ssf::Param(ssf::ParamType::DIRECTORY_HANDLE, "paramDirectory", "description_test_directory"));
	}

	int intValue;
	long longValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;

	ssf::Param paramInt;
	ssf::Param paramLong;
	ssf::Param paramFloat;
	ssf::Param paramDouble;
	ssf::Param paramBool;
	ssf::Param paramString;
	ssf::Param paramFile;
	ssf::Param paramDirectory;

};


TEST_F(TestParam, getType){
	EXPECT_EQ(ssf::ParamType::INT, paramInt.getType());
	EXPECT_EQ(ssf::ParamType::LONG, paramLong.getType());
	EXPECT_EQ(ssf::ParamType::FLOAT, paramFloat.getType());
	EXPECT_EQ(ssf::ParamType::DOUBLE, paramDouble.getType());
	EXPECT_EQ(ssf::ParamType::BOOL, paramBool.getType());
	EXPECT_EQ(ssf::ParamType::STRING, paramString.getType());
	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, paramFile.getType());
	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, paramDirectory.getType());
}

TEST_F(TestParam, getName){
	EXPECT_STREQ("paramInt", paramInt.getName().c_str());
	EXPECT_STREQ("paramLong", paramLong.getName().c_str());
	EXPECT_STREQ("paramFloat", paramFloat.getName().c_str());
	EXPECT_STREQ("paramDouble", paramDouble.getName().c_str());
	EXPECT_STREQ("paramBool", paramBool.getName().c_str());
	EXPECT_STREQ("paramString", paramString.getName().c_str());
	EXPECT_STREQ("paramFile", paramFile.getName().c_str());
	EXPECT_STREQ("paramDirectory", paramDirectory.getName().c_str());
}

TEST_F(TestParam, getDescription){
	EXPECT_STREQ("description_test_int", paramInt.getDescription().c_str());
	EXPECT_STREQ("description_test_long", paramLong.getDescription().c_str());
	EXPECT_STREQ("description_test_float", paramFloat.getDescription().c_str());
	EXPECT_STREQ("description_test_double", paramDouble.getDescription().c_str());
	EXPECT_STREQ("description_test_bool", paramBool.getDescription().c_str());
	EXPECT_STREQ("description_test_string", paramString.getDescription().c_str());
	EXPECT_STREQ("description_test_file", paramFile.getDescription().c_str());
	EXPECT_STREQ("description_test_directory", paramDirectory.getDescription().c_str());
}

TEST_F(TestParam, required){
	EXPECT_FALSE(paramInt.isRequired());
	EXPECT_NO_THROW(paramInt.setRequired(true));
	EXPECT_TRUE(paramInt.isRequired());
}

TEST_F(TestParam, irregularValues){

	EXPECT_NO_THROW(paramInt.setValue(std::numeric_limits<int>::max()));
	EXPECT_EQ(std::numeric_limits<int>::max(), paramInt.getValue<int>());

	EXPECT_NO_THROW(paramInt.setValue(std::numeric_limits<long>::max()));
	EXPECT_EQ(static_cast<int>(std::numeric_limits<long>::max()), paramInt.getValue<long>());
	EXPECT_TRUE(paramInt.getValue<bool>());

	EXPECT_NO_THROW(paramInt.setValue(true));
	EXPECT_EQ(1, paramInt.getValue<int>());

	EXPECT_NO_THROW(paramInt.setValue(false));
	EXPECT_EQ(0, paramInt.getValue<int>());

	EXPECT_NO_THROW(paramBool.setValue(std::numeric_limits<int>::max()));
	EXPECT_TRUE(paramBool.getValue<bool>());
	EXPECT_EQ(1, paramBool.getValue<int>());

	EXPECT_NO_THROW(paramBool.setValue(0));
	EXPECT_FALSE(paramBool.getValue<bool>());


	
	EXPECT_ANY_THROW(paramInt.setValue("invalid"));
	EXPECT_ANY_THROW(paramBool.setValue("invalid"));
	EXPECT_ANY_THROW(paramString.setValue(0));
	EXPECT_ANY_THROW(paramFile.setValue(directoryHandleValue));
	EXPECT_ANY_THROW(paramDirectory.setValue(fileHandleValue));
	
}

TEST_F(TestParam, regularValues){

	EXPECT_NO_THROW(paramInt.setValue(intValue));
	EXPECT_EQ(intValue, paramInt.getValue<int>());

	EXPECT_NO_THROW(paramLong.setValue(longValue));
	EXPECT_EQ(longValue, paramLong.getValue<long>());
	
	EXPECT_NO_THROW(paramFloat.setValue(floatValue));
	EXPECT_FLOAT_EQ(floatValue, paramFloat.getValue<float>());

	EXPECT_NO_THROW(paramDouble.setValue(doubleValue));
	EXPECT_DOUBLE_EQ(doubleValue, paramDouble.getValue<double>());

	EXPECT_NO_THROW(paramBool.setValue(boolValue));
	EXPECT_TRUE(paramBool.getValue<bool>());
	
	EXPECT_NO_THROW(paramString.setValue(stringValue));
	EXPECT_STREQ(stringValue.c_str(), paramString.getValue<std::string>().c_str());

	EXPECT_NO_THROW(paramFile.setValue(fileHandleValue));
	EXPECT_STREQ(fileHandleValue.getAbsoluteFileName().c_str(), paramFile.getValue<ssf::FileHandle>().getAbsoluteFileName().c_str());

	EXPECT_NO_THROW(paramDirectory.setValue(directoryHandleValue));
	EXPECT_STREQ(directoryHandleValue.getAbsolutePath().c_str(), paramDirectory.getValue<ssf::DirectoryHandle>().getAbsolutePath().c_str());
}