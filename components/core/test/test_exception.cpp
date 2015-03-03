#include "gtest/gtest.h"

TEST(IndependentMethod, ResetsToZero) {
	int i = 0;
	EXPECT_EQ(0, i);

	i = 12;
	EXPECT_EQ(12,i);
}