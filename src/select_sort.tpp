//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
SelectSort<T>::SelectSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

template<typename T>
void SelectSort<T>::sort(bool asc) const {
    for (int i = 0; i < this->linear_structure->size() - 1; ++i) {
        int flag = i;
        for (int j = i + 1; j < this->linear_structure->size(); ++j) {
            // 正序时，从无序列表中找到最小的元素；倒序时，从无序列表中找到最大的元素
            if ((asc && this->linear_structure->at(j) < this->linear_structure->at(flag))
                || (!asc && this->linear_structure->at(j) > this->linear_structure->at(flag))) {
                flag = j;
            }
        }
        if (flag != i) {
            T temp = this->linear_structure->at(i);
            this->linear_structure->set(i, this->linear_structure->at(flag));
            this->linear_structure->set(flag, temp);
        }
    }
}
