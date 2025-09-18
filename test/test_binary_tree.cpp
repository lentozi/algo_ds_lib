//
// Created by LengTouZai on 2025/9/16.
//
#include "base/tree_structure.h"
#include "gtest/gtest.h"

TEST(BinaryTreeTest, BuildAndTraverse) {
    BinaryTree<int> tree("TestTree");

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
    tree.build_tree(tree_data);

    // 测试前序遍历
    TreeIterator<int>* it = tree.get_iterator(TraverseType::PreOrder);
    std::vector<int> preorder_result;
    while (it->has_next()) {
        preorder_result.push_back(it->next()->get_data());
    }
    const std::vector expected_preorder = {1, 2, 4, 5, 3};
    EXPECT_EQ(preorder_result, expected_preorder);
    delete it;

    const LinkedBinaryTree<int>* binary_tree = tree.to_linked_binary_tree(TraverseType::PreOrder);
    // EXPECT_NE(binary_tree, nullptr);
    delete binary_tree;

    // 测试中序遍历
    it = tree.get_iterator(TraverseType::InOrder);
    std::vector<int> inorder_result;
    while (it->has_next()) {
        inorder_result.push_back(it->next()->get_data());
    }
    const std::vector expected_inorder = {4, 2, 5, 1, 3};
    EXPECT_EQ(inorder_result, expected_inorder);
    delete it;

    // 测试后序遍历
    it = tree.get_iterator(TraverseType::PostOrder);
    std::vector<int> postorder_result;
    while (it->has_next()) {
        postorder_result.push_back(it->next()->get_data());
    }
    const std::vector expected_postorder = {4, 5, 2, 3, 1};
    EXPECT_EQ(postorder_result, expected_postorder);
    delete it;

    // 测试层次遍历
    it = tree.get_iterator(TraverseType::LevelOrder);
    std::vector<int> levelorder_result;
    while (it->has_next()) {
        levelorder_result.push_back(it->next()->get_data());
    }
    const std::vector expected_levelorder = {1, 2, 3, 4, 5};
    EXPECT_EQ(levelorder_result, expected_levelorder);
    delete it;
}