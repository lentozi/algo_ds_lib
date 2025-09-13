//
// Created by LengTouZai on 2025/9/13.
//
#include "base/string_structure.h"
#include <gtest/gtest.h>

TEST(HStringTest, BasicOperations) {
    HString str1("hello", 5);
    const HString str2("world", 5);
    EXPECT_EQ(str1.size(), 5);
    EXPECT_EQ(str2.size(), 5);

    str1.concat(str2);
    EXPECT_EQ(str1.size(), 10);

    HString substr;
    str1.substring(0, 5, substr);
    EXPECT_EQ(substr.size(), 5);
    EXPECT_EQ(substr.index(HString("hello", 5), 0), 0);
    EXPECT_EQ(str1.kmp_index(HString("wo", 2), 3), 5);

    EXPECT_THROW(str1.substring(0, 20, substr), std::out_of_range); // Invalid substring length
}