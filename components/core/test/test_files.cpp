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