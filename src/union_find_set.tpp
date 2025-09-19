//
// Created by LengTouZai on 2025/9/19.
//
#pragma once

template<typename T>
UnionFindSet<T>::UnionFindSet(std::string name) : SetStructure<T>(name) {
    elements = new ExpandList<std::pair<T, int>>(10);
}

template<typename T>
UnionFindSet<T>::~UnionFindSet() {
    delete elements;
}

template<typename T>
void UnionFindSet<T>::make_set(const std::vector<T> &value) {
    elements->clear();
    for (int i = 0; i < value.size(); ++i) {
        (*elements)[i] = std::make_pair(value.at(i), -1);
    }
    this->_size = value.size();
}

template<typename T>
void UnionFindSet<T>::insert(const T &value) {
    for (int i = 0; i < this->_size; ++i) {
        if ((*elements)[i].first == value) {
            return;
        }
    }
    (*elements)[this->_size] = std::make_pair(value, -1);
    ++this->_size;
}

template<typename T>
T UnionFindSet<T>::find_root(const T &value) const {
    for (int i = 0; i < this->_size; ++i) {
        if ((*elements)[i].first == value) {
            int index = i;
            while ((*elements)[index].second >= 0) {
                index = (*elements)[index].second;
            }
            // 优化 Find 算法，将查找的路径上的节点直接连接到根节点
            int root_index = index;
            index = i;
            while ((*elements)[index].second >= 0 && (*elements)[index].second != root_index) {
                index = (*elements)[index].second;
                (*elements)[index].second = root_index;
            }
            return (*elements)[root_index].first;
        }
    }
    throw std::invalid_argument("Value not found in the set");
}

template<typename T>
void UnionFindSet<T>::union_set(const T &value1, const T &value2) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < this->_size; ++i) {
        if ((*elements)[i].first == value1) {
            index1 = i;
        }
        if ((*elements)[i].first == value2) {
            index2 = i;
        }
    }
    if (index1 == -1 || index2 == -1) {
        throw std::invalid_argument("One or both values not found in the set");
    }

    // 找到 value1 的根节点索引
    int root1 = index1;
    while ((*elements)[root1].second >= 0) {
        root1 = (*elements)[root1].second;
    }

    // 找到 value2 的根节点索引
    int root2 = index2;
    while ((*elements)[root2].second >= 0) {
        root2 = (*elements)[root2].second;
    }

    // 如果两个根节点不同，则进行合并，将 root2 合并到 root1，需要确保 root2 是秩较小的树
    if (root1 != root2) {
        if ((*elements)[root2].second < (*elements)[root1].second) {
            // root2 的秩更大，交换 root1 和 root2
            std::swap(root1, root2);
        }
        // 更新 root1 的秩（负数表示树的高度）
        (*elements)[root1].second += (*elements)[root2].second;
        // 将 root2 的父节点设为 root1，实现合并
        (*elements)[root2].second = root1;
    }
}

template<typename T>
int UnionFindSet<T>::size() const {
    return _size;
}

template<typename T>
bool UnionFindSet<T>::empty() const {
    return _size == 0;
}

template<typename T>
void UnionFindSet<T>::print() const {
    std::cout << this->name << std::endl;
    for (int i = 0; i < this->_size; ++i) {
        std::cout << "Element: " << (*elements)[i].first << ", Parent Index: " << (*elements)[i].second << std::endl;
    }
}

template<typename T>
void UnionFindSet<T>::clear() {
    elements->clear();
    this->_size = 0;
}