//
// Created by LengTouZai on 2025/9/26.
//
#pragma once
#include "linear_structure.h"

template<typename T>
class SortAlgorithm {
protected:
    LinearStructure<T>* linear_structure;

public:
    explicit SortAlgorithm(LinearStructure<T>* input_line) : linear_structure(input_line) {}
    virtual ~SortAlgorithm() = default;
    virtual void sort(bool asc) const = 0;
};

#include "sort/heap_sort.h"
#include "sort/quick_sort.h"
#include "sort/merge_sort.h"
#include "sort/insert_sort.h"
#include "sort/select_sort.h"
#include "sort/bubble_sort.h"
#include "sort/binary_insert_sort.h"