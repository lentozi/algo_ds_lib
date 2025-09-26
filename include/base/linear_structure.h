#pragma once
#include <string>

// LinearStructure 线性结构抽象类
template<typename T>
class LinearStructure {
protected:
	std::string name = "linear_structure";

	virtual void print() const = 0;

public:
	virtual ~LinearStructure() = default;

	virtual void insert(int index, const T &value) = 0;

	virtual void remove(int index, T &value) = 0;

	virtual T &at(int index) = 0;

	virtual int locate(const T &value) const = 0;

	virtual void set(int index, T value) = 0;

	[[nodiscard]] virtual bool empty() const = 0;

	[[nodiscard]] virtual size_t size() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const LinearStructure &s) {
		s.print();
		return os;
	}
};

#include "linear/sqlist.h"
#include "linear/linklist.h"
#include "linear/dlinklist.h"
#include "linear/slinklist.h"
