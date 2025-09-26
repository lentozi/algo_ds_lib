//
// Created by LengTouZai on 2025/9/26.
//
#pragma once

template<typename T>
SeqSearch<T>::SeqSearch(LinearStructure<T>* linear_structure)
    : SearchAlgorithm<T>(linear_structure) {}

template<typename T>
SeqSearch<T>::~SeqSearch() = default;

template<typename T>
int SeqSearch<T>::search(const T& element) const {
    this->linear_structure->set(0, element);
    int i;
    for (i = this->linear_structure->size(); this->linear_structure->at(--i) != element;) {}
    return i;
}
