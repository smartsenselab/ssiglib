#include <gtest/gtest.h>
#include <fstream>

#include <core/file_handle.hpp>

TEST(FileHandle, Constructor) {
	EXPECT_ANY_THROW(ssf::FileHandle InvalidFile("invalid.txt"));
	EXPECT_NO_THROW(ssf::FileHandle ValidFile("test_file.txt"));
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