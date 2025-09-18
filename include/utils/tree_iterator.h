//
// Created by LengTouZai on 2025/9/15.
//
#pragma once
#include "base/stack_structure.h"
#include "base/queue_structure.h"
#include "utils/node.h"

template<typename T>
using BinaryTreeNode = typename Node<T>::BinaryTreeNode;

enum class TraverseType {
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template<typename T>
class TreeIterator {
public:
    explicit TreeIterator(BinaryTreeNode<T>* root, const TraverseType type = TraverseType::PreOrder)
        : traverse_type(type) {
        node_stack = new SqStack<BinaryTreeNode<T>*>("tree_iterator_stack");
        node_queue = new SqQueue<BinaryTreeNode<T>*>("tree_iterator_queue");
        switch (traverse_type) {
            case TraverseType::PreOrder:
                if (root) node_stack->push(root);
                break;
            case TraverseType::InOrder:
                push_left(root);
                break;
            case TraverseType::PostOrder:
                if (root) postorder_init(root);
                break;
            case TraverseType::LevelOrder:
                if (root) node_queue->enqueue(root);
                break;
        }
    }

    ~TreeIterator() {
        delete node_stack;
        delete node_queue;
    }

    [[nodiscard]] bool has_next() const {
        if (traverse_type == TraverseType::LevelOrder)
            return !node_queue->empty();
        return !node_stack->empty();
    }

    BinaryTreeNode<T>* next() {
        if (traverse_type == TraverseType::PreOrder) {
            BinaryTreeNode<T>* node;
            node_stack->pop(node);
            if (node->right) node_stack->push(node->right);
            if (node->left) node_stack->push(node->left);
            return node;
        }
        if (traverse_type == TraverseType::InOrder) {
            BinaryTreeNode<T>* node;
            node_stack->pop(node);
            push_left(node->right);
            return node;
        }
        if (traverse_type == TraverseType::PostOrder) {
            BinaryTreeNode<T>* node;
            node_stack->pop(node);
            return node;
        }
        // LevelOrder
        BinaryTreeNode<T>* node;
        node_queue->dequeue(node);
        if (node->left) node_queue->enqueue(node->left);
        if (node->right) node_queue->enqueue(node->right);
        return node;
    }

private:
    TraverseType traverse_type;
    StackStructure<BinaryTreeNode<T>*>* node_stack = nullptr;
    QueueStructure<BinaryTreeNode<T>*>* node_queue = nullptr;

    void push_left(BinaryTreeNode<T>* node) {
        while (node) {
            node_stack->push(node);
            node = node->left;
        }
    }

    void postorder_init(BinaryTreeNode<T>* root) {
        StackStructure<BinaryTreeNode<T>*>* temp_stack = new SqStack<BinaryTreeNode<T>*>("postorder_temp_stack");
        temp_stack->push(root);
        while (!temp_stack->empty()) {
            BinaryTreeNode<T>* node;
            temp_stack->pop(node);
            node_stack->push(node);
            if (node->left) temp_stack->push(node->left);
            if (node->right) temp_stack->push(node->right);
        }
        delete temp_stack;
    }
};
