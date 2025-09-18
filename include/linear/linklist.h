#pragma once
#include "utils/node.h"

template<typename T>
using SingleNode = typename Node<T>::SingleNode;

template<typename T>
class LinkList final : public LinearStructure<T> {
	SingleNode<T> *head; // 头指针
	size_t length = 0; // 当前线性表长度
	void print() const override;

public:
	explicit LinkList(std::string name);

	~LinkList() override;

	void insert(int index, const T &value) override;

	void remove(int index, T &value) override;

	T &at(int index) override;

	int locate(const T &value) const override;

	[[nodiscard]] bool empty() const override;

	[[nodiscard]] size_t size() const override;

	// 后插操作
	void insert_next_node(SingleNode<T> *node, const T &value);

	// 前插操作
	void insert_prior_node(SingleNode<T> *node, const T &value);

	// 指定节点删除
	void delete_node(SingleNode<T> *node, T &value);

	// 查找指定节点
	SingleNode<T> *find_node(int index) const;
};

#include "linklist.tpp"
