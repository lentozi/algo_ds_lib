//
// Created by LengTouZai on 2025/9/16.
//
#pragma once
#include <unordered_map>
#include <unordered_set>

#include "tree/linked_binary_tree.h"
#include "base/queue_structure.h"
#include "base/stack_structure.h"

/**
 * @brief 构造函数，初始化二叉树名称。
 * @tparam T 节点数据类型
 * @param name 二叉树的名称
 */
template<typename T>
BinaryTree<T>::BinaryTree(std::string name) : TreeStructure<T>(name) {}

/**
 * @brief 析构函数，释放二叉树资源。
 * @tparam T 节点数据类型
 */
template<typename T>
BinaryTree<T>::~BinaryTree() {
    // 非递归的后序遍历删除所有节点
    if (!root) return;
    StackStructure<BinaryTreeNode<T>*>* stack = new SqStack<BinaryTreeNode<T>*>("postorder_stack");
    StackStructure<BinaryTreeNode<T>*>* output = new SqStack<BinaryTreeNode<T>*>("postorder_output");
    // 先将根节点入栈
    stack->push(root);
    while (!stack->empty()) {
        BinaryTreeNode<T>* node;
        // 弹出栈顶节点并将其推入输出栈，该节点在其的子节点之后被处理
        stack->pop(node);
        output->push(node);
        // 先左孩子入栈后右孩子入栈，以保证左子树先被处理（因为要出栈并推入输出栈，所以这里入栈和访问顺序是一致的）
        if (node->left) {
            stack->push(node->left);
        }
        if (node->right) {
            stack->push(node->right);
        }
    }

    // 输出栈中的节点顺序即为后序遍历顺序
    while (!output->empty()) {
        BinaryTreeNode<T>* node;
        output->pop(node);
        delete node;
    }
    delete stack;
    delete output;
}

/**
 * @brief 根据输入的树数据构建二叉树。
 * @tparam T 节点数据类型
 * @param tree 包含节点值及其子节点的向量，子节点用 std::optional 表示。
 * @throws std::invalid_argument 如果某个节点的子节点数量不是 2。
 */
template<typename T>
void BinaryTree<T>::build_tree(std::vector<std::pair<T, std::vector<std::optional<T>>>> tree) {
    // 如果输入的树为空，直接将根节点设为 nullptr
    if (tree.empty()) {
        root = nullptr;
        return;
    }

    // 创建所有节点并存储在哈希表中
    std::unordered_map<T, BinaryTreeNode<T>*> node_map;
    for (const auto& [value, _] : tree) {
        node_map[value] = new BinaryTreeNode<T>(value);
    }

    // 建立父子关系
    std::unordered_set<T> children;
    for (const auto& [value, children_values] : tree) {
        BinaryTreeNode<T>* parent = node_map[value];
        if (children_values.size() != 2) {
            throw std::invalid_argument("Binary tree node must have exactly two children (use nullopt for missing children).");
        }
        // 连接子节点
        parent->left = children_values[0].has_value() ? node_map[children_values[0].value()] : nullptr;
        parent->right = children_values[1].has_value() ? node_map[children_values[1].value()] : nullptr;

        // 记录子节点
        for (const auto& child_value : children_values) {
            if (child_value.has_value()) {
                children.insert(child_value.value());
            }
        }
    }

    // 根节点是没有父节点的节点
    for (const auto& [value, _] : tree) {
        if (children.find(value) == children.end()) {
            root = node_map[value];
            break;
        }
    }
}

/**
 * @brief 打印二叉树的名称。
 * @tparam T 节点数据类型
 */
template<typename T>
void BinaryTree<T>::print() const {
    std::cout << this->name << std::endl;
}

/**
 * @brief 获取二叉树的根节点。
 * @tparam T 节点数据类型
 * @return 指向根节点的指针。
 */
template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::get_root() const {
    return root;
}

/**
 * @brief 非递归实现的前序遍历。
 * @tparam T 节点数据类型
 */
