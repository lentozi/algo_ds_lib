//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

// 对第 k 个元素调整大根堆
template<typename T>
void MaxHeapAdjust(LinearStructure<T>* linear_structure, int k, const int size) {
    linear_structure->set(0, linear_structure->at(k));
    for (int i = 2 * k; i < size; i *= 2) {
        if (i < size - 1 && linear_structure->at(i) < linear_structure->at(i + 1)) {
            i++;
        }
        if (linear_structure->at(0) > linear_structure->at(i)) break;       // 筛选结束
        linear_structure->set(k, linear_structure->at(i));
        k = i;
    }
    linear_structure->set(k, linear_structure->at(0));
}

// 对第 k 个元素调整小根堆
template<typename T>
void MinHeapAdjust(LinearStructure<T>* linear_structure, int k, const int size) {
    linear_structure->set(0, linear_structure->at(k));
    for (int i = 2 * k; i < size; i *= 2) {
        if (i < size - 1 && linear_structure->at(i) > linear_structure->at(i + 1)) {
            i++;
        }
        if (linear_structure->at(0) < linear_structure->at(i)) break;
        linear_structure->set(k, linear_structure->at(i));
        k = i;
    }
    linear_structure->set(k, linear_structure->at(0));
}

template<typename T>
HeapSort<T>::HeapSort(LinearStructure<T> *input_line)
    : SortAlgorithm<T>(input_line) {}

template<typename T>
void HeapSort<T>::sort(const bool asc) const {
    // 堆排序要求第一个位置不存放元素
    if (this->linear_structure->size() <= 2) {
        return;
    }
    if (asc) {
        // 建立大根堆
        for (int i = this->linear_structure->size() / 2; i >= 1; --i) {
            MaxHeapAdjust(this->linear_structure, i, this->linear_structure->size());
        }

        // 交换堆顶元素并调整剩下的元素
        for (int i = this->linear_structure->size() - 1; i > 1; --i) {
            T temp = this->linear_structure->at(i);
            this->linear_structure->set(i, this->linear_structure->at(1));
            this->linear_structure->set(1, temp);
            MaxHeapAdjust(this->linear_structure, 1, i);
        }
    } else {
        // 建立小根堆
        for (int i = this->linear_structure->size() / 2; i >= 1; --i) {
            MinHeapAdjust(this->linear_structure, i, this->linear_structure->size());
        }

        // 交换堆顶元素并调整剩下的元素
        for (int i = this->linear_structure->size() - 1; i > 1; --i) {
            T temp = this->linear_structure->at(i);
            this->linear_structure->set(i, this->linear_structure->at(1));
            this->linear_structure->set(1, temp);
            MinHeapAdjust(this->linear_structure, 1, i);
        }
    }
}
