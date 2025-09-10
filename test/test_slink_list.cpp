//
// Created by LengTouZai on 2025/9/10.
//
#include <gtest/gtest.h>
#include "base/linear_structure.h"

TEST(SLinkListTest, InsertAndLocate) {
    SLinkList<int> list("SLinkList", 10);
    list.insert(0, 42);
    list.insert(1, 43);
    list.insert(1, 44);
    EXPECT_EQ(list.locate(43), 2);
}
