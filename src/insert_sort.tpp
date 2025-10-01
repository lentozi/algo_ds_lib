//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
InsertSort<T>::InsertSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

template<typename T>
void InsertSort<T>::sort(const bool asc) const {
    if (this->linear_structure->size() <= 2) {
        return;
    }
    for (int i = 2; i < this->linear_structure->size(); ++i) {
        // 设置哨兵
        this->linear_structure->set(0, this->linear_structure->at(i));
        if (asc) {
            // 正序
            int j;
            for (j = i - 1; this->linear_structure->at(j) >= this->linear_structure->at(0); --j) {
                // 移动后面的元素
                this->linear_structure->set(j + 1, this->linear_structure->at(j));
            }
            // 插入元素
            this->linear_structure->set(j + 1, this->linear_structure->at(0));
        } else {
            // 倒序
            int j;
            for (j = i - 1; this->linear_structure->at(j) <= this->linear_structure->at(0); --j) {
                // 移动后面的元素
                this->linear_structure->set(j + 1, this->linear_structure->at(j));
            }
            // 插入元素
            this->linear_structure->set(j + 1, this->linear_structure->at(0));
        }
    }
}
