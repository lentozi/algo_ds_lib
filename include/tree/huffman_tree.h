//
// Created by LengTouZai on 2025/9/19.
//
// 哈夫曼树
#pragma once

#include <string>

template<typename T>
using BinaryTreeNode = typename Node<T>::BinaryTreeNode;

template<typename T>
class HuffmanTree final : public TreeStructure<T> {
    // T 为字符类型，频率为 int
    BinaryTreeNode<std::pair<T, int>> *root = nullptr;
    std::unordered_map<T, std::string> huffman_table; // 存储字符对应的哈夫曼编码
    int _wpl = 0;
    void print() const override;

public:
    explicit HuffmanTree(std::string name, const std::vector<std::pair<T, int>> &frequency);
    ~HuffmanTree() override;

    BinaryTreeNode<T> *get_root() const;

    std::string encode(const std::vector<T> &data) const;
    std::vector<T> decode(const std::string &bit_string) const;

    [[nodiscard]] int wpl() const;
};

#include "huffman_tree.tpp"
