//
// Created by LengTouZai on 2025/9/13.
//
#pragma once

class HString final : public StringStructure {
    char* data = nullptr; // 串数据
    size_t _length = 0; // 串长度
    void print() const override;

public:
    explicit HString(const char* data, size_t length);
    HString() = default;
    HString(const HString& other);
    HString& operator=(const HString& other);
    ~HString() override;

    void assign(const StringStructure& other) override;
    void concat(const StringStructure& other) override;
    void substring(int pos, int length, StringStructure& result) const override;
    [[nodiscard]] size_t size() const override;
    [[nodiscard]] bool empty() const override;
    [[nodiscard]] int index(const StringStructure& pattern, int start_pos) const override;
    [[nodiscard]] int kmp_index(const StringStructure& pattern, int start_pos) const override;
};

#include "hstring.tpp"