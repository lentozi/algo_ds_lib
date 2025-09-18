//
// Created by LengTouZai on 2025/9/15.
//
#pragma once
#include <string>
#include <vector>
#include <optional>

template<typename T>
class TreeStructure {
protected:
    std::string name = "tree_structure";

    virtual void print() const = 0;

public:
    virtual ~TreeStructure() = default;

    // virtual void build_tree(std::vector<std::pair<T, std::vector<std::optional<T>>>> tree) = 0;
};

#include "tree/binary_tree.h"
#include "tree/linked_binary_tree.h"