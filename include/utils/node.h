#pragma once
#include <ostream>

template<typename T>
class Node {
public:
    class SingleNode {
    public:
        T data;
        SingleNode *next;

        explicit SingleNode(const T &value) : data(value), next(nullptr) {
        }

        friend std::ostream &operator<<(std::ostream &os, const SingleNode &node) {
            os << "SingleNode(data: " << node.data << ")";
            return os;
        }
    };

    class DoubleNode {
    public:
        T data;
        DoubleNode *prev;
        DoubleNode *next;

        explicit DoubleNode(const T &value) : data(value), prev(nullptr), next(nullptr) {
        }

        friend std::ostream &operator<<(std::ostream &os, const DoubleNode &node) {
            os << "DoubleNode(data: " << node.data << ")";
            return os;
        }
    };
};