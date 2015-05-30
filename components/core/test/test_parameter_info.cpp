/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#include <gtest/gtest.h>

#include <map>

#include "core/parameter_info.hpp"

class TestParameterInfo : public ::testing::Test{
public:

	virtual void SetUp(){

		intValue = 99;
		doubleValue = 99.9;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");
		intVectorValue = std::vector < int > {10, 11, 12};
		doubleVectorValue = std::vector < double > {1000, 1100.1, 1200.2};
		stringVectorValue = std::vector < std::string > {"a", "b", "c"};

		paramIntInfo = ssf::ParameterInfo(ssf::Parameter("paramInt", intValue, "description_test_int"));
		paramDoubleInfo = ssf::ParameterInfo(ssf::Parameter("paramDouble", doubleValue, "description_test_double"));
		paramBoolInfo = ssf::ParameterInfo(ssf::Parameter("paramBool", boolValue, "description_test_bool"));
		paramStringInfo = ssf::ParameterInfo(ssf::Parameter("paramString", stringValue, "description_test_string"));
		paramFileHandleInfo = ssf::ParameterInfo(ssf::Parameter("paramFileHandle", fileHandleValue, "description_test_file"));
		paramDirectoryHandleInfo = ssf::ParameterInfo(ssf::Parameter("paramDirectoryHandle", directoryHandleValue, "description_test_directory"));
		paramIntVectorInfo = ssf::ParameterInfo(ssf::Parameter("paramIntVector", intVectorValue, "description_test_intVector"));
		paramDoubleVectorInfo = ssf::ParameterInfo(ssf::Parameter("paramDoubleVector", doubleVectorValue, "description_test_doubleVector"));
		paramStringVectorInfo = ssf::ParameterInfo(ssf::Parameter("paramStringVector", stringVectorValue, "description_test_stringVector"));
	}

	int intValue;
	double doubleValue;
	bool boolValue;
	std::string stringValue;
	ssf::FileHandle fileHandleValue;
	ssf::DirectoryHandle directoryHandleValue;
	std::vector<int> intVectorValue;
	std::vector<double> doubleVectorValue;
	std::vector<std::string> stringVectorValue;

	ssf::ParameterInfo paramIntInfo;
	ssf::ParameterInfo paramDoubleInfo;
	ssf::ParameterInfo paramBoolInfo;
	ssf::ParameterInfo paramStringInfo;
	ssf::ParameterInfo paramFileHandleInfo;
	ssf::ParameterInfo paramDirectoryHandleInfo;
	ssf::ParameterInfo paramIntVectorInfo;
	ssf::ParameterInfo paramDoubleVectorInfo;
	ssf::ParameterInfo paramStringVectorInfo;

};

TEST_F(TestParameterInfo, name){
	EXPECT_EQ("paramInt", paramIntInfo.name());
	EXPECT_EQ("paramDouble", paramDoubleInfo.name());
	EXPECT_EQ("paramBool", paramBoolInfo.name());
	EXPECT_EQ("paramString", paramStringInfo.name());
	EXPECT_EQ("paramFileHandle", paramFileHandleInfo.name());
	EXPECT_EQ("paramDirectoryHandle", paramDirectoryHandleInfo.name());
	EXPECT_EQ("paramIntVector", paramIntVectorInfo.name());
	EXPECT_EQ("paramDoubleVector", paramDoubleVectorInfo.name());
	EXPECT_EQ("paramStringVector", paramStringVectorInfo.name());
}

TEST_F(TestParameterInfo, description){
	EXPECT_EQ("description_test_int", paramIntInfo.description());
	EXPECT_EQ("description_test_double", paramDoubleInfo.description());
	EXPECT_EQ("description_test_bool", paramBoolInfo.description());
	EXPECT_EQ("description_test_string", paramStringInfo.description());
	EXPECT_EQ("description_test_file", paramFileHandleInfo.description());
	EXPECT_EQ("description_test_directory", paramDirectoryHandleInfo.description());
	EXPECT_EQ("description_test_intVector", paramIntVectorInfo.description());
	EXPECT_EQ("description_test_doubleVector", paramDoubleVectorInfo.description());
	EXPECT_EQ("description_test_stringVector", paramStringVectorInfo.description());
}

TEST_F(TestParameterInfo, getType){
	EXPECT_EQ(ssf::ParamType::INT, paramIntInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE, paramDoubleInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::BOOL, paramBoolInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::STRING, paramStringInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, paramFileHandleInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, paramDirectoryHandleInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::INT_VECTOR, paramIntVectorInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE_VECTOR, paramDoubleVectorInfo.expectedType());
	EXPECT_EQ(ssf::ParamType::STRING_VECTOR, paramStringVectorInfo.expectedType());
	
}

TEST_F(TestParameterInfo, isRequired){
	EXPECT_FALSE(paramIntInfo.isRequired());
	EXPECT_FALSE(paramDoubleInfo.isRequired());
	EXPECT_FALSE(paramBoolInfo.isRequired());
	EXPECT_FALSE(paramStringInfo.isRequired());
	EXPECT_FALSE(paramFileHandleInfo.isRequired());
	EXPECT_FALSE(paramDirectoryHandleInfo.isRequired());
	EXPECT_FALSE(paramIntVectorInfo.isRequired());
	EXPECT_FALSE(paramDoubleVectorInfo.isRequired());
	EXPECT_FALSE(paramStringVectorInfo.isRequired());

}

TEST_F(TestParameterInfo, testCopy){
	ssf::ParameterInfo copyParameter(paramIntInfo);
	EXPECT_EQ("paramInt", copyParameter.name());
	EXPECT_EQ("description_test_int", copyParameter.description());
	EXPECT_EQ(ssf::ParamType::INT, copyParameter.expectedType());
	EXPECT_FALSE(copyParameter.isRequired());

	ssf::ParameterInfo lhsParameter = paramIntInfo;
	EXPECT_EQ("paramInt", lhsParameter.name());
	EXPECT_EQ("description_test_int", lhsParameter.description());
	EXPECT_EQ(ssf::ParamType::INT, lhsParameter.expectedType());
	EXPECT_FALSE(lhsParameter.isRequired());
}

TEST_F(TestParameterInfo, defaultValue){

	EXPECT_EQ("99", paramIntInfo.defaultValue());
	EXPECT_EQ("99.900000", paramDoubleInfo.defaultValue());
	EXPECT_EQ("true", paramBoolInfo.defaultValue());
	EXPECT_EQ("stringValue", paramStringInfo.defaultValue());
	EXPECT_EQ(ssf::FileHandle("test_file.txt").absolutePath(), paramFileHandleInfo.defaultValue());
	EXPECT_EQ(ssf::DirectoryHandle("folder_test").absolutePath(), paramDirectoryHandleInfo.defaultValue());
	EXPECT_EQ("10, 11, 12", paramIntVectorInfo.defaultValue());
	EXPECT_EQ("1000.000000, 1100.100000, 1200.200000", paramDoubleVectorInfo.defaultValue());
	EXPECT_EQ("a, b, c", paramStringVectorInfo.defaultValue());

}