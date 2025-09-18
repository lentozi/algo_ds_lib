//
// Created by LengTouZai on 2025/9/17.
//
#pragma once

template<typename T>
LinkedBinaryTree<T>::LinkedBinaryTree(std::string name) {
    this->name = name;
    this->_traverse = TraverseType::PreOrder;
}

template<typename T>
LinkedBinaryTree<T>::~LinkedBinaryTree() = default;

template<typename T>
void LinkedBinaryTree<T>::print() const {
    std::cout << this->name << std::endl;
}

template<typename T>
void LinkedBinaryTree<T>::build_tree(BinaryTreeNode<T> *binary_root, TraverseType type) {
    if (type != TraverseType::InOrder && type != TraverseType::PreOrder) {
        throw std::invalid_argument("Only InOrder and PreOrder traversal types are supported for building threaded binary tree.");
    }
    this->_traverse = type;

    // 先复制一边二叉树的节点，复制为线索二叉树节点
    QueueStructure<BinaryTreeNode<T>*>* queue = new SqQueue<BinaryTreeNode<T>*>("tree_queue");
    QueueStructure<LinkedTreeNode<T>*>* linked_queue = new SqQueue<LinkedTreeNode<T>*>("linked_tree_queue");

    // 对二叉树层序遍历
    if (binary_root) queue->enqueue(binary_root);
    auto* linked_root = new LinkedTreeNode<T>(binary_root->get_data());
    linked_queue->enqueue(linked_root);
    while (!queue->empty() && !linked_queue->empty()) {
        BinaryTreeNode<T>* tree_node;
        LinkedTreeNode<T>* linked_tree_node;
        queue->dequeue(tree_node);
        linked_queue->dequeue(linked_tree_node);
        if (tree_node->left) {
            queue->enqueue(tree_node->left);
            linked_tree_node->left = new LinkedTreeNode<T>(tree_node->left->get_data());
            linked_queue->enqueue(static_cast<LinkedTreeNode<T> *>(linked_tree_node->left));
        }
        if (tree_node->right) {
            queue->enqueue(tree_node->right);
            linked_tree_node->right = new LinkedTreeNode<T>(tree_node->right->get_data());
            linked_queue->enqueue(static_cast<LinkedTreeNode<T> *>(linked_tree_node->right));
        }
    }

    this->root = linked_root;
    delete queue, linked_queue;

    // 再根据遍历类型建立线索
    auto* iterator = new TreeIterator<int>(linked_root, type);
    if (!iterator->has_next()) return;
    auto* prev = static_cast<LinkedTreeNode<T> *>(iterator->next());
    while (iterator->has_next()) {
        auto *next = static_cast<LinkedTreeNode<T> *>(iterator->next());
        if (type == TraverseType::InOrder) {
            // 中序线索二叉树
            if (next->left == nullptr) {
                next->ltag = 1; // 左指针是线索
                next->left = prev; // 指向前驱节点
            }
            if (prev && prev->right == nullptr) {
                prev->rtag = 1; // 右指针是线索
                prev->right = next; // 指向后继节点
            }
        } else {
            // 前序线索二叉树
            if (prev) {
                if (next->left == nullptr) {
                    next->ltag = 1; // 左指针是线索
                    next->left = prev; // 指向前驱节点
                }
                if (prev->right == nullptr) {
                    prev->rtag = 1; // 右指针是线索
                    prev->right = next; // 指向后继节点
                }
            }
        }
        prev = next;
    }

    reset_iterator();
}

template<typename T>
LinkedTreeNode<T>* LinkedBinaryTree<T>::begin() {
    return root;
}

template<typename T>
LinkedTreeNode<T>* LinkedBinaryTree<T>::end() {
    return _end;
}

template<typename T>
bool LinkedBinaryTree<T>::is_end() const {
    return _current == _end;
}

template<typename T>
void LinkedBinaryTree<T>::reset_iterator() {
    _current = root;
}

template<typename T>
LinkedTreeNode<T> *LinkedBinaryTree<T>::next() {
    if (!_current) return nullptr;
    if (this->_traverse == TraverseType::InOrder) {
        if (_current->rtag == 1) { // 右指针是线索
            _current = _current->right;
        } else { // 右指针是孩子节点，返回右子树的最左下节点
            _current = _current->right;
            while (_current && _current->ltag == 0) { // 一直沿左子树走到底
                _current = _current->left;
            }
        }
        return _current;
    }
    if (this->_traverse == TraverseType::PreOrder) {
        if (_current->ltag == 0) { // 左指针是孩子节点
            _current = _current->left;
        } else { // 右指针是孩子节点，或右指针是线索
            _current = _current->right;
        }
        return _current;
    }
    return nullptr;
}

