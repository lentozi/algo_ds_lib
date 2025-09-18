//
// Created by LengTouZai on 2025/9/16.
//
#pragma once
#include "utils/tree_iterator.h"
#include "utils/node.h"

template<typename T>
class LinkedBinaryTree;

template<typename T>
using BinaryTreeNode = typename Node<T>::BinaryTreeNode;

template<typename T>
class BinaryTree final : public TreeStructure<T> {
    BinaryTreeNode<T> *root = nullptr;
    void print() const override;

public:
    explicit BinaryTree(std::string name = "binary_tree");

    ~BinaryTree() override;

    void build_tree(std::vector<std::pair<T, std::vector<std::optional<T>>>> tree);

    BinaryTreeNode<T>* get_root() const;

    void preorder_traversal() const;
    void inorder_traversal() const;
    void postorder_traversal() const;
    void levelorder_traversal() const;

    void to_forest() const;

    LinkedBinaryTree<T>* to_linked_binary_tree(TraverseType type = TraverseType::PreOrder) const;

    TreeIterator<T>* get_iterator(TraverseType type = TraverseType::PreOrder) const {
        return new TreeIterator<T>(root, type);
    }
};

#include "binary_tree.tpp"