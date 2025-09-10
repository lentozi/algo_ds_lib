//
// Created by LengTouZai on 2025/9/10.
//
#include <gtest/gtest.h>
#include "base/linear_structure.h"

TEST(DLinkListTest, InsertAndPriorNode) {
    DLinkList<int> list("DLinkList");
    list.insert(0, 42);
    list.insert(1, 43);
    list.insert(1, 44);
    DoubleNode<int>* node = list.find_node(1);
    list.insert_prior_node(node, 100);
    EXPECT_EQ(list.locate(100), 1);
    EXPECT_EQ(list.locate(43), 3);
}
