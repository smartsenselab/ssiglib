#include <gtest/gtest.h>
#include <fstream>

#include <core/file_handle.hpp>
#include <core/directory_handle.hpp>

TEST(FileHandle, constructor) {
	EXPECT_ANY_THROW(ssf::FileHandle InvalidFile("invalid.txt"));
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

///////////////

TEST(DirectoryHandle, constructor){
	EXPECT_ANY_THROW(ssf::DirectoryHandle InvalidFile("invalid_folder"));
	EXPECT_NO_THROW(ssf::DirectoryHandle ValidFile("folder_test"));
}

TEST(DirectoryHandle, exists){
	EXPECT_TRUE(ssf::DirectoryHandle::exists("folder_test"));
	EXPECT_FALSE(ssf::DirectoryHandle::exists("invalid_folder"));
}

TEST(DirectoryHandle, erase) {
	//For unnecessary link with a library to folder creation,
	//the valid folder erase test was implemented in "creation" test.
	EXPECT_FALSE(ssf::DirectoryHandle::erase("invalid_folder"));
}

TEST(DirectoryHandle, lists) {
	ssf::DirectoryHandle DirectoryHandle("folder_test");
	EXPECT_EQ(3, DirectoryHandle.listSubDirectories().size());
}

TEST(DirectoryHandle, create) {
	ssf::DirectoryHandle::create("temp_folder");
	EXPECT_NO_THROW(ssf::DirectoryHandle ValidFile("temp_folder"));
	EXPECT_TRUE(ssf::DirectoryHandle::exists("temp_folder"));
	EXPECT_TRUE(ssf::DirectoryHandle::erase("temp_folder"));
}