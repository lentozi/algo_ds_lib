//
// Created by LengTouZai on 2025/9/26.
//
#include "base/search_algorithm.h"
#include "gtest/gtest.h"

TEST(SeqSearchTest, SeqSearch) {
    LinearStructure<int>* list = new SqList<int>("SequenceList", 10);
    // 第一个位置不存放元素
    list->insert(0, -1);
    list->insert(1, 1);
    list->insert(1, 2);
    list->insert(1, 3); // List: 1, 3, 2

    const auto* seq_searcher = new SeqSearch(list);

    EXPECT_EQ(seq_searcher->search(1), 3);
    EXPECT_EQ(seq_searcher->search(2), 2);
    EXPECT_EQ(seq_searcher->search(3), 1);
    EXPECT_EQ(seq_searcher->search(4), 0);

    delete seq_searcher;
    delete list;
}