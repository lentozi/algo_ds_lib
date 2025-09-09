#pragma once
#include "sqlist.h"

template <typename T>
class SLinkList : public LinearStructure<T> {

private:
	class StaticNode {
	public:
		T data;
		int next;
		bool valid;

		StaticNode(const T& value) : data(value), next(-1), valid(true) {}

		friend std::ostream& operator<<(std::ostream& os, const StaticNode& node) {
			os << "StaticNode(data: " << node.data << ")";
			return os;
		}
	};

	StaticNode* static_list;			// 静态链表数组
	size_t length = 0;				// 当前静态链表的长度
	size_t capacity;
	void print() const override;

public:
	SLinkList(std::string name, size_t initial_capacity = 10);
	~SLinkList();
	void insert(int index, const T& value) override;
	void remove(int index, T& value) override;
	T& at(int index) override;
	int locate(const T& value) const override;
	bool empty() const override;
	size_t size() const override;
};

#include "slinklist.tpp"