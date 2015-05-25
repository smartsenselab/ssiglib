//#include <gtest/gtest.h>
//
//#include <core/version_info.hpp>
//
//TEST(VersionInfo, operators) {
//	ssf::VersionInfo v1(0, 1, 2);
//	ssf::VersionInfo v2(0, 1, 2);
//	ssf::VersionInfo v3(0, 1, 3);
//
//	EXPECT_TRUE(v1 == v2);
//	EXPECT_FALSE(v1 == v3);
//
//	EXPECT_TRUE(v1 != v3);
//	EXPECT_FALSE(v1 != v2);
//
//	EXPECT_TRUE(v3 > v1);
//	EXPECT_FALSE(v1 > v2);
//	EXPECT_FALSE(v1 > v3);
//
//	EXPECT_TRUE(v1 < v3);
//	EXPECT_FALSE(v1 < v2);
//	EXPECT_FALSE(v3 < v1);
//
//	EXPECT_TRUE(v1 <= v3);
//	EXPECT_TRUE(v1 <= v2);
//	EXPECT_FALSE(v3 <= v1);
//
//	EXPECT_TRUE(v3 >= v1);
//	EXPECT_TRUE(v1 >= v2);
//	EXPECT_FALSE(v1 >= v3);
//}
//
//TEST(VersionInfo, stringOperations) {
//
//	ssf::VersionInfo v1(1, 2, 3);	
//	ssf::VersionInfo v2("1.2.3");
//
//	EXPECT_TRUE(v1 == v2);
//
//	EXPECT_ANY_THROW(v1.set(""));
//	EXPECT_ANY_THROW(v1.set("1.x.xxx"));
//	EXPECT_ANY_THROW(v1.set("1.2.3.4"));
//
//	EXPECT_TRUE(v1 == v2);
//
//	v1.set(0, 2, 0);
//	v2.set("0.2.0");
//
//	EXPECT_TRUE(v1 == v2);
//}