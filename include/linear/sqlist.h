#pragma once

#include <string>
#include "utils/expand_list.h"


template<typename T>
class SqList final : public LinearStructure<T> {
	size_t length; // 当前线性表长度
	ExpandList<T> *data;

public:
	explicit SqList(std::string name, size_t initial_capacity = 10);

	~SqList() override;

	void insert(int index, const T &value) override;

	void remove(int index, T &value) override;

	T &at(int index) override;

	int locate(const T &value) const override;

	void set(int index, T value);

	[[nodiscard]] bool empty() const override;

	[[nodiscard]] size_t size() const override;

	void print() const override;
};

#include "sqlist.tpp"
