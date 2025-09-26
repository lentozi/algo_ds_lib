//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
InsertSort<T>::InsertSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

// TODO 这是选择排序！！！
// template<typename T>
// void InsertSort<T>::sort(bool asc) const {
//     for (int i = 0; i < this->linear_structure->size() - 1; ++i) {
//         int flag = i;
//         for (int j = i + 1; j < this->linear_structure->size(); ++j) {
//             // 正序时，从无序列表中找到最小的元素；倒序时，从无序列表中找到最大的元素
//             if ((asc && this->linear_structure->at(j) < this->linear_structure->at(flag))
//                 || (!asc && this->linear_structure->at(j) > this->linear_structure->at(flag))) {
//                 flag = j;
//             }
//         }
//         if (flag != i) {
//             T temp = this->linear_structure->at(i);
//             this->linear_structure->set(i, this->linear_structure->at(flag));
//             this->linear_structure->set(flag, temp);
//         }
//     }
// }
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
