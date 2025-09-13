//
// Created by LengTouZai on 2025/9/13.
//
#pragma once

#include <string>

// 串结构基类
class StringStructure {
protected:
    std::string name = "string_structure";

    virtual void print() const = 0;

public:
    virtual ~StringStructure() = default;

    // 赋值
    virtual void assign(const StringStructure& other) = 0;

    // 拼接
    virtual void concat(const StringStructure& other) = 0;

    // 截取子串
    virtual void substring(int pos, int length, StringStructure& result) const = 0;

    // 获取长度
    [[nodiscard]] virtual size_t size() const = 0;

    // 是否为空
    [[nodiscard]] virtual bool empty() const = 0;

    // 朴素匹配子串
    [[nodiscard]] virtual int index(const StringStructure& pattern, int start_pos = 0) const = 0;

    // KMP匹配子串
    [[nodiscard]] virtual int kmp_index(const StringStructure& pattern, int start_pos = 0) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const StringStructure &s) {
        s.print();
        return os;
    }
};

#include "string/hstring.h"
