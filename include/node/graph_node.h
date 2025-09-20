//
// Created by LengTouZai on 2025/9/20.
//
#pragma once

template<typename T, typename E>
class ArcNode {
public:
    T adjvex;   // 该弧所指向的顶点位置
    ArcNode *next; // 指向下一条弧的指针
    E value;    // 边的权值

    explicit ArcNode(const T &adjvex, const E value) : adjvex(adjvex), next(nullptr), value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const ArcNode &node) {
        os << "ArcNode(adjvex: " << node.adjvex << ")";
        return os;
    }
};

template<typename V, typename E>
class VNode {
public:
    V data; // 顶点信息
    ArcNode<int, E> *first_arc; // 指向第一条依附该顶点的弧的指针

    explicit VNode() : first_arc(nullptr) {}
    explicit VNode(const V &data) : data(data), first_arc(nullptr) {}

    friend std::ostream &operator<<(std::ostream &os, const VNode &node) {
        os << "VNode(data: " << node.data << ")";
        return os;
    }
};