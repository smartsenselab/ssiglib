//#include <gtest/gtest.h>
//
//#include "core/parameter.hpp"
//#include "core/parameter_book.hpp"
//#include "core/parameter_info.hpp"
//
//class TestParameter : public ::testing::Test{
//protected:
//
//	virtual void SetUp(){
//		intValue = 99;
//		longValue = 99999;
//		floatValue = float(99.88);
//		doubleValue = 99999.88888888;
//		boolValue = true;
//		stringValue = "stringValue";
//		fileHandleValue = ssf::FileHandle("test_file.txt");
//		directoryHandleValue = ssf::DirectoryHandle("folder_test");
//
//		EXPECT_NO_THROW(paramBook.registerParameter(paramInt, "paramInt", "description_test_int", true, intValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramLong, "paramLong", "description_test_long", true, longValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramFloat, "paramFloat", "description_test_float", true, floatValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramDouble, "paramDouble", "description_test_double", true, doubleValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramBool, "paramBool", "description_test_bool", true, boolValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramString, "paramString", "description_test_string", true, stringValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramFileHandle, "paramFile", "description_test_file", true, fileHandleValue));
//		EXPECT_NO_THROW(paramBook.registerParameter(paramDirectoryHandle, "paramDirectory", "description_test_directory", true, directoryHandleValue));
//
//		EXPECT_NO_THROW(infoInt = ssf::ParameterInfo(paramInt));
//		EXPECT_NO_THROW(infoLong = ssf::ParameterInfo(paramLong));
//		EXPECT_NO_THROW(infoFloat = ssf::ParameterInfo(paramFloat));
//		EXPECT_NO_THROW(infoDouble = ssf::ParameterInfo(paramDouble));
//		EXPECT_NO_THROW(infoBool = ssf::ParameterInfo(paramBool));
//		EXPECT_NO_THROW(infoString = ssf::ParameterInfo(paramString));
//		EXPECT_NO_THROW(infoFileHandle = ssf::ParameterInfo(paramFileHandle));
//		EXPECT_NO_THROW(infoDirectoryHandle = ssf::ParameterInfo(paramDirectoryHandle));
//	}
//
//	int intValue;
//	long longValue;
//	float floatValue;
//	double doubleValue;
//	bool boolValue;
//	std::string stringValue;
//	ssf::FileHandle fileHandleValue;
//	ssf::DirectoryHandle directoryHandleValue;
//
//	ssf::Parameter<int> paramInt;
//	ssf::Parameter<long> paramLong;
//	ssf::Parameter<float> paramFloat;
//	ssf::Parameter<double> paramDouble;
//	ssf::Parameter<bool> paramBool;
//	ssf::Parameter<std::string> paramString;
//	ssf::Parameter<ssf::FileHandle> paramFileHandle;
//	ssf::Parameter<ssf::DirectoryHandle> paramDirectoryHandle;
//
//	ssf::ParameterInfo infoInt;
//	ssf::ParameterInfo infoLong;
//	ssf::ParameterInfo infoFloat;
//	ssf::ParameterInfo infoDouble;
//	ssf::ParameterInfo infoBool;
//	ssf::ParameterInfo infoString;
//	ssf::ParameterInfo infoFileHandle;
//	ssf::ParameterInfo infoDirectoryHandle;
//
//	ssf::ParameterBook paramBook;
//};
//
//
//TEST_F(TestParameter, invalidConstructor){
//	int a = 0;
//	EXPECT_ANY_THROW(ssf::Parameter<long long> testLongLong);
//}
//
//
//TEST_F(TestParameter, getValue){
//	EXPECT_NO_THROW(paramInt.getValue());
//	EXPECT_NO_THROW(paramLong.getValue());
//	EXPECT_NO_THROW(paramFloat.getValue());
//	EXPECT_NO_THROW(paramDouble.getValue());
//	EXPECT_NO_THROW(paramBool.getValue());
//	EXPECT_NO_THROW(paramString.getValue());
//	EXPECT_NO_THROW(paramFileHandle.getValue());
//	EXPECT_NO_THROW(paramDirectoryHandle.getValue());
//
//	EXPECT_EQ(intValue, paramInt.getValue());
//	EXPECT_EQ(longValue, paramLong.getValue());
//	EXPECT_EQ(floatValue, paramFloat.getValue());
//	EXPECT_EQ(doubleValue, paramDouble.getValue());
//	EXPECT_TRUE(paramBool.getValue());
//	EXPECT_STREQ(stringValue.c_str(), paramString.getValue().c_str());
//	EXPECT_STREQ(fileHandleValue.getAbsoluteFileName().c_str(), paramFileHandle.getValue().getAbsoluteFileName().c_str());
//	EXPECT_STREQ(directoryHandleValue.getAbsolutePath().c_str(), paramDirectoryHandle.getValue().getAbsolutePath().c_str());
//}
//
//TEST_F(TestParameter, getType){
//	EXPECT_EQ(ssf::ParameterType::INT, paramInt.getType());
//	EXPECT_EQ(ssf::ParameterType::LONG, paramLong.getType());
//	EXPECT_EQ(ssf::ParameterType::FLOAT, paramFloat.getType());
//	EXPECT_EQ(ssf::ParameterType::DOUBLE, paramDouble.getType());
//	EXPECT_EQ(ssf::ParameterType::BOOL, paramBool.getType());
//	EXPECT_EQ(ssf::ParameterType::STRING, paramString.getType());
//	EXPECT_EQ(ssf::ParameterType::FILE_HANDLE, paramFileHandle.getType());
//	EXPECT_EQ(ssf::ParameterType::DIRECTORY_HANDLE, paramDirectoryHandle.getType());
//}
//
//TEST_F(TestParameter, getName){
//	EXPECT_NO_THROW(paramInt.getName());
//	EXPECT_NO_THROW(paramLong.getName());
//	EXPECT_NO_THROW(paramFloat.getName());
//	EXPECT_NO_THROW(paramDouble.getName());
//	EXPECT_NO_THROW(paramBool.getName());
//	EXPECT_NO_THROW(paramString.getName());
//	EXPECT_NO_THROW(paramFileHandle.getName());
//	EXPECT_NO_THROW(paramDirectoryHandle.getName());
//
//	EXPECT_STREQ("paramInt", paramInt.getName().c_str());
//	EXPECT_STREQ("paramLong", paramLong.getName().c_str());
//	EXPECT_STREQ("paramFloat", paramFloat.getName().c_str());
//	EXPECT_STREQ("paramDouble", paramDouble.getName().c_str());
//	EXPECT_STREQ("paramBool", paramBool.getName().c_str());
//	EXPECT_STREQ("paramString", paramString.getName().c_str());
//	EXPECT_STREQ("paramFile", paramFileHandle.getName().c_str());
//	EXPECT_STREQ("paramDirectory", paramDirectoryHandle.getName().c_str());
//}
//
//
//
//TEST_F(TestParameter, invalidRegisterParameter){
//	//Parameter already registered
//	EXPECT_ANY_THROW(paramBook.registerParameter(paramInt, "otherName", "description_test_int", true, 0));
//	//Parameter name already exists
//	EXPECT_ANY_THROW(paramBook.registerParameter(paramDouble, "paramInt", "description_test_double", true, 0.0));
//}
//
//TEST_F(TestParameter, setParameterValue){
//	EXPECT_NO_THROW(paramBook.setValue("paramInt", intValue + 1));
//	EXPECT_EQ(intValue + 1, paramInt.getValue());
//	EXPECT_NO_THROW(paramBook.setValue("paramInt", intValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramLong", longValue + 1));
//	EXPECT_EQ(longValue + 1, paramLong.getValue());
//	EXPECT_NO_THROW(paramBook.setValue("paramLong", longValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramFloat", floatValue + 1));
//	EXPECT_EQ(floatValue + 1, paramFloat.getValue());
//	EXPECT_NO_THROW(paramBook.setValue("paramFloat", floatValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramDouble", doubleValue + 1));
//	EXPECT_EQ(doubleValue + 1, paramDouble.getValue());
//	EXPECT_NO_THROW(paramBook.setValue("paramDouble", doubleValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramBool", !boolValue));
//	EXPECT_FALSE(paramBool.getValue());
//	EXPECT_NO_THROW(paramBook.setValue("paramBool", boolValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramString", stringValue + "new"));
//	EXPECT_STREQ((stringValue + "new").c_str(), paramString.getValue().c_str());
//	EXPECT_NO_THROW(paramBook.setValue("paramString", stringValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramFile", ssf::FileHandle("test_file.txt")));
//	EXPECT_STREQ(ssf::FileHandle("test_file.txt").getAbsoluteFileName().c_str(), paramFileHandle.getValue().getAbsoluteFileName().c_str());
//	EXPECT_NO_THROW(paramBook.setValue("paramFile", fileHandleValue));
//
//	EXPECT_NO_THROW(paramBook.setValue("paramDirectory", ssf::DirectoryHandle("folder_test")));
//	EXPECT_STREQ(ssf::DirectoryHandle("folder_test").getAbsolutePath().c_str(), paramDirectoryHandle.getValue().getAbsolutePath().c_str());
//	EXPECT_NO_THROW(paramBook.setValue("paramDirectory", directoryHandleValue));
//
//}
//
//TEST_F(TestParameter, invalidSetParameterValue){
//	EXPECT_ANY_THROW(paramBook.setValue("invalid_name", 0));
//}
//
//TEST_F(TestParameter, parameterInfo){
//	EXPECT_NO_THROW(infoInt.getDefaultValue<int>());
//	EXPECT_NO_THROW(infoLong.getDefaultValue<long>());
//	EXPECT_NO_THROW(infoFloat.getDefaultValue<float>());
//	EXPECT_NO_THROW(infoDouble.getDefaultValue<double>());
//	EXPECT_NO_THROW(infoBool.getDefaultValue<bool>());
//	EXPECT_NO_THROW(infoString.getDefaultValue<std::string>());
//	EXPECT_NO_THROW(infoFileHandle.getDefaultValue<ssf::FileHandle>());
//	EXPECT_NO_THROW(infoDirectoryHandle.getDefaultValue<ssf::DirectoryHandle>());
//
//	EXPECT_ANY_THROW(infoLong.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoFloat.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoDouble.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoBool.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoString.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoFileHandle.getDefaultValue<int>());
//	EXPECT_ANY_THROW(infoDirectoryHandle.getDefaultValue<int>());
//
//	EXPECT_EQ(intValue, infoInt.getDefaultValue<int>());
//	EXPECT_EQ(longValue, infoLong.getDefaultValue<long>());
//	EXPECT_EQ(floatValue, infoFloat.getDefaultValue<float>());
//	EXPECT_EQ(doubleValue, infoDouble.getDefaultValue<double>());
//	EXPECT_TRUE(infoBool.getDefaultValue<bool>());
//	EXPECT_STREQ(stringValue.c_str(), infoString.getDefaultValue<std::string>().c_str());
//	EXPECT_STREQ(fileHandleValue.getAbsoluteFileName().c_str(), infoFileHandle.getDefaultValue<ssf::FileHandle>().getAbsoluteFileName().c_str());
//	EXPECT_STREQ(directoryHandleValue.getAbsolutePath().c_str(), infoDirectoryHandle.getDefaultValue<ssf::DirectoryHandle>().getAbsolutePath().c_str());
//
//	EXPECT_STREQ("paramInt", infoInt.getName().c_str());
//	EXPECT_STREQ("paramLong", infoLong.getName().c_str());
//	EXPECT_STREQ("paramFloat", infoFloat.getName().c_str());
//	EXPECT_STREQ("paramDouble", infoDouble.getName().c_str());
//	EXPECT_STREQ("paramBool", infoBool.getName().c_str());
//	EXPECT_STREQ("paramString", infoString.getName().c_str());
//	EXPECT_STREQ("paramFile", infoFileHandle.getName().c_str());
//	EXPECT_STREQ("paramDirectory", infoDirectoryHandle.getName().c_str());
//}