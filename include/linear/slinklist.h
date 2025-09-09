#pragma once
#include "utils/expand_list.h"

template<typename T>
class SLinkList final : public LinearStructure<T> {
	class StaticNode {
	public:
		T data;
		int next;
		bool valid;

		explicit StaticNode(const T &value = NULL) : data(value), next(-1), valid(true) {
		}

		friend std::ostream &operator<<(std::ostream &os, const StaticNode &node) {
			os << "StaticNode(data: " << node.data << ")";
			return os;
		}
	};

	ExpandList<StaticNode> *static_list;
	// StaticNode* static_list;			// 静态链表数组
	size_t length = 0; // 当前静态链表的长度
	// size_t capacity;
	void print() const override;

public:
	explicit SLinkList(std::string name, size_t initial_capacity = 10);

	~SLinkList() override;

	void insert(int index, const T &value) override;

	void remove(int index, T &value) override;

	T &at(int index) override;

	int locate(const T &value) const override;

	[[nodiscard]] bool empty() const override;

	[[nodiscard]] size_t size() const override;
};

#include "slinklist.tpp"
