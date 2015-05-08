#include <gtest/gtest.h>

#include <core/version_info.hpp>

TEST(FileHandle, equal) {
	ssf::VersionInfo v1(0, 1, 2);
	ssf::VersionInfo v2(0, 1, 2);
	ssf::VersionInfo v3(0, 1, 3);

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
}