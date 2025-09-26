#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
SLinkList<T>::SLinkList(std::string name, size_t initial_capacity) {
	if (initial_capacity == 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	static_list = new ExpandList<StaticNode>(initial_capacity);

	(*static_list)[0].valid = false;
	(*static_list)[0].next = -1;
	this->name = name;
}

template<typename T>
SLinkList<T>::~SLinkList() {
	delete static_list;
}

template<typename T>
void SLinkList<T>::insert(const int index, const T &value) {
	if (index < 0 || index > length) {
		throw std::out_of_range("Index out of range");
	}

	// 查询可插入的位置
	int valid_index = 0;
	for (valid_index = 0; valid_index < static_list->get_capacity(); ++valid_index) {
		if ((*static_list)[valid_index].valid) break;
	}

	if (valid_index < 0 || valid_index > static_list->get_capacity()) {
		throw std::out_of_range("No valid index");
	}

	// 查询第 index 个数据
	int prev_index = 0;
	for (int i = 0; i < index; ++i) {
		prev_index = (*static_list)[prev_index].next;
	}

	(*static_list)[valid_index].data = value;
	(*static_list)[valid_index].valid = false;
	(*static_list)[valid_index].next = (*static_list)[prev_index].next;
	(*static_list)[prev_index].next = valid_index;
	++length;
}

template<typename T>
void SLinkList<T>::remove(const int index, T &value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}

	// 查找待删除节点的前一个节点
	int prev_index = 0;
	for (int i = 0; i < index - 1; ++i) {
		prev_index = (*static_list)[prev_index].next;
	}
	int to_delete_index = (*static_list)[prev_index].next;
	value = (*static_list)[to_delete_index].data;
	(*static_list)[to_delete_index].valid = true;
	(*static_list)[prev_index].next = (*static_list)[to_delete_index].next;
	--length;
}

template<typename T>
T &SLinkList<T>::at(const int index) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}

	int link_index = (*static_list)[0].next;
	for (int i = 0; i < index; ++i, link_index = (*static_list)[link_index].next) {
	}
	return (*static_list)[link_index].data;
}

template<typename T>
void SLinkList<T>::set(const int index, T value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}

	int link_index = (*static_list)[0].next;
	for (int i = 0; i < index; ++i, link_index = (*static_list)[link_index].next) {
	}
	(*static_list)[link_index].data = value;
}


template<typename T>
int SLinkList<T>::locate(const T &value) const {
	int range_index = 0;
	for (int i = 0; i < length && !(*static_list)[range_index].valid; ++i) {
		range_index = (*static_list)[range_index].next;
		if ((*static_list)[range_index].data == value) return i;
	}
	return -1;
}

template<typename T>
bool SLinkList<T>::empty() const {
	return length == 0;
}

template<typename T>
size_t SLinkList<T>::size() const {
	return length;
}

template<typename T>
void SLinkList<T>::print() const {
	std::cout << this->name << " (Length: " << length << "): ";
	int range_index = 0;
	for (int i = 0; i < length && !(*static_list)[range_index].valid; ++i) {
		range_index = (*static_list)[range_index].next;
		std::cout << (*static_list)[range_index] << " ";
		if ((*static_list)[range_index].next == -1) break;
	}
}
