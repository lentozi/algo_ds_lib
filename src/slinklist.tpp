#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
SLinkList<T>::SLinkList(std::string name, size_t initial_capacity)
	: length(0), capacity(initial_capacity) {
	if (initial_capacity == 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	static_list = (StaticNode*)malloc(initial_capacity * sizeof(StaticNode));
	if (!static_list) {
		throw std::bad_alloc();
	}
	static_list[0].valid = false;
	static_list[0].next = -1;
	this->name = name;
}

template <typename T>
SLinkList<T>::~SLinkList() {
	free(static_list);
}

template <typename T>
void SLinkList<T>::insert(int index, const T& value) {
	if (index < 0 || index > length) {
		throw std::out_of_range("Index out of range");
	}
	if (length >= capacity) {
		// 扩容
		capacity *= 2;
		StaticNode* new_list = (StaticNode*)std::malloc(capacity * sizeof(StaticNode));
		if (!new_list) {
			throw std::bad_alloc();
		}
		for (size_t i = 0; i < length; ++i) {
			new_list[i] = static_list[i];
		}
		free(static_list);
		static_list = new_list;
	}

	// 查询可插入的位置
	int valid_index = 0;
	for (valid_index = 0; valid_index < capacity; ++valid_index) {
		if (static_list[valid_index].valid) break;
	}

	if (valid_index < 0 || valid_index > capacity) {
		throw std::out_of_range("No valid index");
	}

	// 查询第 index 个数据
	int prev_index = 0;
	for (int i = 0; i < index; ++i) {
		prev_index = static_list[prev_index].next;
	}

	static_list[valid_index].data = value;
	static_list[valid_index].valid = false;
	static_list[valid_index].next = static_list[prev_index].next;
	static_list[prev_index].next = valid_index;
	++length;
}

template <typename T>
void SLinkList<T>::remove(int index, T& value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}

	// 查找待删除节点的前一个节点
	int prev_index = 0;
	for (int i = 0; i < index - 1; ++i) {
		prev_index = static_list[prev_index].next;
	}
	int to_delete_index = static_list[prev_index].next;
	value = static_list[to_delete_index].data;
	static_list[to_delete_index].valid = true;
	static_list[prev_index].next = static_list[to_delete_index].next;
	--length;
}

template <typename T>
T& SLinkList<T>::at(int index) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}

	int link_index = static_list[0].next;
	for (int i = 0; i < index; ++i, link_index = static_list[link_index].next);
	return static_list[link_index].data;
}

template <typename T>
int SLinkList<T>::locate(const T& value) const {
	int range_index = 0;
	for (int i = 0; i < length && !static_list[range_index].valid; ++i) {
		range_index = static_list[range_index].next;
		if (static_list[range_index].data == value) return i;
	}
	return -1;
}

template <typename T>
bool SLinkList<T>::empty() const {
	return length == 0;
}

template <typename T>
size_t SLinkList<T>::size() const {
	return length;
}

template <typename T>
void SLinkList<T>::print() const {
	std::cout << this->name << " (Length: " << length << ", Capacity: " << capacity << "): ";
	int range_index = 0;
	for (int i = 0; i < length && !static_list[range_index].valid; ++i) {
		range_index = static_list[range_index].next;
		std::cout << static_list[range_index] << " ";
		if (static_list[range_index].next == -1) break;
	}
}