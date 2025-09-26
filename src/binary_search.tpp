//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
BinarySearch<T>::BinarySearch(LinearStructure<T> *linear_structure)
    : SearchAlgorithm<T>(linear_structure) {}

template<typename T>
BinarySearch<T>::~BinarySearch() = default;

template<typename T>
int BinarySearch<T>::search(const T &element) const {
    int low = 0, high = this->linear_structure->size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (this->linear_structure->at(mid) == element) {
            return mid;
        }
        if (this->linear_structure->at(mid) > element) {
            high = mid - 1;
        } else if (this->linear_structure->at(mid) < element) {
            low = mid + 1;
        }
    }

    return -1;
}
