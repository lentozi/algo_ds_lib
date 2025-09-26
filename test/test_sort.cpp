//
// Created by LengTouZai on 2025/9/26.
//
#include "base/sort_algorithm.h"
#include "gtest/gtest.h"

TEST(SortTest, Sort) {
    LinearStructure<int>* list = new SqList<int>("SequenceList", 10);
    // 要求第一个位置不存放元素
    list->insert(0, -1);
    list->insert(1, 9);
    list->insert(1, 7);
    list->insert(1, 20);
    list->insert(1, 5);
    list->insert(1, 11);
    list->insert(1, 2);

    const auto* sorter = new InsertSort(list);
    sorter->sort(true);

    EXPECT_EQ(list->at(1), 2);
    EXPECT_EQ(list->at(2), 5);
    EXPECT_EQ(list->at(3), 7);
    EXPECT_EQ(list->at(4), 9);
    EXPECT_EQ(list->at(5), 11);
    EXPECT_EQ(list->at(6), 20);

    delete list;
    delete sorter;
}