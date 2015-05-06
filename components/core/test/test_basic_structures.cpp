#include <gtest/gtest.h>
#include <fstream>

#include <core/point2d.hpp>
#include <core/point3d.hpp>
#include <core/cube.hpp>

TEST(Point2D, handles) {
	ssf::Point2Di point_i;
	ssf::Point2Df point_f;
	ssf::Point2Dd point_d;
	ssf::Point2D<long> point_l;

	EXPECT_EQ(0, point_i.getX());
	EXPECT_EQ(0, point_i.getY());
}

TEST(Point3D, handles) {
	ssf::Point3Di point_i;
	ssf::Point3Df point_f;
	ssf::Point3Dd point_d;
	ssf::Point3D<long> point_l;

	EXPECT_EQ(0, point_i.getX());
	EXPECT_EQ(0, point_i.getY());
	EXPECT_EQ(0, point_i.getZ());
}

TEST(Cube, handles) {
	ssf::Cube<int> cube;
	
	EXPECT_EQ(0, cube.getPositionX());
	EXPECT_EQ(0, cube.getPositionY());
	EXPECT_EQ(0, cube.getPositionZ());
}