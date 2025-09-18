//
// Created by LengTouZai on 2025/9/17.
//
#pragma once
#include "utils/node.h"
#include "utils/tree_iterator.h"

template<typename T>
using LinkedTreeNode = typename Node<T>::LinkedTreeNode;
template<typename T>
using BinaryTreeNode = typename Node<T>::BinaryTreeNode;

template<typename T>
class BinaryTree;

template<typename T>
class LinkedBinaryTree final : public TreeStructure<T> {
    LinkedTreeNode<T>* root = nullptr;
    LinkedTreeNode<T>* _current = nullptr; // 用于迭代器的当前节点
    LinkedTreeNode<T>* _end = nullptr; // 用于迭代器的结束节点
    TraverseType _traverse;
    void print() const override;

public:
    explicit LinkedBinaryTree(std::string name = "linked_binary_tree");
    ~LinkedBinaryTree() override;

    void build_tree(BinaryTreeNode<T> *binary_root, TraverseType type = TraverseType::PreOrder);

    LinkedTreeNode<T>* begin();
    LinkedTreeNode<T>* next();
    LinkedTreeNode<T>* end();
    [[nodiscard]] bool is_end() const;
    void reset_iterator();

};

#include "linked_binary_tree.tpp"
