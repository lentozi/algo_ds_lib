//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

#include "base/linear_structure.h"

template<typename T>
class SeqSearch final : public SearchAlgorithm<T> {
public:
    explicit SeqSearch(LinearStructure<T>* linear_structure);
    SeqSearch(const SeqSearch&) = delete;
    ~SeqSearch() override;
    int search(const T& element) const override;
};

#include "seq_search.tpp"
