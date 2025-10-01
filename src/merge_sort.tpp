//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

// 表 [low...mid] 到 [mid+1...high] 各自有序，将两个表合并
template<typename T>
void merge(LinearStructure<T>* input_line, LinearStructure<T>* auxiliary, const int low, const int mid, const int high, bool asc) {
    for (int i = 0; i < input_line->size(); ++i) {
        auxiliary->set(i, input_line->at(i));       // 将原数组中所有元素复制到辅助数组中

    }
    int i, j, k;       // i 是第一个数组中的遍历索引，j 是第二个数组中的遍历索引，k 是最终数组的遍历索引
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; ++k) {
        if ((asc && auxiliary->at(i) <= auxiliary->at(j))
            || (!asc && auxiliary->at(i) >= auxiliary->at(j)))
            input_line->set(k, auxiliary->at(i++));
        else
            input_line->set(k, auxiliary->at(j++));
    }
    while (i <= mid) input_line->set(k++, auxiliary->at(i++));     // 若第一个表未检测完，直接复制
    while (j <= high) input_line->set(k++, auxiliary->at(j++));    // 若第二个表未检测完，直接复制
}

template<typename T>
void merge_sort(LinearStructure<T>* input_line, LinearStructure<T>* auxiliary, int low, int high, bool asc) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort<T>(input_line, auxiliary, low, mid, asc);
        merge_sort<T>(input_line, auxiliary, mid + 1, high, asc);
        merge(input_line, auxiliary, low, mid, high, asc);
    }
}

template<typename T>
MergeSort<T>::MergeSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {
    this->auxiliary = new SqList<T>("Auxiliary", input_line->size());
    for (int i = 0; i < input_line->size(); ++i) {
        this->auxiliary->insert(i, input_line->at(i));
    }
}

template<typename T>
MergeSort<T>::~MergeSort() {
    delete this->auxiliary;
}

template<typename T>
void MergeSort<T>::sort(bool asc) const {
    merge_sort(this->linear_structure, this->auxiliary, 0, this->linear_structure->size() - 1, asc);
}
