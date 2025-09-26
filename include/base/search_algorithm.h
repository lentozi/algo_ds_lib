//
// Created by LengTouZai on 2025/9/26.
//
#pragma once
#include "linear_structure.h"

template<typename T>
class SearchAlgorithm {
protected:
    LinearStructure<T>* linear_structure;
public:
    explicit SearchAlgorithm(LinearStructure<T>* linear_structure) : linear_structure(linear_structure) {
        if (linear_structure->empty()) {
            throw std::runtime_error("LinearStructure is empty.");
        }
    }
    virtual ~SearchAlgorithm() = default;
    virtual int search(const T& element) const = 0;
};

#include "search/seq_search.h"