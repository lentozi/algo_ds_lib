#pragma once
#include "utils/expand_list.h"

/**
 * 栈的顺序存储结构
 */
template <typename T>
class SqStack final : public StackStructure<T> {
	ExpandList<T>* data;		// 栈中元素
	int top = -1;			// 栈顶元素指针
	int max_size = -1;		// 栈最大长度，如果设置为 -1 则不做限制
	void print() const override;

public:
	explicit SqStack(std::string name, size_t initial_capacity = 10, int max_size = -1);
	~SqStack() override;

	/**
	 * 将新元素压入栈
	 *
	 * <p>
	 * top指针初始时为 -1，在入栈元素时先 +1 再赋值，核心逻辑：<code>data[++top] = value;</code>
	 * <br/>
	 * 需判断栈是否已满，核心逻辑：<code>is_full = top == max_size - 1;</code>
	 * </p>
	 * @param value 压入栈的元素
	 */
	void push(const T& value) override;

	/**
	 * 将元素出栈
	 *
	 * <p>
	 * top指针初始时为 -1，在出栈元素时先赋值再 -1，核心逻辑：<code>value = data[top--];</code>
	 * <br/>
	 * 需判断栈是否为空，核心逻辑：<code>is_empty = top == -1;</code>
	 * </p>
	 * @param value 出栈返回的元素
	 */
	void pop(T& value) override;

	/**
	 * 获取栈顶元素
	 *
	 * <p>
	 * top指针初始时为 -1，获取栈顶元素时直接返回 top 指向的元素，核心逻辑：<code>value = data[top];</code>
	 * </p>
	 * @param value 返回的栈顶元素
	 */
	void get_top(T& value) const override;

	/**
	 * 判断栈是否为空
	 *
	 * <p>
	 * top指针初始时为 -1，栈空时 top 仍为 -1，核心逻辑：<code>is_empty = top == -1;</code>
	 * </p>
	 * @return 返回栈是否为空
	 */
	[[nodiscard]] bool empty() const override;

	/**
	 * 获取栈中元素个数
	 *
	 * <p>
	 * top指针初始化时为 -1，栈中元素个数为 top + 1，核心逻辑：<code>size = top + 1;</code>
	 * </p>
	 * @return 返回栈中元素个数
	 */
	[[nodiscard]] size_t size() const override;
};

#include "sqstack.tpp"