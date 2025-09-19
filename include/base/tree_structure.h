//
// Created by LengTouZai on 2025/9/15.
//
#pragma once
#include <string>
#include <utility>

template<typename T>
class TreeStructure {
protected:
    std::string name = "tree_structure";

    virtual void print() const = 0;

public:
    explicit TreeStructure(std::string name) : name(std::move(name)) {}

    virtual ~TreeStructure() = default;
};

#include "tree/parent_tree.h"
#include "tree/binary_tree.h"
#include "tree/huffman_tree.h"
#include "tree/linked_binary_tree.h"