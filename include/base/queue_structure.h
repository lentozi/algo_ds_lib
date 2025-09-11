//
// Created by LengTouZai on 2025/9/10.
//
#pragma once
#include <string>

template<typename T>
class QueueStructure {
protected:
    std::string name = "queue_structure";

    virtual void print() const = 0;

public:
    virtual ~QueueStructure() = default;

    virtual void enqueue(const T &value) = 0;

    virtual void dequeue(T &value) = 0;

    virtual void get_front(T &value) const = 0;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual size_t size() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const QueueStructure &q) {
        q.print();
        return os;
    }
};

#include "queue/sqqueue.h"
