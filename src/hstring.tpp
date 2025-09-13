//
// Created by LengTouZai on 2025/9/13.
//
#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>

inline HString::HString(const char *data, const size_t length) {
    this->_length = length;
    this->data = new char[length + 1];
    std::copy_n(data, length, this->data);
    this->data[length] = '\0';
}

inline HString::HString(const HString &other)  : StringStructure(other) {
    this->_length = other._length;
    this->data = new char[_length + 1];
    std::copy_n(other.data, _length, this->data);
    this->data[_length] = '\0';
}

inline HString& HString::operator=(const HString &other) {
    if (this != &other) {
        delete[] this->data;
        this->_length = other._length;
        this->data = new char[_length + 1];
        std::copy_n(other.data, _length, this->data);
        this->data[_length] = '\0';
    }
    return *this;
}

inline HString::~HString() {
    delete[] data;
}

inline void HString::assign(const StringStructure &other) {
    const auto* other_hstring = dynamic_cast<const HString*>(&other);
    if (other_hstring == nullptr) {
        throw std::invalid_argument("Incompatible string type for assignment");
    }
    delete[] this->data;
    this->_length = other_hstring->_length;
    this->data = new char[_length + 1];
    std::copy_n(other_hstring->data, _length, this->data);
    this->data[_length] = '\0';
}

inline void HString::concat(const StringStructure &other) {
    const auto* other_hstring = dynamic_cast<const HString*>(&other);
    if (other_hstring == nullptr) {
        throw std::invalid_argument("Incompatible string type for concatenation");
    }
    const auto new_data = new char[this->_length + other_hstring->_length + 1];
    std::copy_n(this->data, this->_length, new_data);
    std::copy_n(other_hstring->data, other_hstring->_length, new_data + this->_length);
    new_data[this->_length + other_hstring->_length] = '\0';
    delete[] this->data;
    this->data = new_data;
    this->_length += other_hstring->_length;
}

inline void HString::substring(const int pos, const int length, StringStructure &result) const {
    if (pos < 0 || length < 0 || pos + length > static_cast<int>(this->_length)) {
        throw std::out_of_range("Substring position or length is out of range");
    }
    const auto sub_data = new char[length + 1];
    std::copy_n(this->data + pos, length, sub_data);
    sub_data[length] = '\0';
    auto* sub_string = dynamic_cast<HString*>(&result);
    if (sub_string == nullptr) {
        throw std::invalid_argument("Incompatible string type for substring result");
    }
    delete[] sub_string->data;
    sub_string->data = sub_data;
    sub_string->_length = length;
}

inline size_t HString::size() const {
    return this->_length;
}

inline bool HString::empty() const {
    return this->_length == 0;
}

inline int HString::index(const StringStructure &pattern, const int start_pos) const {
    const auto *pattern_hstring = dynamic_cast<const HString*>(&pattern);
    int i =start_pos, j = 0;
    while (i < this->_length && j < pattern.size()) {
        if (this->data[i] != pattern_hstring->data[j]) {
            i = i - j + 1;
            j = 0;
        } else {
            i++; j++;
        }
    }
    if (j == pattern.size())
        return i - j;
    return -1;
}

inline int HString::kmp_index(const StringStructure &pattern, const int start_pos) const {
    const auto *pattern_hstring = dynamic_cast<const HString*>(&pattern);
    // 计算模式串的部分匹配表
    if (pattern_hstring == nullptr) {
        throw std::invalid_argument("Incompatible string type for KMP pattern");
    }
    const int m = static_cast<int>(pattern_hstring->_length);
    if (m == 0) return start_pos <= static_cast<int>(this->_length) ? start_pos : -1;
    const auto next_val = new int[m];
    next_val[0] = -1;
    if (m > 1) {
        next_val[1] = 0;
        for (int i = 2; i < m; ++i) {
            int target_val = next_val[i - 1];
            // 寻找最长相同前后缀
            while (target_val != -1 && pattern_hstring->data[i - 1] != pattern_hstring->data[target_val]) {
                target_val = next_val[target_val];
            }
            // 找到最长相同前后缀则长度加 1，否则为 0
            next_val[i] = target_val + 1;

            // KMP 优化
            if (pattern_hstring->data[i] == pattern_hstring->data[next_val[i]]) {
                next_val[i] = next_val[next_val[i]];
            }
        }
    }

    // KMP 匹配
    int i = start_pos, j = 0;
    while (i < static_cast<int>(this->_length) && j < m) {
        if (this->data[i] == pattern_hstring->data[j]) {
            i++; j++;
        } else {
            j = next_val[j];
            if (j == -1) {
                i++; j++;
            }
        }
    }

    delete[] next_val;
    if (i == static_cast<int>(this->_length) && j < m) {
        return -1;
    }
    return i - j;
}

inline void HString::print() const {
    std::cout << this->name << " (Length: " << this->_length << "): " << (this->data ? this->data : "") << std::endl;
}
