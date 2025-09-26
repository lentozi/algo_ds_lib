//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
class BinarySearch final : public SearchAlgorithm<T> {
public:
    explicit BinarySearch(LinearStructure<T>* linear_structure);
    BinarySearch(const BinarySearch&) = delete;
    ~BinarySearch() override;
    int search(const T& element) const override;
};

#include "binary_search.tpp"
