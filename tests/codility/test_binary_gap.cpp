#include "codility/binary_gap.hpp"

#include <gtest/gtest.h>

TEST(BinaryGapTest, CodilityExamples) {
    EXPECT_EQ(codility::binary_gap(9), 2);   // 1001
    EXPECT_EQ(codility::binary_gap(529), 4); // 1000010001
    EXPECT_EQ(codility::binary_gap(20), 1);  // 10100
    EXPECT_EQ(codility::binary_gap(15), 0);  // 1111
    EXPECT_EQ(codility::binary_gap(32), 0);  // 100000
}

TEST(BinaryGapTest, EdgeCases) {
    EXPECT_EQ(codility::binary_gap(1), 0);
    EXPECT_EQ(codility::binary_gap(1041), 5);
}