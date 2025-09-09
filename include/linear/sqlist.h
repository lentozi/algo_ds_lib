#pragma once

#include <string>
#include "utils/expand_list.h"


template<typename T>
class SqList final : public LinearStructure<T> {
	// T* data;			// 存储线性表元素的数组
	size_t length; // 当前线性表长度
	// size_t capacity;		// 当前线性表容量
	ExpandList<T> *data;

public:
	explicit SqList(std::string name, size_t initial_capacity = 10);

	~SqList() override;

	void insert(int index, const T &value) override;

	void remove(int index, T &value) override;

	T &at(int index) override;

	int locate(const T &value) const override;

	[[nodiscard]] bool empty() const override;

	[[nodiscard]] size_t size() const override;

	void print() const override;
};

#include "sqlist.tpp"
