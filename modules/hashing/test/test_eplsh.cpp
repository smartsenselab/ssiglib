/*L*****************************************************************************
 *
 *  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
 *
 *  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 *
 *  By downloading, copying, installing or using the software you agree to this
 *  license. If you do not agree to this license, do not download, install, copy
 *  or use the software.
 *
 *                Software License Agreement (BSD License)
 *             For Smart Surveillance Interest Group Library
 *                         http://ssig.dcc.ufmg.br
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
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************L*/

#include <gtest/gtest.h>

#include "hashing/eplsh.hpp"

TEST(EPLSH, Retrieval) {
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 1, 1, 2, 2, 3);
  cv::Mat_<float> gallery = (cv::Mat_<float>(5, 2) <<
                             2, 1,
                             3, 1,
                             1, 2,
                             1, 3,
                             1, 1);
  cv::Mat_<float> q1 = (cv::Mat_<float>(1, 2) << 3, 0);
  cv::Mat_<float> q2 = (cv::Mat_<float>(1, 2) << 0, 3);
  cv::Mat_<float> q3 = (cv::Mat_<float>(1, 2) << 0, 0);

  ssig::EPLSH plsh(gallery, labels, 1000, 2, 1);
  ssig::EPLSH::CandListType cand;

  plsh.query(q1, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 1);
  EXPECT_EQ(cand[1].first, 3);
  EXPECT_EQ(cand[2].first, 2);

  // check response consistency
  EXPECT_GE(cand[0].second, 0);
  EXPECT_LE(cand[2].second, 0);

  plsh.query(q2, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 2);
  EXPECT_EQ(cand[1].first, 3);
  EXPECT_EQ(cand[2].first, 1);

  // check response consistency
  EXPECT_GE(cand[0].second, 0);
  EXPECT_LE(cand[2].second, 0);

  plsh.query(q3, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 3);
}

TEST(EPLSH, FactorsDims) {
  cv::Mat_<int> labels = (cv::Mat_<int>(5, 1) << 1, 1, 2, 2, 3);
  cv::Mat_<float> gallery = (cv::Mat_<float>(5, 2) <<
                             2, 1,
                             3, 1,
                             1, 2,
                             1, 3,
                             1, 1);
  cv::Mat_<float> q1 = (cv::Mat_<float>(1, 2) << 3, 0);
  cv::Mat_<float> q2 = (cv::Mat_<float>(1, 2) << 0, 3);
  cv::Mat_<float> q3 = (cv::Mat_<float>(1, 2) << 0, 0);

  ssig::EPLSH plsh(gallery, labels, 1000, 1, 2);
  ssig::EPLSH::CandListType cand;

  plsh.query(q1, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 1);
  EXPECT_EQ(cand[1].first, 3);
  EXPECT_EQ(cand[2].first, 2);

  // check response consistency
  EXPECT_GE(cand[0].second, 0);
  EXPECT_LE(cand[2].second, 0);

  plsh.query(q2, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 2);
  EXPECT_EQ(cand[1].first, 3);
  EXPECT_EQ(cand[2].first, 1);

  // check response consistency
  EXPECT_GE(cand[0].second, 0);
  EXPECT_LE(cand[2].second, 0);

  plsh.query(q3, cand);

  // check ranks
  EXPECT_EQ(cand.size(), size_t(3));
  EXPECT_EQ(cand[0].first, 3);
}
