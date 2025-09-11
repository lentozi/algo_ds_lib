//
// Created by LengTouZai on 2025/9/11.
//
#include <gtest/gtest.h>
#include "base/queue_structure.h"

TEST(SqQueueTest, EnqueueDequeueAndSize) {
    SqQueue<int> queue("SequenceQueue", 5, 5);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.size(), 3);

    int value;
    queue.dequeue(value);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(queue.size(), 2);
    queue.get_front(value);
    EXPECT_EQ(value, 2);
    queue.enqueue(4);
    queue.enqueue(5);
    EXPECT_EQ(queue.size(), 4);
    queue.enqueue(6);
    EXPECT_EQ(queue.size(), 5);
    EXPECT_THROW(queue.enqueue(7), std::out_of_range); // Queue is full
    queue.dequeue(value);
    EXPECT_EQ(value, 2);
    queue.dequeue(value);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(queue.size(), 3);
    queue.enqueue(7);
    EXPECT_EQ(queue.size(), 4);
    queue.get_front(value);
    EXPECT_EQ(value, 4);
}
