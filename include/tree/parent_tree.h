//
// Created by LengTouZai on 2025/9/18.
//
#pragma once
#include <vector>
#include <optional>
#include "utils/node.h"
#include "utils/expand_list.h"

template<typename T>
using ParentTreeNode = typename Node<T>::ParentTreeNode;

template<typename T>
class ParentTree final : public TreeStructure<T> {
    ExpandList<ParentTreeNode<T>> *parent_table;
    size_t _size;
    void print() const override;

public:
    explicit ParentTree(std::string name = "parent_tree");
    ~ParentTree() override;

    void build_tree(std::vector<std::pair<T, std::vector<std::optional<T>>>> tree);

    T get_root() const;

    T find_parent(T value) const;
};

#include "parent_tree.tpp"