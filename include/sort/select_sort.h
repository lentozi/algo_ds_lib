//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
class SelectSort final : public SortAlgorithm<T> {
public:
    explicit SelectSort(LinearStructure<T>* input_line);
    ~SelectSort() override = default;
    void sort(bool asc) const override;
};

#include "select_sort.tpp"