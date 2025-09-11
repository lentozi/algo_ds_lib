#pragma once
#include <string>

/**
 * 栈数据结构抽象类
 *
 * <p>
 * 栈：只允许一段进行插入或删除的线性表，具有后进先出的特性
 * <br/>
 * 栈的数学性质：当 n 个不同元素入栈时，出栈元素的不同排列个数为 $\frac{1}{n+1}C^{n}_{2n}$
 * </p>
 * @tparam T 数据元素类型
 */
template<typename T>
class StackStructure {
protected:
	std::string name = "stack_structure";

	virtual void print() const = 0;

public:
	virtual ~StackStructure() = default;

	// 将数据元素入栈
	virtual void push(const T &value) = 0;

	// 将数据元素出栈
	virtual void pop(T &value) = 0;

	// 获取栈顶元素
	virtual void get_top(T &value) const = 0;

	// 判断栈是否为空
	[[nodiscard]] virtual bool empty() const = 0;

	// 获取栈元素个数
	[[nodiscard]] virtual size_t size() const = 0;

	friend std::ostream &operator<<(std::ostream &os, const StackStructure &s) {
		s.print();
		return os;
	}
};

#include "stack/sqstack.h"