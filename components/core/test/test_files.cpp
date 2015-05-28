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
#include <fstream>

#include <core/file_handle.hpp>
#include <core/directory_handle.hpp>

TEST(FileHandle, constructor) {
	EXPECT_NO_THROW(ssf::FileHandle InvalidFile("invalid.txt"));
	EXPECT_NO_THROW(ssf::FileHandle ValidFile("test_file.txt"));
}

TEST(FileHandle, exists){
	EXPECT_TRUE(ssf::FileHandle::exists("test_file.txt"));
	EXPECT_FALSE(ssf::FileHandle::exists("invalid.txt"));
}

TEST(FileHandle, hasExtension) {
	ssf::FileHandle fileHandle("test_file.txt");
	EXPECT_TRUE(fileHandle.hasExtension());
}

TEST(FileHandle, erase) {
	std::ofstream tempFile("temp_file.txt");
	tempFile << "temp" << std::endl;
	tempFile.close();

	std::ofstream tempFile2("temp_file2.txt");
	tempFile2 << "temp" << std::endl;
	tempFile2.close();

	ssf::FileHandle fileHandle("temp_file.txt");
	EXPECT_TRUE(fileHandle.erase());
	EXPECT_TRUE(ssf::FileHandle::erase("temp_file2.txt"));
	EXPECT_FALSE(ssf::FileHandle::erase("invalid_file.txt"));
}

TEST(FileHandle, strings) {
	ssf::FileHandle fileHandle("test_file.txt");
	EXPECT_STREQ("test_file", fileHandle.getSimpleName().c_str());
}

TEST(FileHandle, copy) {
	ssf::FileHandle fileHandle1("test_file.txt");
	ssf::FileHandle fileHandle2(fileHandle1);
	ssf::FileHandle fileHandle3 = fileHandle2;

	EXPECT_STREQ("test_file", fileHandle2.getSimpleName().c_str());
	EXPECT_STREQ("test_file", fileHandle3.getSimpleName().c_str());
}

///////////////

TEST(DirectoryHandle, constructor){
	EXPECT_NO_THROW(ssf::DirectoryHandle InvalidFile("invalid_folder"));
	EXPECT_NO_THROW(ssf::DirectoryHandle ValidFile("folder_test"));
}

TEST(DirectoryHandle, exists){
	EXPECT_TRUE(ssf::DirectoryHandle::exists("folder_test"));
	EXPECT_FALSE(ssf::DirectoryHandle::exists("invalid_folder"));
}

TEST(DirectoryHandle, erase) {
	//Aims a unnecessary link with a library to folder creation,
	//the valid folder erase test was implemented in "creation" test.
	EXPECT_FALSE(ssf::DirectoryHandle::erase("invalid_folder"));
}

TEST(DirectoryHandle, lists) {
	ssf::DirectoryHandle directoryHandle("folder_test");
	EXPECT_EQ(3, directoryHandle.listSubDirectories().size());
}

TEST(DirectoryHandle, create) {
	ssf::DirectoryHandle::create("temp_folder");
	EXPECT_NO_THROW(ssf::DirectoryHandle ValidFile("temp_folder"));
	EXPECT_TRUE(ssf::DirectoryHandle::exists("temp_folder"));
	EXPECT_TRUE(ssf::DirectoryHandle::erase("temp_folder"));
}

TEST(DirectoryHandle, strings) {
	ssf::DirectoryHandle directoryHandle("folder_test");
	EXPECT_STREQ("folder_test", directoryHandle.getSimpleName().c_str());
}

TEST(DirectoryHandle, copy) {
	ssf::DirectoryHandle directoryHandle1("folder_test");
	ssf::DirectoryHandle directoryHandle2(directoryHandle1);
	ssf::DirectoryHandle directoryHandle3 = directoryHandle2;

	EXPECT_STREQ("folder_test", directoryHandle2.getSimpleName().c_str());
	EXPECT_STREQ("folder_test", directoryHandle3.getSimpleName().c_str());
}