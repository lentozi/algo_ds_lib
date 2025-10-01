//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
BubbleSort<T>::BubbleSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

template<typename T>
void BubbleSort<T>::sort(bool asc) const {
    for (int i = 0; i < this->linear_structure->size() - 1; ++i) {
        bool flag = false;      // 表示此趟排序是否有元素改动
        for (int j = this->linear_structure->size() - 1; j > i; --j) {
            if ((asc && this->linear_structure->at(j - 1) > this->linear_structure->at(j))
                || (!asc && this->linear_structure->at(j - 1) < this->linear_structure->at(j))) {
                T temp = this->linear_structure->at(j);
                this->linear_structure->set(j, this->linear_structure->at(j - 1));
                this->linear_structure->set(j - 1, temp);
                flag = true;
            }
        }
        if (!flag) break;
    }
}
