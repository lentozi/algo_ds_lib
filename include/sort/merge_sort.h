//
// Created by LengTouZai on 2025/10/1.
//
#pragma once

template<typename T>
class MergeSort final : public SortAlgorithm<T> {
private:
    LinearStructure<T>* auxiliary;
public:
    explicit MergeSort(LinearStructure<T>* input_line);
    ~MergeSort() override;
    void sort(bool asc) const override;
};

#include "merge_sort.tpp"