#pragma once
#include "utils/node.h"

template <typename T>
using DoubleNode = typename Node<T>::DoubleNode;

// 双端链表
template <typename T>
class DLinkList : public LinearStructure<T> {
private:
	DoubleNode<T>* head;		// 头指针
	size_t length = 0;		// 当前线性表长度
	void print() const override;

public:
	DLinkList(std::string name);
	~DLinkList();
	void insert(int index, const T& value) override;
	void remove(int index, T& value) override;
	T& at(int index) override;
	int locate(const T& value) const override;
	bool empty() const override;
	size_t size() const override;
	// 后插操作
	void insert_next_node(DoubleNode<T>* node, const T& value);
	// 前插操作
	void insert_prior_node(DoubleNode<T>* node, const T& value);
	// 指定节点删除
	void delete_node(DoubleNode<T>* node, T& value);
	// 查找指定节点
	DoubleNode<T>* find_node(int index) const;
};

#include "dlinklist.tpp"