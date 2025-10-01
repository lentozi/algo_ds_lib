//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
class BubbleSort final : public SortAlgorithm<T> {
public:
    explicit BubbleSort(LinearStructure<T>* input_line);
    ~BubbleSort() override = default;
    void sort(bool asc) const override;
};

#include "bubble_sort.tpp"