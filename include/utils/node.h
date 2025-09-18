#pragma once
#include <ostream>

template<typename T>
class Node {
public:
    class SingleNode {
    public:
        T data;
        SingleNode *next;

        explicit SingleNode(const T &value) : data(value), next(nullptr) {}

        friend std::ostream &operator<<(std::ostream &os, const SingleNode &node) {
            os << "SingleNode(data: " << node.data << ")";
            return os;
        }
    };

    class DoubleNode {
    public:
        T data;
        DoubleNode *prev;
        DoubleNode *next;

        explicit DoubleNode(const T &value) : data(value), prev(nullptr), next(nullptr) {}

        friend std::ostream &operator<<(std::ostream &os, const DoubleNode &node) {
            os << "DoubleNode(data: " << node.data << ")";
            return os;
        }
    };

    class ParentTreeNode {
    public:
        T data;
        int parent_index;

        explicit ParentTreeNode() : parent_index(0) {}
        explicit ParentTreeNode(const T &value) : data(value), parent_index(-1) {}

        friend std::ostream &operator<<(std::ostream &os, const ParentTreeNode &node) {
            os << "ParentTreeNode(data: " << node.data << ", parent_index: " << node.parent_index << ")";
            return os;
        }
    };

    class TreeNode {
    protected:
        T data;

    public:
        explicit TreeNode(const T &value) : data(value) {}

        T get_data() const {
            return data;
        }

        friend std::ostream &operator<<(std::ostream &os, const TreeNode &node) {
            os << "TreeNode(data: " << node.data << ")";
            return os;
        }
    };

    class BinaryTreeNode : public TreeNode {
    public:
        BinaryTreeNode *left;
        BinaryTreeNode *right;

        explicit BinaryTreeNode(const T &value) : TreeNode(value), left(nullptr), right(nullptr) {}

        friend std::ostream &operator<<(std::ostream &os, const BinaryTreeNode &node) {
            os << "BinaryTreeNode(data: " << node.data << ")";
            return os;
        }
    };

    class LinkedTreeNode : public BinaryTreeNode {
    public:
        int ltag = 0; // 左标志，0 表示孩子节点，1 表示线索
        int rtag = 0; // 右标志，0 表示孩子节点，1 表示线索

        explicit LinkedTreeNode(const T &value, const int ltag = 0, const int rtag = 0)
            : BinaryTreeNode(value), ltag(ltag), rtag(rtag) {}

        friend std::ostream &operator<<(std::ostream &os, const LinkedTreeNode &node) {
            os << "LinkedTreeNode(data: " << node.data << ", ltag: " << node.ltag << ", rtag: " << node.rtag << ")";
            return os;
        }
    };
};