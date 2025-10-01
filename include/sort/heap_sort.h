//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
class HeapSort final : public SortAlgorithm<T> {
public:
    explicit HeapSort(LinearStructure<T>* input_line);
    ~HeapSort() override = default;
    void sort(bool asc) const override;
};

#include "heap_sort.tpp"