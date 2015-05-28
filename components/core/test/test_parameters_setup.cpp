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

#include <map>

#include "core/parameters_setup.hpp"

class TestParametersSetup : public ::testing::Test{
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

		paramSetup = ssf::ParametersSetup("test");

		EXPECT_NO_THROW(paramSetup.addParameter("paramInt", intValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramDouble", doubleValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramBool", boolValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramString", stringValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramFileHandle", fileHandleValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramDirectoryHandle", directoryHandleValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramIntVector", intVectorValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramDoubleVector", doubleVectorValue));
		EXPECT_NO_THROW(paramSetup.addParameter("paramStringVector", stringVectorValue));

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

	ssf::ParametersSetup paramSetup;

};

TEST_F(TestParametersSetup, id){
	EXPECT_EQ("test", paramSetup.getID());
	EXPECT_NO_THROW(paramSetup.setID("id_test"));
	EXPECT_EQ("id_test", paramSetup.getID());
}

TEST_F(TestParametersSetup, testValues){

	std::map<std::string, std::vector<std::string>> values = paramSetup.getParametersValues();
	EXPECT_EQ("99", values["paramInt"][0]);
	EXPECT_EQ("99.900000", values["paramDouble"][0]);
	EXPECT_EQ("true", values["paramBool"][0]);
	EXPECT_EQ("stringValue", values["paramString"][0]);
	EXPECT_EQ(ssf::FileHandle("test_file.txt").getAbsoluteFileName(), values["paramFileHandle"][0]);
	EXPECT_EQ(ssf::DirectoryHandle("folder_test").getAbsolutePath(), values["paramDirectoryHandle"][0]);
	EXPECT_EQ("10", values["paramIntVector"][0]);
	EXPECT_EQ("11", values["paramIntVector"][1]);
	EXPECT_EQ("12", values["paramIntVector"][2]);
	EXPECT_EQ("1000.000000", values["paramDoubleVector"][0]);
	EXPECT_EQ("1100.100000", values["paramDoubleVector"][1]);
	EXPECT_EQ("1200.200000", values["paramDoubleVector"][2]);
	EXPECT_EQ("a", values["paramStringVector"][0]);
	EXPECT_EQ("b", values["paramStringVector"][1]);
	EXPECT_EQ("c", values["paramStringVector"][2]);

}

TEST_F(TestParametersSetup, setValue){
	EXPECT_NO_THROW(paramSetup.setValue("paramInt", 10));
	EXPECT_NO_THROW(paramSetup.setValue("paramDouble", 11.1));
	EXPECT_NO_THROW(paramSetup.setValue("paramBool", false));
	EXPECT_NO_THROW(paramSetup.setValue("paramString", "new_value"));
	EXPECT_NO_THROW(paramSetup.setValue("paramFileHandle", ssf::FileHandle("new_file.txt")));
	EXPECT_NO_THROW(paramSetup.setValue("paramDirectoryHandle", ssf::DirectoryHandle("new_directory")));
	EXPECT_NO_THROW(paramSetup.setValue("paramIntVector", std::vector < int > {97, 98, 99}));
	EXPECT_NO_THROW(paramSetup.setValue("paramDoubleVector", std::vector < double > {97.7, 98.8, 99.9}));
	EXPECT_NO_THROW(paramSetup.setValue("paramStringVector", std::vector < std::string > {"x", "y", "z"}));

	std::map<std::string, std::vector<std::string>> values = paramSetup.getParametersValues();
	EXPECT_EQ("10", values["paramInt"][0]);
	EXPECT_EQ("11.100000", values["paramDouble"][0]);
	EXPECT_EQ("false", values["paramBool"][0]);
	EXPECT_EQ("new_value", values["paramString"][0]);
	EXPECT_EQ(ssf::FileHandle("new_file.txt").getAbsoluteFileName(), values["paramFileHandle"][0]);
	EXPECT_EQ(ssf::DirectoryHandle("new_directory").getAbsolutePath(), values["paramDirectoryHandle"][0]);
	EXPECT_EQ("97", values["paramIntVector"][0]);
	EXPECT_EQ("98", values["paramIntVector"][1]);
	EXPECT_EQ("99", values["paramIntVector"][2]);
	EXPECT_EQ("97.700000", values["paramDoubleVector"][0]);
	EXPECT_EQ("98.800000", values["paramDoubleVector"][1]);
	EXPECT_EQ("99.900000", values["paramDoubleVector"][2]);
	EXPECT_EQ("x", values["paramStringVector"][0]);
	EXPECT_EQ("y", values["paramStringVector"][1]);
	EXPECT_EQ("z", values["paramStringVector"][2]);
}

TEST_F(TestParametersSetup, exception){
	EXPECT_ANY_THROW(paramSetup.addParameter("paramInt", intValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramDouble", doubleValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramBool", boolValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramString", stringValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramFileHandle", fileHandleValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramDirectoryHandle", directoryHandleValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramIntVector", intVectorValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramDoubleVector", doubleVectorValue));
	EXPECT_ANY_THROW(paramSetup.addParameter("paramStringVector", stringVectorValue));

	EXPECT_ANY_THROW(paramSetup.setValue("paramIntAAA", 10));
	EXPECT_ANY_THROW(paramSetup.setValue("paramDoubleAAA", 11.1));
	EXPECT_ANY_THROW(paramSetup.setValue("paramBoolAAA", false));
	EXPECT_ANY_THROW(paramSetup.setValue("paramStringAAA", "new_value"));
	EXPECT_ANY_THROW(paramSetup.setValue("paramFileHandleAAA", ssf::FileHandle("new_file.txt")));
	EXPECT_ANY_THROW(paramSetup.setValue("paramDirectoryHandleAAA", ssf::DirectoryHandle("new_directory")));
	EXPECT_ANY_THROW(paramSetup.setValue("paramIntVectorAAA", std::vector < int > {97, 98, 99}));
	EXPECT_ANY_THROW(paramSetup.setValue("paramDoubleVectorAAA", std::vector < double > {97.7, 98.8, 99.9}));
	EXPECT_ANY_THROW(paramSetup.setValue("paramStringVectorAAA", std::vector < std::string > {"x", "y", "z"}));

}

TEST_F(TestParametersSetup, ReadFromFile){

	ssf::ParametersSetup paramFromFile(ssf::FileHandle("parameters.yml"), "config1");

	EXPECT_EQ("config1", paramFromFile.getID());

	std::map<std::string, std::vector<std::string>> values = paramFromFile.getParametersValues();
	EXPECT_EQ("10", values["paramInteger"][0]);
	EXPECT_EQ("2.200000", values["paramDouble"][0]);
	EXPECT_EQ("test_string", values["paramString"][0]);
	EXPECT_EQ("true", values["paramBool"][0]);
	EXPECT_EQ("test_file.txt", values["paramFileHandle"][0]);
	EXPECT_EQ("folder_test", values["paramDirectoryHandle"][0]);
	EXPECT_EQ("10", values["paramIntVector"][0]);
	EXPECT_EQ("11", values["paramIntVector"][1]);
	EXPECT_EQ("12", values["paramIntVector"][2]);
	EXPECT_EQ("1000", values["paramDoubleVector"][0]);
	EXPECT_EQ("1100.100000", values["paramDoubleVector"][1]);
	EXPECT_EQ("1200.200000", values["paramDoubleVector"][2]);
	EXPECT_EQ("a", values["paramStringVector"][0]);
	EXPECT_EQ("b", values["paramStringVector"][1]);
	EXPECT_EQ("c", values["paramStringVector"][2]);

}

TEST_F(TestParametersSetup, InvalidReadFrom){

	EXPECT_ANY_THROW(ssf::ParametersSetup invalid1(ssf::FileHandle("parameters.yml"), "invalid1"));
	EXPECT_ANY_THROW(ssf::ParametersSetup invalid2(ssf::FileHandle("parameters.yml"), "invalid2"));
	EXPECT_ANY_THROW(ssf::ParametersSetup invalid3(ssf::FileHandle("parameters.yml"), "invalid3"));
	EXPECT_ANY_THROW(ssf::ParametersSetup invalid4(ssf::FileHandle("parameters.yml"), "invalid4"));
	EXPECT_ANY_THROW(ssf::ParametersSetup invalid5(ssf::FileHandle("invalid_file.yml"), "any"));

	

}