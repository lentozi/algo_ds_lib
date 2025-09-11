//
// Created by LengTouZai on 2025/9/10.
//
#include <gtest/gtest.h>
#include "base/linear_structure.h"

TEST(SqListTest, InsertRemoveAndAt) {
    SqList<int> list("SequenceList", 10);
    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(1, 3); // List: 1, 3, 2
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 3);
    EXPECT_EQ(list.at(2), 2);
    int value;
    list.remove(1, value); // List: 1, 2
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_THROW(list.insert(5, 4), std::out_of_range); // Invalid index
    EXPECT_THROW(list.remove(5, value), std::out_of_range); // Invalid index
}
