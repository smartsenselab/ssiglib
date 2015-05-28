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

#include <opencv/cv.h>

#include <core/point2d.hpp>
#include <core/point3d.hpp>
#include <core/cube.hpp>
#include <core/rect.hpp>

TEST(Point2D, handles) {
	ssf::Point2Di point_i;
	ssf::Point2Df point_f;
	ssf::Point2Dd point_d;
	ssf::Point2D<long> point_l;
	
	EXPECT_EQ(0, point_i.getX());
	EXPECT_EQ(0, point_i.getY());

	point_i.set(11, 11);
	cv::Point point_cv = point_i.toOpenCVPoint();
	EXPECT_EQ(11, point_cv.x);
	EXPECT_EQ(11, point_cv.y);

	point_cv = cv::Point(22, 22);
	point_i.set(point_cv);

	EXPECT_EQ(22, point_i.getX());
	EXPECT_EQ(22, point_i.getY());

	ssf::Point2Di point_i_b(point_cv);
	EXPECT_TRUE(point_i == point_i_b);
	EXPECT_FALSE(point_i != point_i_b);

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

TEST(Rect, handles) {
	ssf::Rect<int> rect;

	EXPECT_EQ(0, rect.getPositionX());
	EXPECT_EQ(0, rect.getPositionY());
}

TEST(Cube, handles) {
	ssf::Cube<int> cube;
	
	EXPECT_EQ(0, cube.getPositionX());
	EXPECT_EQ(0, cube.getPositionY());
	EXPECT_EQ(0, cube.getPositionZ());
}