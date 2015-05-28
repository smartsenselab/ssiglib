/*L*****************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install,
*  copy or use the software.
*
*                              License Agreement
*                      For Smart Surveillance Framework
*                        http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, 
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright 
*       notice, this list of conditions and the following disclaimer in the 
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its 
*       contributors may be used to endorse or promote products derived from 
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
*  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#include <gtest/gtest.h>

#include "core/parameters.hpp"


class TestParameters : public ::testing::Test{
protected:

	virtual void SetUp(){

		intValue = 99;
		doubleValue = 99999.88888888;
		boolValue = true;
		stringValue = "stringValue";
		fileHandleValue = ssf::FileHandle("test_file.txt");
		directoryHandleValue = ssf::DirectoryHandle("folder_test");
		intVectorValue = std::vector < int > {10, 11, 12};
		doubleVectorValue = std::vector < double > {1000, 1100.1, 1200.2};
		stringVectorValue = std::vector < std::string > {"a", "b", "c"};

		EXPECT_NO_THROW(parameters.addParameter("paramInt", intValue, "description_test_int"));
		EXPECT_NO_THROW(parameters.addParameter("paramDouble", doubleValue, "description_test_double"));
		EXPECT_NO_THROW(parameters.addParameter("paramBool", boolValue, "description_test_bool"));
		EXPECT_NO_THROW(parameters.addParameter("paramString", stringValue, "description_test_string"));
		EXPECT_NO_THROW(parameters.addParameter("paramFileHandle", fileHandleValue, "description_test_file"));
		EXPECT_NO_THROW(parameters.addParameter("paramDirectoryHandle", directoryHandleValue, "description_test_directory"));
		EXPECT_NO_THROW(parameters.addParameter("paramIntVector", intVectorValue, "description_test_intVector"));
		EXPECT_NO_THROW(parameters.addParameter("paramDoubleVector", doubleVectorValue, "description_test_doubleVector"));
		EXPECT_NO_THROW(parameters.addParameter("paramStringVector", stringVectorValue, "description_test_stringVector"));

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

	ssf::Parameters parameters;
};


TEST_F(TestParameters, getName){
	EXPECT_EQ("paramInt", parameters["paramInt"].getName());
	EXPECT_EQ("paramDouble", parameters["paramDouble"].getName());
	EXPECT_EQ("paramBool", parameters["paramBool"].getName());
	EXPECT_EQ("paramString", parameters["paramString"].getName());
	EXPECT_EQ("paramFileHandle", parameters["paramFileHandle"].getName());
	EXPECT_EQ("paramDirectoryHandle", parameters["paramDirectoryHandle"].getName());
	EXPECT_EQ("paramIntVector", parameters["paramIntVector"].getName());
	EXPECT_EQ("paramDoubleVector", parameters["paramDoubleVector"].getName());
	EXPECT_EQ("paramStringVector", parameters["paramStringVector"].getName());
}

TEST_F(TestParameters, getDescription){
	EXPECT_EQ("description_test_int", parameters["paramInt"].getDescription());
	EXPECT_EQ("description_test_double", parameters["paramDouble"].getDescription());
	EXPECT_EQ("description_test_bool", parameters["paramBool"].getDescription());
	EXPECT_EQ("description_test_string", parameters["paramString"].getDescription());
	EXPECT_EQ("description_test_file", parameters["paramFileHandle"].getDescription());
	EXPECT_EQ("description_test_directory", parameters["paramDirectoryHandle"].getDescription());
	EXPECT_EQ("description_test_intVector", parameters["paramIntVector"].getDescription());
	EXPECT_EQ("description_test_doubleVector", parameters["paramDoubleVector"].getDescription());
	EXPECT_EQ("description_test_stringVector", parameters["paramStringVector"].getDescription());
}

TEST_F(TestParameters, getType){
	EXPECT_EQ(ssf::ParamType::INT, parameters["paramInt"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE, parameters["paramDouble"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::BOOL, parameters["paramBool"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::STRING, parameters["paramString"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::FILE_HANDLE, parameters["paramFileHandle"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DIRECTORY_HANDLE, parameters["paramDirectoryHandle"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::INT_VECTOR, parameters["paramIntVector"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::DOUBLE_VECTOR, parameters["paramDoubleVector"].getExpectedType());
	EXPECT_EQ(ssf::ParamType::STRING_VECTOR, parameters["paramStringVector"].getExpectedType());

}

TEST_F(TestParameters, isRequired){
	EXPECT_FALSE(parameters["paramInt"].isRequired());
	EXPECT_FALSE(parameters["paramDouble"].isRequired());
	EXPECT_FALSE(parameters["paramBool"].isRequired());
	EXPECT_FALSE(parameters["paramString"].isRequired());
	EXPECT_FALSE(parameters["paramFileHandle"].isRequired());
	EXPECT_FALSE(parameters["paramDirectoryHandle"].isRequired());
	EXPECT_FALSE(parameters["paramIntVector"].isRequired());
	EXPECT_FALSE(parameters["paramDoubleVector"].isRequired());
	EXPECT_FALSE(parameters["paramStringVector"].isRequired());

	parameters["paramInt"].setRequired(true);
	EXPECT_TRUE(parameters["paramInt"].isRequired());
	parameters["paramInt"].setRequired(false);
	EXPECT_FALSE(parameters["paramInt"].isRequired());

}

TEST_F(TestParameters, accessParameter){
	EXPECT_NO_THROW(parameters["paramInt"]);
	EXPECT_NO_THROW(parameters.getParameter("paramInt"));
	EXPECT_ANY_THROW(parameters["invalid"]);
	EXPECT_ANY_THROW(parameters.getParameter("invalid"));
}

TEST_F(TestParameters, values){
	EXPECT_EQ(intValue, parameters["paramInt"].toInt());
	EXPECT_EQ(stringValue, parameters["paramString"].toString());
	EXPECT_EQ(boolValue, parameters["paramBool"].toBool());
	EXPECT_EQ(intVectorValue[0], parameters["paramIntVector"].toIntVector()[0]);
	EXPECT_EQ(stringVectorValue[0], parameters["paramStringVector"].toStringVector()[0]);
}

TEST_F(TestParameters, setup){

	ssf::ParametersSetup paramSetup("test");

	paramSetup.addParameter("paramInt", 25);
	paramSetup.addParameter("paramString", "word");
	paramSetup.addParameter("paramBool", true);
	paramSetup.addParameter("paramIntVector", std::vector < int > {51, 52, 53});
	paramSetup.addParameter("paramStringVector", std::vector < std::string > {"51", "52", "53"});

	EXPECT_NO_THROW(parameters.setup(paramSetup));

	EXPECT_EQ(25, parameters["paramInt"].toInt());
	EXPECT_EQ("word", parameters["paramString"].toString());
	EXPECT_EQ(true, parameters["paramBool"].toBool());
	EXPECT_EQ(51, parameters["paramIntVector"].toIntVector()[0]);
	EXPECT_EQ("51", parameters["paramStringVector"].toStringVector()[0]);
}

TEST_F(TestParameters, setupExeptions){

	ssf::ParametersSetup paramSetup("test");

	paramSetup.addParameter("paramInt", "word");
	paramSetup.addParameter("paramString", "word");
	paramSetup.addParameter("paramBool", true);
	paramSetup.addParameter("paramIntVector", std::vector < int > {51, 52, 53});
	paramSetup.addParameter("paramStringVector", std::vector < std::string > {"51", "52", "53"});

	EXPECT_ANY_THROW(parameters.setup(paramSetup));

	paramSetup.setValue("paramInt", 25);
	parameters["paramDouble"].setRequired(true);

	EXPECT_ANY_THROW(parameters.setup(paramSetup));

	parameters["paramDouble"].setRequired(false);
	EXPECT_NO_THROW(parameters.setup(paramSetup));
	
}

TEST_F(TestParameters, getParameterInfo){

	std::map<std::string, ssf::ParameterInfo> parametersInfo =  parameters.getParametersInfo();

	EXPECT_EQ("paramInt", parametersInfo["paramInt"].getName());
	EXPECT_EQ("description_test_int", parametersInfo["paramInt"].getDescription());
	EXPECT_EQ(ssf::ParamType::INT, parametersInfo["paramInt"].getExpectedType());
	EXPECT_EQ("99", parametersInfo["paramInt"].getDefaultValue());
	EXPECT_EQ(9, parametersInfo.size());


}