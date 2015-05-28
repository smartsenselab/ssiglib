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

#include <core/version_info.hpp>

TEST(VersionInfo, operators) {
	ssf::VersionInfo v1(0, 1, 2);
	ssf::VersionInfo v2(0, 1, 2);
	ssf::VersionInfo v3(0, 1, 3);

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);

	EXPECT_TRUE(v1 != v3);
	EXPECT_FALSE(v1 != v2);

	EXPECT_TRUE(v3 > v1);
	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v1 > v3);

	EXPECT_TRUE(v1 < v3);
	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v3 < v1);

	EXPECT_TRUE(v1 <= v3);
	EXPECT_TRUE(v1 <= v2);
	EXPECT_FALSE(v3 <= v1);

	EXPECT_TRUE(v3 >= v1);
	EXPECT_TRUE(v1 >= v2);
	EXPECT_FALSE(v1 >= v3);
}

TEST(VersionInfo, stringOperations) {

	ssf::VersionInfo v1(1, 2, 3);	
	ssf::VersionInfo v2("1.2.3");

	EXPECT_TRUE(v1 == v2);

	EXPECT_ANY_THROW(v1.set(""));
	EXPECT_ANY_THROW(v1.set("1.x.xxx"));
	EXPECT_ANY_THROW(v1.set("1.2.3.4"));

	EXPECT_TRUE(v1 == v2);

	v1.set(0, 2, 0);
	v2.set("0.2.0");

	EXPECT_TRUE(v1 == v2);
}