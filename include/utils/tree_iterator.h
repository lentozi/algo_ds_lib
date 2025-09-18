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

template<typename T, typename V = typename std::remove_pointer_t<T>::value_type>
class TreeIterator {
    static_assert(
        std::is_base_of_v<BinaryTreeNode<V>, std::remove_pointer_t<T>>,
        "T 必须是 BinaryTreeNode<V> 或其子类的指针类型"
    );

public:
    explicit TreeIterator(T root, const TraverseType type = TraverseType::PreOrder)
        : traverse_type(type) {
        node_stack = new SqStack<T>("tree_iterator_stack");
        node_queue = new SqQueue<T>("tree_iterator_queue");
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

    T next() {
        if (traverse_type == TraverseType::PreOrder) {
            T node;
            node_stack->pop(node);
            if (node->right) node_stack->push(static_cast<T>(node->right));
            if (node->left) node_stack->push(static_cast<T>(node->left));
            return node;
        }
        if (traverse_type == TraverseType::InOrder) {
            T node;
            node_stack->pop(node);
            push_left(static_cast<T>(node->right));
            return node;
        }
        if (traverse_type == TraverseType::PostOrder) {
            T node;
            node_stack->pop(node);
            return node;
        }
        // LevelOrder
        T node;
        node_queue->dequeue(node);
        if (node->left) node_queue->enqueue(static_cast<T>(node->left));
        if (node->right) node_queue->enqueue(static_cast<T>(node->right));
        return node;
    }

private:
    TraverseType traverse_type;
    StackStructure<T>* node_stack = nullptr;
    QueueStructure<T>* node_queue = nullptr;

    void push_left(T node) {
        while (node) {
            node_stack->push(node);
            node = static_cast<T>(node->left);
        }
    }

    void postorder_init(T root) {
        StackStructure<T>* temp_stack = new SqStack<T>("postorder_temp_stack");
        temp_stack->push(root);
        while (!temp_stack->empty()) {
            T node;
            temp_stack->pop(node);
            node_stack->push(node);
            if (node->left) temp_stack->push(static_cast<T>(node->left));
            if (node->right) temp_stack->push(static_cast<T>(node->right));
        }
        delete temp_stack;
    }
};
