//
// Created by LengTouZai on 2025/9/10.
//
#include <gtest/gtest.h>
#include "base/stack_structure.h"

TEST(SqStackTest, PushAndPrint) {
    SqStack<int> stack("SqStack", 10);
    stack.push(42);
    stack.push(43);
    stack.push(44);
    EXPECT_FALSE(stack.empty());
}
