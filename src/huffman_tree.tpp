//
// Created by LengTouZai on 2025/9/19.
//
#pragma once
#include "base/stack_structure.h"

template<typename T>
HuffmanTree<T>::HuffmanTree(std::string name, const std::vector<std::pair<T, int> > &frequency)
    : TreeStructure<T>(name) {
    // 初始化叶节点 TODO 用小根堆进行优化
    std::vector<BinaryTreeNode<std::pair<T, int> > *> nodes;
    for (int i = 0; i < frequency.size(); i++) {
        nodes.push_back(new BinaryTreeNode<std::pair<T, int>>(frequency[i]));
    }

    int min_index, second_min_index;
    while (nodes.size() > 1) {
        min_index = 0, second_min_index = 1;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->get_data().second < nodes[min_index]->get_data().second) {
                if (nodes[min_index]->get_data().second < nodes[second_min_index]->get_data().second) {
                    second_min_index = min_index;
                }
                if (i == second_min_index) {
                    // 需要将 second_min_index 和 min_index 互换位置
                    second_min_index = min_index;
                }
                min_index = i;
            } else if (nodes[i]->get_data().second < nodes[second_min_index]->get_data().second && i != min_index) {
                second_min_index = i;
            }
        }

        auto* parent = new BinaryTreeNode<std::pair<T, int>>(std::make_pair('\0', nodes[min_index]->get_data().second + nodes[second_min_index]->get_data().second));
        parent->left = nodes[min_index];
        parent->right = nodes[second_min_index];
        // nodes.erase(nodes.begin() + min_index);
        // nodes.erase(nodes.begin() + second_min_index);
        // nodes.erase(nodes.begin() + std::max(min_index, second_min_index));
        // nodes.erase(nodes.begin() + std::min(min_index, second_min_index));
        if (min_index > second_min_index) {
            nodes.erase(nodes.begin() + min_index);
            nodes.erase(nodes.begin() + second_min_index);
        } else {
            nodes.erase(nodes.begin() + second_min_index);
            nodes.erase(nodes.begin() + min_index);
        }
        nodes.push_back(parent);
    }

    root = nodes.front();
    nodes.pop_back();

    // 构建哈夫曼编码表
    // 进行二叉树的先序遍历访问各个叶节点
    StackStructure<BinaryTreeNode<std::pair<T, int>>*>* stack = new SqStack<BinaryTreeNode<std::pair<T, int>>*>("huffman_stack");
    StackStructure<std::string>* path_stack = new SqStack<std::string>("huffman_path_stack");

    if (!root) return;
    stack->push(root);
    path_stack->push("");
    while (!stack->empty()) {
        BinaryTreeNode<std::pair<T, int>>* node;
        stack->pop(node);
        std::string path;
        path_stack->pop(path);

        // 访问 node 节点
        if (!node->left && !node->right) {
            // 叶节点，存储编码
            huffman_table[node->get_data().first] = path;
            _wpl += node->get_data().second * path.length();
        }
        if (node->right) {
            stack->push(node->right);
            path_stack->push(path + "1");
        }
        if (node->left) {
            stack->push(node->left);
            path_stack->push(path + "0");
        }
    }
    delete stack;
}

template<typename T>
HuffmanTree<T>::~HuffmanTree() {
    // 非递归的后序遍历删除所有节点
    if (!root) return;
    StackStructure<BinaryTreeNode<std::pair<T, int>>*>* stack = new SqStack<BinaryTreeNode<std::pair<T, int>>*>("postorder_stack");
    StackStructure<BinaryTreeNode<std::pair<T, int>>*>* output = new SqStack<BinaryTreeNode<std::pair<T, int>>*>("postorder_output");
    // 先将根节点入栈
    stack->push(root);
    while (!stack->empty()) {
        BinaryTreeNode<std::pair<T, int>>* node;
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
        BinaryTreeNode<std::pair<T, int>>* node;
        output->pop(node);
        delete node;
    }
    delete stack;
    delete output;
}

template<typename T>
BinaryTreeNode<T> *HuffmanTree<T>::get_root() const {
    return root;
}

template<typename T>
std::string HuffmanTree<T>::encode(const std::vector<T> &data) const {
    std::string output;
    for (const auto& ch : data) {
        if (huffman_table.find(ch) == huffman_table.end()) {
            throw std::invalid_argument("Character not in Huffman table");
        }
        output += huffman_table.at(ch);
    }
    return output;
}

template<typename T>
std::vector<T> HuffmanTree<T>::decode(const std::string &bit_string) const {
    std::vector<T> output;
    BinaryTreeNode<std::pair<T, int>>* current = root;
    for (const char& bit : bit_string) {
        if (!current->left && !current->right) {
            // 叶节点，输出字符并回到根节点
            output.push_back(current->get_data().first);
            current = root;
        }
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            throw std::invalid_argument("Invalid bit in bit string");
        }
    }
    output.push_back(current->get_data().first);
    return output;
}

template<typename T>
int HuffmanTree<T>::wpl() const {
    return _wpl;
}

template<typename T>
void HuffmanTree<T>::print() const {
    std::cout << this->name << " (WPL: " << _wpl << ")\n";
    for (const auto& [ch, code] : huffman_table) {
        std::cout << ch << ": " << code << "\n";
    }
}