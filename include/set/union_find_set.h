//
// Created by LengTouZai on 2025/9/19.
//
#pragma once
#include <vector>
#include <string>

#include "utils/expand_list.h"

template<typename T>
class UnionFindSet final : public SetStructure<T> {
    ExpandList<std::pair<T, int>> *elements; // 元素及其对应的父节点索引
    int _size{};
    void print() const override;

public:
    explicit UnionFindSet(std::string name = "union_find_set");
    ~UnionFindSet() override;

    void make_set(const std::vector<T> &value);
    void insert(const T &value);
    T find_root(const T &value) const;
    void union_set(const T &value1, const T &value2);

    [[nodiscard]] int size() const;
    [[nodiscard]] bool empty() const;
    void clear();
};

#include "union_find_set.tpp"