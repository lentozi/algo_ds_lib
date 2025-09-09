#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
LinkList<T>::LinkList(std::string name) {
	head = static_cast<SingleNode<T> *>(malloc(sizeof(SingleNode<T>))); // 创建头节点，分配内存
	if (!head) {
		throw std::bad_alloc();
	}
	head->next = nullptr;
	this->name = name;
	this->length = 0;
}

template <typename T>
LinkList<T>::~LinkList() {
	SingleNode<T>* current = head;
	while (current) {
		SingleNode<T>* next = current->next;
		free(current);
		current = next;
	}
}

template <typename T>
void LinkList<T>::insert(const int index, const T& value) {
	if (index < 0 || index > length) {
		throw std::out_of_range("Index out of range");
	}
	SingleNode<T>* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	auto* new_node = static_cast<SingleNode<T> *>(malloc(sizeof(SingleNode<T>)));
	if (!new_node) {
		throw std::bad_alloc();
	}
	new_node->data = value;
	new_node->next = current->next;
	current->next = new_node;
	++length;
}

template <typename T>
void LinkList<T>::remove(const int index, T& value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	SingleNode<T>* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	SingleNode<T>* to_delete = current->next;
	value = to_delete->data;
	current->next = to_delete->next;
	free(to_delete);
	--length;
}

template <typename T>
T& LinkList<T>::at(const int index) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	SingleNode<T>* current = head->next;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template <typename T>
int LinkList<T>::locate(const T& value) const {
	SingleNode<T>* current = head->next;
	int index = 0;
	while (current) {
		if (current->data == value) {
			return index;
		}
		current = current->next;
		++index;
	}
	return -1;
}

template <typename T>
bool LinkList<T>::empty() const {
	return length == 0;
}

template <typename T>
size_t LinkList<T>::size() const {
	return length;
}

template <typename T>
void LinkList<T>::print() const {
	SingleNode<T>* current = head->next;
	std::cout << this->name << " (Length: " << length << "): ";
	while (current) {
		std::cout << *current << " ";
		current = current->next;
	}
}

template <typename T>
void LinkList<T>::insert_next_node(SingleNode<T>* node, const T& value) {
	if (!node) {
		throw std::invalid_argument("Node is null");
	}
	auto* new_node = static_cast<SingleNode<T> *>(malloc(sizeof(SingleNode<T>)));
	if (!new_node) {
		throw std::bad_alloc();
	}
	new_node->data = value;
	new_node->next = node->next;
	node->next = new_node;
	++length;
}

// 插入节点的下一个节点，时间复杂度O(1)
template <typename T>
void LinkList<T>::insert_prior_node(SingleNode<T>* node, const T& value) {
	if (!node || node == head) {
		throw std::invalid_argument("Node is null or head");
	}
	auto* new_node = static_cast<SingleNode<T> *>(malloc(sizeof(SingleNode<T>)));
	if (!new_node) {
		throw std::bad_alloc();
	}
	new_node->data = node->data;
	new_node->next = node->next;
	node->data = value;
	node->next = new_node;
	++length;
}

// 删除指定节点，时间复杂度O(1)，删除的是下一个节点，需要先找到前一个节点，时间复杂度O(n)
template <typename T>
void LinkList<T>::delete_node(SingleNode<T>* node, T& value) {
	if (!node || node == head) {
		throw std::invalid_argument("Node is null, head, or last node");
	}
	// 删除指定节点，时间复杂度O(1)，删除的是下一个节点，需要先找到前一个节点，时间复杂度O(n)
	if (node->next) {
		node->value = node->next->data;
		SingleNode<T>* to_delete = node->next;
		node->next = to_delete->next;
		value = to_delete->data;
		free(to_delete);
	}
	else {
		// 删除的是最后一个节点，需要先找到前一个节点
		SingleNode<T>* current = head;
		while (current->next && current->next != node) {
			current = current->next;
		}
		if (current->next == node) {
			current->next = nullptr;
			free(node);
		}
		else {
			throw std::invalid_argument("Node not found in the list");
		}
	}
}

template <typename T>
SingleNode<T>* LinkList<T>::find_node(const int index) const {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	SingleNode<T>* current = head->next;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	return current;
}