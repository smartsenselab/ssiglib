///*L*************************************************************************************************
//*
//*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//* 
//*  By downloading, copying, installing or using the software you agree to this license. If you do 
//*  not agree to this license, do not download, install, copy or use the software.
//*
//*                            Software License Agreement (BSD License)
//*                               For Smart Surveillance Framework
//*                                 http://ssig.dcc.ufmg.br/ssf/
//*
//*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
//*  
//*  Redistribution and use in source and binary forms, with or without modification, are permitted 
//*  provided that the following conditions are met:
//*
//*    1. Redistributions of source code must retain the above copyright notice, this list of 
//*       conditions and the following disclaimer.
//*
//*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
//*       conditions and the following disclaimer in the documentation and/or other materials 
//*       provided with the distribution.
//*
//*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
//*       endorse or promote products derived from this software without specific prior written 
//*       permission.
//*
//*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
//*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
//*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
//*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
//*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
//*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
//*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//*  POSSIBILITY OF SUCH DAMAGE.
//*************************************************************************************************L*/
//
//#include <gtest/gtest.h>
//
//#include "core/resource.hpp"
//
//class ResourceTest : public ssf::Resource{
//
//public:
//	std::string name() { return "RESOURCE_SPECIALIZATION"; }
//	std::string type() { return "TYPE_RESOURCE_SPECIALIZATION"; }
//
//	ResourceTest(){
//
//		this->setAuthor("Antonio");
//		this->setAuthorEmail("antonio@ssig.br");
//		this->setDescription("resource_description");
//		this->setRequiredVersion(2, 0);
//
//		intValue = 99;
//		doubleValue = 99999.88888888;
//		boolValue = true;
//		stringValue = "stringValue";
//		fileHandleValue = ssf::FileHandle("test_file.txt");
//		directoryHandleValue = ssf::DirectoryHandle("folder_test");
//		intVectorValue = std::vector < int > {10, 11, 12};
//		doubleVectorValue = std::vector < double > {1000, 1100.1, 1200.2};
//		stringVectorValue = std::vector < std::string > {"a", "b", "c"};
//
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramInt", intValue, "description_test_int"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDouble", doubleValue, "description_test_double"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramBool", boolValue, "description_test_bool"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramString", stringValue, "description_test_string"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramFileHandle", fileHandleValue, "description_test_file"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDirectoryHandle", directoryHandleValue, "description_test_directory"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramIntVector", intVectorValue, "description_test_intVector"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramDoubleVector", doubleVectorValue, "description_test_doubleVector"));
//		EXPECT_NO_THROW(this->PARAMETERS.addParameter("paramStringVector", stringVectorValue, "description_test_stringVector"));
//
//	}
//
//	int intValue;
//	double doubleValue;
//	bool boolValue;
//	std::string stringValue;
//	ssf::FileHandle fileHandleValue;
//	ssf::DirectoryHandle directoryHandleValue;
//	std::vector<int> intVectorValue;
//	std::vector<double> doubleVectorValue;
//	std::vector<std::string> stringVectorValue;
//
//};
//
//
//class TestResource : public ::testing::Test{
//protected:
//
//	virtual void SetUp(){
//		EXPECT_NO_THROW(resource = new ResourceTest());
//	}
//
//	virtual void TearDown() {
//		delete resource;
//	}
//
//	ResourceTest* resource;
//};
//
//TEST_F(TestResource, resourceInfo){
//
//	EXPECT_STREQ("RESOURCE_SPECIALIZATION", this->resource->name().c_str());
//	EXPECT_STREQ("TYPE_RESOURCE_SPECIALIZATION", this->resource->type().c_str());
//
//	ssf::ResourceInfo info = this->resource->info();
//	EXPECT_STREQ("Antonio", info.author().c_str());
//	EXPECT_STREQ("antonio@ssig.br", info.authorEmail().c_str());
//	EXPECT_STREQ("resource_description", info.description().c_str());
//	EXPECT_STREQ("2.0.0", info.requiredVersion().toString().c_str());
//	EXPECT_EQ(2, info.requiredVersion().major());
//	EXPECT_EQ(0, info.requiredVersion().minor());
//
//	std::map<std::string, ssf::ParameterInfo> paramsInfo = info.parametersInfo();
//
//	EXPECT_EQ(ssf::ParamType::INT, paramsInfo["paramInt"].expectedType());
//	EXPECT_STREQ("paramInt", paramsInfo["paramInt"].name().c_str());
//	EXPECT_STREQ("description_test_int", paramsInfo["paramInt"].description().c_str());
//
//}