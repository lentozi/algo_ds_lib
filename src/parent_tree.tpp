//
// Created by LengTouZai on 2025/9/18.
//
#pragma once
#include <unordered_set>

template<typename T>
ParentTree<T>::ParentTree(std::string name) : TreeStructure<T>(name), _size(0) {
    parent_table = new ExpandList<ParentTreeNode<T>>(10);
}

template<typename T>
ParentTree<T>::~ParentTree() {
    delete parent_table;
}

template<typename T>
void ParentTree<T>::build_tree(std::vector<std::pair<T, std::vector<std::optional<T>>>> tree) {
    // 如果输入的树为空，直接将根节点设为 nullptr
    if (tree.empty()) {
        parent_table->clear();
        return;
    }
    parent_table->clear();
    // 先创建所有节点
    auto* unordered_node = new std::unordered_set<T>();
    for (const auto& [value, children_list] : tree) {
        unordered_node->insert(value);
        for (const auto& child : children_list) {
            if (child.has_value()) {
                unordered_node->insert(child.value());
            }
        }
    }

    for (const auto& value : *unordered_node) {
    }
    for (int i = 0; i < unordered_node->size(); ++i) {
        (*parent_table)[i] = ParentTreeNode<T>(*(std::next(unordered_node->begin(), i)));
    }

    this->_size = unordered_node->size();
    delete unordered_node;

    // 再设置父节点索引
    for (const auto& [value, children_list] : tree) {
        // 查找父节点索引
        int parent_index = -1;
        for (int i = 0; i < this->_size; ++i) {
            if ((*parent_table)[i].data == value) {
                parent_index = i;
                break;
            }
        }
        for (const auto& child : children_list) {
            if (child.has_value()) {
                // 查找子节点索引
                for (int j = 0; j < this->_size; ++j) {
                    if ((*parent_table)[j].data == child.value()) {
                        // 设置父索引
                        (*parent_table)[j].parent_index = parent_index;
                        break;
                    }
                }
            }
        }
    }
}

template<typename T>
void ParentTree<T>::print() const {
    std::cout << this->name << std::endl;
    for (int i = 0; i < this->_size; ++i) {
        const auto& node = (*parent_table)[i];
        std::cout << node << std::endl;
    }
}

template<typename T>
T ParentTree<T>::get_root() const {
    if (this->_size == 0)
        throw std::runtime_error("The tree is empty.");
    for (int i = 0; i < this->_size; ++i) {
        if ((*parent_table)[i].parent_index == -1) {
            return (*parent_table)[i].data;
        }
    }
    throw std::runtime_error("No root found.");
}

template<typename T>
T ParentTree<T>::find_parent(T value) const {
    for (int i = 0; i < this->_size; ++i) {
        if ((*parent_table)[i].data == value) {
            int parent_index = (*parent_table)[i].parent_index;
            if (parent_index == -1) {
                // 根节点没有父节点
                throw std::invalid_argument("The node is the root and has no parent.");
            }
            return (*parent_table)[parent_index].data;
        }
    }
    throw std::invalid_argument("Value not found in the tree.");
}