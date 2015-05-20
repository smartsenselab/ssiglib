#include <gtest/gtest.h>

#include "core/parameters.hpp"


class TestParams : public ::testing::Test{
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

		EXPECT_NO_THROW(parameters.addParameter("paramInteger", "description_test_integer", ssf::ParamType::INTEGER));
		EXPECT_NO_THROW(parameters.addParameter("paramReal", "description_test_real", ssf::ParamType::REAL));
		EXPECT_NO_THROW(parameters.addParameter("paramBool", "description_test_bool", ssf::ParamType::BOOL));
		EXPECT_NO_THROW(parameters.addParameter("paramString", "description_test_string", ssf::ParamType::STRING));
		EXPECT_NO_THROW(parameters.addParameter("paramFile", "description_test_file", ssf::ParamType::FILE_HANDLE));
		EXPECT_NO_THROW(parameters.addParameter("paramDirectory", "description_test_directory", ssf::ParamType::DIRECTORY_HANDLE));
	}

	int intValue;
	long longValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;

	ssf::Parameters parameters;
};

TEST_F(TestParams, getType){
	EXPECT_EQ(ssf::ParamType::INTEGER, parameters["paramInteger"].getType());
	EXPECT_EQ(ssf::ParamType::REAL, parameters["paramReal"].getType());
	EXPECT_EQ(ssf::ParamType::BOOL, parameters["paramBool"].getType());
	EXPECT_EQ(ssf::ParamType::STRING, parameters["paramString"].getType());
	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, parameters["paramFile"].getType());
	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, parameters["paramDirectory"].getType());
	EXPECT_ANY_THROW(parameters["invalid_name"].getType());
}

TEST_F(TestParams, getName){
	EXPECT_STREQ("paramInteger", parameters["paramInteger"].getName().c_str());
	EXPECT_STREQ("paramReal", parameters["paramReal"].getName().c_str());
	EXPECT_STREQ("paramBool", parameters["paramBool"].getName().c_str());
	EXPECT_STREQ("paramString", parameters["paramString"].getName().c_str());
	EXPECT_STREQ("paramFile", parameters["paramFile"].getName().c_str());
	EXPECT_STREQ("paramDirectory", parameters["paramDirectory"].getName().c_str());
	EXPECT_ANY_THROW(parameters["invalid_name"].getName());
}

TEST_F(TestParams, getDescription){
	EXPECT_STREQ("description_test_integer", parameters["paramInteger"].getDescription().c_str());
	EXPECT_STREQ("description_test_real", parameters["paramReal"].getDescription().c_str());
	EXPECT_STREQ("description_test_bool", parameters["paramBool"].getDescription().c_str());
	EXPECT_STREQ("description_test_string", parameters["paramString"].getDescription().c_str());
	EXPECT_STREQ("description_test_file", parameters["paramFile"].getDescription().c_str());
	EXPECT_STREQ("description_test_directory", parameters["paramDirectory"].getDescription().c_str());
	EXPECT_ANY_THROW(parameters["invalid_name"].getDescription());
}

TEST_F(TestParams, required){
	EXPECT_FALSE(parameters["paramInteger"].isRequired());
	EXPECT_NO_THROW(parameters["paramInteger"].setRequired(true));
	EXPECT_TRUE(parameters["paramInteger"].isRequired());
	EXPECT_ANY_THROW(parameters["invalid_name"].isRequired());
	EXPECT_ANY_THROW(parameters["invalid_name"].setRequired(false));
}

TEST(Parameters, readFromFile){
	ssf::Parameters paramFromFile("parameters.yml");

	EXPECT_EQ(10, paramFromFile["paramInteger"].toInt());
	EXPECT_EQ(2.2, paramFromFile["paramReal"].toDouble());
	EXPECT_STREQ("test_string", paramFromFile["paramString"].toString().c_str());
	EXPECT_TRUE(paramFromFile["paramInteger"].toBool());

}