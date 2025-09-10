//
// Created by LengTouZai on 2025/9/10.
//
#include <gtest/gtest.h>
#include "base/linear_structure.h"

TEST(SqListTest, InsertAndPrint) {
    SqList<int> list("SequenceList", 10);
    list.insert(0, 42);
    list.insert(1, 43);
    list.insert(1, 44);
    EXPECT_EQ(list.locate(42), 0);
    EXPECT_EQ(list.locate(44), 1);
    EXPECT_EQ(list.locate(43), 2);
}