template<typename T>
void BinaryTree<T>::preorder_traversal() const {
    // 非递归的前序遍历
    if (!root) return;
    StackStructure<BinaryTreeNode<T>*>* stack = new SqStack<BinaryTreeNode<T>*>("preorder_stack");
    stack->push(root);
    while (!stack->empty()) {
        BinaryTreeNode<T>* node;
        stack->pop(node);
        std::cout << node->data << " ";
        // 先右孩子入栈后左孩子入栈，以保证左子树先被处理
        if (node->right) {
            stack->push(node->right);
        }
        if (node->left) {
            stack->push(node->left);
        }
    }
    std::cout << std::endl;
    delete stack;
}

/**
 * @brief 非递归实现的中序遍历。
 * @tparam T 节点数据类型
 */
template<typename T>
void BinaryTree<T>::inorder_traversal() const {
    // 非递归的中序遍历
    if (!root) return;
    StackStructure<BinaryTreeNode<T>*>* stack = new SqStack<BinaryTreeNode<T>*>("inorder_stack");
    BinaryTreeNode<T>* current = root;
    while (current || !stack->empty()) {
        // 遍历将左孩子全部入栈
        while (current) {
            stack->push(current);
            current = current->left;
        }
        // 左孩子为空时，弹出栈顶节点并访问，然后处理右孩子
        BinaryTreeNode<T>* node;
        stack->pop(node);
        std::cout << node->data << " ";
        current = node->right;
    }
    std::cout << std::endl;
    delete stack;
}

/**
 * @brief 非递归实现的后序遍历。
 * @tparam T 节点数据类型
 */
template<typename T>
void BinaryTree<T>::postorder_traversal() const {
    // 非递归的后序遍历
    if (!root) return;
    StackStructure<BinaryTreeNode<T>*>* stack = new SqStack<BinaryTreeNode<T>*>("postorder_stack");
    StackStructure<BinaryTreeNode<T>*>* output = new SqStack<BinaryTreeNode<T>*>("postorder_output");
    // 先将根节点入栈
    stack->push(root);
    while (!stack->empty()) {
        BinaryTreeNode<T>* node;
        // 弹出栈顶节点并将其推入输出栈，该节点在其的子节点之后被处理
        stack->pop(node);
        output->push(node);
        // 先左孩子入栈后右孩子入栈，以保证左子树先被处理（因为要出栈并推入输出栈，所以这里入栈和访问顺序是一致的）
        if (node->left) {
            stack->push(node->left);
        }
        if (node->right) {
            stack->push(node->right);
        }
    }

    // 输出栈中的节点顺序即为后序遍历顺序
    while (!output->empty()) {
        BinaryTreeNode<T>* node;
        output->pop(node);
        std::cout << node->data << " ";
    }
    std::cout << std::endl;
    delete stack;
    delete output;
}

/**
 * @brief 层序遍历二叉树。
 * @tparam T 节点数据类型
 */
template<typename T>
void BinaryTree<T>::levelorder_traversal() const {
    // 层序遍历
    if (!root) return;
    QueueStructure<BinaryTreeNode<T>*>* queue = new SqQueue<BinaryTreeNode<T>*>("levelorder_queue");
    queue->enqueue(root);
    while (!queue->empty()) {
        BinaryTreeNode<T>* node;
        queue->dequeue(node);
        std::cout << node->data << " ";
        if (node->left) {
            queue->enqueue(node->left);
        }
        if (node->right) {
            queue->enqueue(node->right);
        }
    }
    std::cout << std::endl;
    delete queue;
}

/**
 * @brief 将二叉树转换为森林。
 * @tparam T 节点数据类型
 * @note 该方法尚未实现。
 */
template<typename T>
void BinaryTree<T>::to_forest() const {
    // TODO 实现将二叉树转换为森林的功能
    std::cout << root == nullptr ? "nullptr" : root->data << " ";
}

/**
 * @brief 将二叉树转换为线索二叉树。
 * @tparam T 节点数据类型
 * @note 该方法尚未实现。
 */
template<typename T>
LinkedBinaryTree<T>* BinaryTree<T>::to_linked_binary_tree(TraverseType type) const {
    // 将二叉树转换为线索二叉树
    auto* linked_binary_tree = new LinkedBinaryTree<T>("linked_binary_tree");
    linked_binary_tree->build_tree(root, type);
    return linked_binary_tree;
}