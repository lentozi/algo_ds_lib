//
// Created by LengTouZai on 2025/9/19.
//
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "base/tree_structure.h"

TEST(HuffmanTreeTest, BuildAndEncodeDecode) {
    // 构建一个简单的哈夫曼树，严格遵循左子树频率小于右子树频率的规则以保证唯一性
    // 字符及其频率
    const std::vector<std::pair<char, int>> frequency = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    TreeStructure<char>* tree = new HuffmanTree("HuffmanTree", frequency);

    // 测试编码
    const std::string encoded = dynamic_cast<HuffmanTree<char>*>(tree)->encode({'a', 'b', 'c', 'd', 'e', 'f'});
    EXPECT_FALSE(encoded.empty());
    EXPECT_EQ(encoded, "110011011001011110"); // 计算得到的编码应该是 110011011001011110

    // 测试解码
    std::vector<char> decoded = dynamic_cast<HuffmanTree<char>*>(tree)->decode(encoded);
    EXPECT_EQ(decoded, std::vector({'a', 'b', 'c', 'd', 'e', 'f'}));

    // 测试 WPL
    EXPECT_EQ(dynamic_cast<HuffmanTree<char>*>(tree)->wpl(), 224); // 计算得到的 WPL 应该是 224

    delete tree;
}