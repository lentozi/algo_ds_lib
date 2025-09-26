//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
class BinaryInsertSort final : public SortAlgorithm<T> {
public:
    explicit BinaryInsertSort(LinearStructure<T>* input_line);
    ~BinaryInsertSort() override = default;
    void sort(bool asc) const override;
};

#include "binary_insert_sort.tpp"