#pragma once
#include <string>

// 栈数据结构抽象类
template <typename T>
class StackStructure {
protected:
	std::string name = "stack_structure";
	virtual void print() const = 0;

public:
	virtual ~StackStructure() = default;
	// 将数据元素入栈
	virtual void push(const T& value) = 0;
	// 将数据元素出栈
	virtual void pop(T& value) = 0;
	// 获取栈顶元素
	virtual void get_top(T& value) = 0;
	// 判断栈是否为空
	virtual bool empty() const = 0;
	// 获取栈元素个数
	virtual size_t size() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const StackStructure<T>& s) {
		s.print();
		return os;
	}
};