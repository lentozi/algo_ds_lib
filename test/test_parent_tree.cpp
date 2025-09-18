//
// Created by LengTouZai on 2025/9/18.
//

#include "gtest/gtest.h"
#include "base/tree_structure.h"

TEST(ParentTreeTest, ParentTreeBuildAndFind) {
    TreeStructure<int>* tree = new ParentTree<int>("parent_tree");

    // 构建一个简单的二叉树
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    const std::vector<std::pair<int, std::vector<std::optional<int>>>> tree_data = {
        {1, {2, 3}},
        {2, {4, 5}},
        {3, {std::nullopt, std::nullopt}},
        {4, {std::nullopt, std::nullopt}},
        {5, {std::nullopt, std::nullopt}}
    };
    dynamic_cast<ParentTree<int>*>(tree)->build_tree(tree_data);

    EXPECT_EQ(dynamic_cast<ParentTree<int>*>(tree)->get_root(), 1);
    EXPECT_THROW(dynamic_cast<ParentTree<int>*>(tree)->find_parent(1), std::invalid_argument); // 根节点没有父节点
    EXPECT_EQ(dynamic_cast<ParentTree<int>*>(tree)->find_parent(2), 1);
    EXPECT_EQ(dynamic_cast<ParentTree<int>*>(tree)->find_parent(3), 1);
    EXPECT_THROW(dynamic_cast<ParentTree<int>*>(tree)->find_parent(8), std::invalid_argument); // 节点 8 没有在树中
    EXPECT_EQ(dynamic_cast<ParentTree<int>*>(tree)->find_parent(5), 2); // 节点 5 的父节点是 4

    delete tree;
}