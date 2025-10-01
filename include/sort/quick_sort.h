//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
class QuickSort final : public SortAlgorithm<T> {
public:
    explicit QuickSort(LinearStructure<T>* input_line);
    ~QuickSort() override = default;
    void sort(bool asc) const override;
};

#include "quick_sort.tpp"