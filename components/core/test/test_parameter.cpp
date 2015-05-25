//#include <gtest/gtest.h>
//
//#include "core/parameter.hpp"
//#include <limits>
//
//TEST(Parameter, INTEGER){
//	ssf::Parameter p("test", "description");
//
//	int intValue;
//	long long longLongValue;
//	unsigned int unsignedValue;
//	float floatValue;
//	std::string stringValue;
//	
//	intValue = std::numeric_limits<int>::max();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::max(), p.toInt());
//
//	intValue = std::numeric_limits<int>::min();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::min(), p.toInt());
//
//	intValue = 0;
//	p.setValue(intValue);
//	EXPECT_EQ(0, p.toInt());
//
//	unsignedValue = std::numeric_limits<unsigned int>::max();
//	p.setValue(unsignedValue);
//	EXPECT_EQ(std::numeric_limits<unsigned int>::max(), p.toUnsignedInt());
//
//	unsignedValue = std::numeric_limits<unsigned int>::max();
//	p.setValue(unsignedValue);
//	EXPECT_ANY_THROW(p.toInt());
//
//	intValue = std::numeric_limits<int>::min();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::min(), p.toInt());
//
//	intValue = 0;
//	p.setValue(intValue);
//	EXPECT_EQ(0, p.toInt());
//
//	longLongValue = std::numeric_limits<int>::max();
//	p.setValue(longLongValue);
//	EXPECT_EQ(std::numeric_limits<int>::max(), p.toInt());
//
//	longLongValue = std::numeric_limits<long long>::max();
//	p.setValue(longLongValue);
//	EXPECT_ANY_THROW(p.toInt());
//
//	floatValue = 10.5;
//	p.setValue(floatValue);
//	EXPECT_EQ(10, p.toInt());
//
//	stringValue = "101";
//	p.setValue(stringValue);
//	EXPECT_EQ(101, p.toInt());
//
//	p.setValue("101");
//	EXPECT_EQ(101, p.toInt());
//
//	p.setValue("10.99");
//	EXPECT_EQ(10, p.toInt());
//
//}
//
//
//TEST(Parameter, REAL){
//	ssf::Parameter p("test", "description");
//
//	int intValue;
//	long long longLongValue;
//	unsigned int unsignedValue;
//	float floatValue;
//	std::string stringValue;
//
//	intValue = std::numeric_limits<int>::max();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::max(), p.toInt());
//
//	intValue = std::numeric_limits<int>::min();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::min(), p.toInt());
//
//	intValue = 0;
//	p.setValue(intValue);
//	EXPECT_EQ(0, p.toInt());
//
//	unsignedValue = std::numeric_limits<unsigned int>::max();
//	p.setValue(unsignedValue);
//	EXPECT_EQ(std::numeric_limits<unsigned int>::max(), p.toUnsignedInt());
//
//	unsignedValue = std::numeric_limits<unsigned int>::max();
//	p.setValue(unsignedValue);
//	EXPECT_ANY_THROW(p.toInt());
//
//	intValue = std::numeric_limits<int>::min();
//	p.setValue(intValue);
//	EXPECT_EQ(std::numeric_limits<int>::min(), p.toInt());
//
//	intValue = 0;
//	p.setValue(intValue);
//	EXPECT_EQ(0, p.toInt());
//
//	longLongValue = std::numeric_limits<int>::max();
//	p.setValue(longLongValue);
//	EXPECT_EQ(std::numeric_limits<int>::max(), p.toInt());
//
//	longLongValue = std::numeric_limits<long long>::max();
//	p.setValue(longLongValue);
//	EXPECT_ANY_THROW(p.toInt());
//
//	floatValue = 10.5;
//	p.setValue(floatValue);
//	EXPECT_EQ(10, p.toInt());
//
//	stringValue = "101";
//	p.setValue(stringValue);
//	EXPECT_EQ(101, p.toInt());
//
//	p.setValue("101");
//	EXPECT_EQ(101, p.toInt());
//
//	p.setValue("10.99");
//	EXPECT_EQ(10, p.toInt());
//
//}
//
//
////
////class TestParams : public ::testing::Test{
////protected:
////
////	virtual void SetUp(){
////		intValue = 99;
////		longValue = 99999;
////		floatValue = float(99.88);
////		doubleValue = 99999.88888888;
////		boolValue = true;
////		stringValue = "stringValue";
////		fileHandleValue = ssf::FileHandle("test_file.txt");
////		directoryHandleValue = ssf::DirectoryHandle("folder_test");
////
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::INT, "paramInt", "description_test_int"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::LONG, "paramLong", "description_test_long"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::FLOAT, "paramFloat", "description_test_float"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::DOUBLE, "paramDouble", "description_test_double"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::BOOL, "paramBool", "description_test_bool"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::STRING, "paramString", "description_test_string"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::FILE_HANDLE, "paramFile", "description_test_file"));
////		EXPECT_NO_THROW(parameters.addParameter(ssf::ParamType::DIRECTORY_HANDLE, "paramDirectory", "description_test_directory"));
////	}
////
////	int intValue;
////	long longValue;
////	float floatValue;
////	double doubleValue;
////	bool boolValue;
////	std::string stringValue;
////	ssf::FileHandle fileHandleValue;
////	ssf::DirectoryHandle directoryHandleValue;
////
////
////	ssf::Parameters parameters;
////};
////
////TEST_F(TestParams, getType){
////	EXPECT_EQ(ssf::ParamType::INT, parameters.getType("paramInt"));
////	EXPECT_EQ(ssf::ParamType::LONG, parameters.getType("paramLong"));
////	EXPECT_EQ(ssf::ParamType::FLOAT, parameters.getType("paramFloat"));
////	EXPECT_EQ(ssf::ParamType::DOUBLE, parameters.getType("paramDouble"));
////	EXPECT_EQ(ssf::ParamType::BOOL, parameters.getType("paramBool"));
////	EXPECT_EQ(ssf::ParamType::STRING, parameters.getType("paramString"));
////	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, parameters.getType("paramFile"));
////	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, parameters.getType("paramDirectory"));
////	EXPECT_ANY_THROW(parameters.getType("invalid_name"));
////}
////
////TEST_F(TestParams, getName){
////	EXPECT_STREQ("paramInt", parameters.getName("paramInt").c_str());
////	EXPECT_STREQ("paramLong", parameters.getName("paramLong").c_str());
////	EXPECT_STREQ("paramFloat", parameters.getName("paramFloat").c_str());
////	EXPECT_STREQ("paramDouble", parameters.getName("paramDouble").c_str());
////	EXPECT_STREQ("paramBool", parameters.getName("paramBool").c_str());
////	EXPECT_STREQ("paramString", parameters.getName("paramString").c_str());
////	EXPECT_STREQ("paramFile", parameters.getName("paramFile").c_str());
////	EXPECT_STREQ("paramDirectory", parameters.getName("paramDirectory").c_str());
////	EXPECT_ANY_THROW(parameters.getName("invalid_name").c_str());
////}
////
////TEST_F(TestParams, getDescription){
////	EXPECT_STREQ("description_test_int", parameters.getDescription("paramInt").c_str());
////	EXPECT_STREQ("description_test_long", parameters.getDescription("paramLong").c_str());
////	EXPECT_STREQ("description_test_float", parameters.getDescription("paramFloat").c_str());
////	EXPECT_STREQ("description_test_double", parameters.getDescription("paramDouble").c_str());
////	EXPECT_STREQ("description_test_bool", parameters.getDescription("paramBool").c_str());
////	EXPECT_STREQ("description_test_string", parameters.getDescription("paramString").c_str());
////	EXPECT_STREQ("description_test_file", parameters.getDescription("paramFile").c_str());
////	EXPECT_STREQ("description_test_directory", parameters.getDescription("paramDirectory").c_str());
////	EXPECT_ANY_THROW(parameters.getDescription("invalid_name").c_str());
////}
////
////TEST_F(TestParams, required){
////	EXPECT_FALSE(parameters.isRequired("paramInt"));
////	EXPECT_NO_THROW(parameters.setRequired("paramInt", true));
////	EXPECT_TRUE(parameters.isRequired("paramInt"));
////	EXPECT_ANY_THROW(parameters.isRequired("invalid_name"));
////	EXPECT_ANY_THROW(parameters.setRequired("invalid_name", false));
////}
////
////TEST_F(TestParams, irregularValues){
////
////	EXPECT_NO_THROW(parameters.setValue("paramInt", std::numeric_limits<int>::max()));
////	EXPECT_EQ(std::numeric_limits<int>::max(), parameters.getValue<int>("paramInt"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramInt", std::numeric_limits<long>::max()));
////	EXPECT_EQ(static_cast<int>(std::numeric_limits<long>::max()), parameters.getValue<long>("paramInt"));
////	EXPECT_TRUE(parameters.getValue<bool>("paramInt"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramInt",true));
////	EXPECT_EQ(1, parameters.getValue<int>("paramInt"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramInt", false));
////	EXPECT_EQ(0, parameters.getValue<int>("paramInt"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramBool", std::numeric_limits<int>::max()));
////	EXPECT_TRUE(parameters.getValue<bool>("paramBool"));
////	EXPECT_EQ(1, parameters.getValue<int>("paramBool"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramBool", 0));
////	EXPECT_FALSE(parameters.getValue<bool>("paramBool"));
////
////
////	
////	EXPECT_ANY_THROW(parameters.setValue("paramInt", "invalid"));
////	EXPECT_ANY_THROW(parameters.setValue("paramBool", "invalid"));
////	EXPECT_ANY_THROW(parameters.setValue("paramString", 0));
////	EXPECT_ANY_THROW(parameters.setValue("paramFile", directoryHandleValue));
////	EXPECT_ANY_THROW(parameters.setValue("paramDirectory", fileHandleValue));
////
////}
////
////TEST_F(TestParams, regularValues){
////
////	EXPECT_NO_THROW(parameters.setValue("paramInt", intValue));
////	EXPECT_EQ(intValue, parameters.getValue<int>("paramInt"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramLong", longValue));
////	EXPECT_EQ(longValue, parameters.getValue<long>("paramLong"));
////	
////	EXPECT_NO_THROW(parameters.setValue("paramFloat", floatValue));
////	EXPECT_FLOAT_EQ(floatValue, parameters.getValue<float>("paramFloat"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramDouble", doubleValue));
////	EXPECT_DOUBLE_EQ(doubleValue, parameters.getValue<double>("paramDouble"));
////
////	EXPECT_NO_THROW(parameters.setValue("paramBool", boolValue));
////	EXPECT_TRUE(parameters.getValue<bool>("paramBool"));
////	
////	EXPECT_NO_THROW(parameters.setValue("paramString", stringValue));
////	EXPECT_STREQ(stringValue.c_str(), parameters.getValue<std::string>("paramString").c_str());
////
////	EXPECT_NO_THROW(parameters.setValue("paramFile", fileHandleValue));
////	EXPECT_STREQ(fileHandleValue.getAbsoluteFileName().c_str(), parameters.getValue<ssf::FileHandle>("paramFile").getAbsoluteFileName().c_str());
////
////	EXPECT_NO_THROW(parameters.setValue("paramDirectory", directoryHandleValue));
////	EXPECT_STREQ(directoryHandleValue.getAbsolutePath().c_str(), parameters.getValue<ssf::DirectoryHandle>("paramDirectory").getAbsolutePath().c_str());
////}