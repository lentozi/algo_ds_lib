//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
BinaryInsertSort<T>::BinaryInsertSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {
}

template<typename T>
void BinaryInsertSort<T>::sort(const bool asc) const {
    if (this->linear_structure->size() <= 2) {
        return;
    }
    for (int i = 2; i < this->linear_structure->size(); ++i) {
        // 设置哨兵
        this->linear_structure->set(0, this->linear_structure->at(i));
        // 正序
        int low = 0, high = i - 1;
        // 进行折半查找
        if (asc) {
            while (low <= high) {
                if (int mid = (low + high) / 2; this->linear_structure->at(mid) <= this->linear_structure->at(0)) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        } else {
            while (low <= high) {
                if (int mid = (low + high) / 2; this->linear_structure->at(mid) >= this->linear_structure->at(0)) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        // 插入到 high + 1 的位置
        for (int j = i; j > high + 1; --j) {
            // 移动后面的元素
            this->linear_structure->set(j, this->linear_structure->at(j - 1));
        }
        this->linear_structure->set(high + 1, this->linear_structure->at(0));
    }
}
