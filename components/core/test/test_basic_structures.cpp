//#include <gtest/gtest.h>
//#include <fstream>
//
//#include <opencv/cv.h>
//
//#include <core/point2d.hpp>
//#include <core/point3d.hpp>
//#include <core/cube.hpp>
//#include <core/rect.hpp>
//
//TEST(Point2D, handles) {
//	ssf::Point2Di point_i;
//	ssf::Point2Df point_f;
//	ssf::Point2Dd point_d;
//	ssf::Point2D<long> point_l;
//	
//	EXPECT_EQ(0, point_i.getX());
//	EXPECT_EQ(0, point_i.getY());
//
//	point_i.set(11, 11);
//	cv::Point point_cv = point_i.toOpenCVPoint();
//	EXPECT_EQ(11, point_cv.x);
//	EXPECT_EQ(11, point_cv.y);
//
//	point_cv = cv::Point(22, 22);
//	point_i.set(point_cv);
//
//	EXPECT_EQ(22, point_i.getX());
//	EXPECT_EQ(22, point_i.getY());
//
//	ssf::Point2Di point_i_b(point_cv);
//	EXPECT_TRUE(point_i == point_i_b);
//	EXPECT_FALSE(point_i != point_i_b);
//
//}
//
//TEST(Point3D, handles) {
//	ssf::Point3Di point_i;
//	ssf::Point3Df point_f;
//	ssf::Point3Dd point_d;
//	ssf::Point3D<long> point_l;
//
//	EXPECT_EQ(0, point_i.getX());
//	EXPECT_EQ(0, point_i.getY());
//	EXPECT_EQ(0, point_i.getZ());
//}
//
//TEST(Rect, handles) {
//	ssf::Rect<int> rect;
//
//	EXPECT_EQ(0, rect.getPositionX());
//	EXPECT_EQ(0, rect.getPositionY());
//}
//
//TEST(Cube, handles) {
//	ssf::Cube<int> cube;
//	
//	EXPECT_EQ(0, cube.getPositionX());
//	EXPECT_EQ(0, cube.getPositionY());
//	EXPECT_EQ(0, cube.getPositionZ());
//}