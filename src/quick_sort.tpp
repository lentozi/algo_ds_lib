//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
int quick_sort_partition(LinearStructure<T>* input_line, int low, int high) {
    T pivot = input_line->at(low);     // 将当前表中第一个元素设置为枢纽
    while (low < high) {
        while (low < high && input_line->at(high) >= pivot) --high;
        input_line->set(low, input_line->at(high));
        while (low < high && input_line->at(low) <= pivot) ++low;
        input_line->set(high, input_line->at(low));
    }
    input_line->set(low, pivot);
    return low;
}

template<typename T>
int quick_sort_partition_desc(LinearStructure<T>* input_line, int low, int high) {
    T pivot = input_line->at(low);
    while (low < high) {
        while (low < high && input_line->at(high) <= pivot) --high;
        input_line->set(low, input_line->at(high));
        while (low < high && input_line->at(low) >= pivot) ++low;
        input_line->set(high, input_line->at(low));
    }
    input_line->set(low, pivot);
    return low;
}

template<typename T>
void quick_sort(LinearStructure<T>* input_line, int low, int high) {
    if (low < high) {
        const int pivot_pos = quick_sort_partition(input_line, low, high);
        // 依次对两个子表进行递归排序
        quick_sort(input_line, low, pivot_pos - 1);
        quick_sort(input_line, pivot_pos + 1, high);
    }
}

template<typename T>
void quick_sort_desc(LinearStructure<T>* input_line, int low, int high) {
    if (low < high) {
        const int pivot_pos = quick_sort_partition_desc(input_line, low, high);
        // 依次对两个子表进行递归排序
        quick_sort(input_line, low, pivot_pos - 1);
        quick_sort(input_line, pivot_pos + 1, high);
    }
}

template<typename T>
QuickSort<T>::QuickSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

template<typename T>
void QuickSort<T>::sort(bool asc) const {
    if (asc) {
        quick_sort(this->linear_structure, 0, this->linear_structure->size() - 1);
    } else {
        quick_sort_desc(this->linear_structure, 0, this->linear_structure->size() - 1);
    }
}
