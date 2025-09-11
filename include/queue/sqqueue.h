//
// Created by LengTouZai on 2025/9/11.
//
#pragma once
#include "utils/expand_list.h"

template<typename T>
class SqQueue final : public QueueStructure<T> {
    ExpandList<T> *data; // 队列中元素
    int front = 0; // 队头指针，初始时为 0，指向队头元素
    int rear = -1; // 队尾指针，初始时为 -1，指向队尾元素
    int max_size = -1; // 队列最大长度，如果设置为 -1 则不做限制
    int flag = 0; // 队列标记，0 表示上一个操作是出队，1 表示上一个操作是入队

    void print() const override;

public:
    explicit SqQueue(std::string name, size_t initial_capacity = 10, int max_size = -1);

    ~SqQueue() override;

    void enqueue(const T &value) override;

    void dequeue(T &value) override;

    void get_front(T &value) const override;

    [[nodiscard]] bool empty() const override;

    [[nodiscard]] size_t size() const override;
};

#include "sqqueue.tpp"