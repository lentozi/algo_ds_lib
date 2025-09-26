//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
class InsertSort final : public SortAlgorithm<T> {
public:
    explicit InsertSort(LinearStructure<T>* input_line);
    ~InsertSort() override = default;
    void sort(bool asc) const override;
};

#include "insert_sort.tpp"