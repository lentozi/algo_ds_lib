//
// Created by LengTouZai on 2025/9/19.
//
#pragma once

#include <string>
#include <utility>

template<typename T>
class SetStructure {
protected:
    std::string name = "set_structure";

    virtual void print() const = 0;

public:
    explicit SetStructure(std::string name) : name(std::move(name)) {}
    virtual ~SetStructure() = default;

    friend std::ostream &operator<<(std::ostream &os, const SetStructure<T> &set) {
        set.print();
        return os;
    }
};

#include "set/union_find_set.h"