#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
DLinkList<T>::DLinkList(std::string name) {
	head = static_cast<DoubleNode<T> *>(malloc(sizeof(DoubleNode<T>)));
	if (!head) {
		throw std::bad_alloc();
	}
	head->next = nullptr;
	head->prev = nullptr;
	this->name = name;
	this->length = 0;
}

template <typename T>
DLinkList<T>::~DLinkList() {
	DoubleNode<T>* current = head;
	while (current) {
		DoubleNode<T>* next = current->next;
		free(current);
		current = next;
	}
}

template <typename T>
void DLinkList<T>::insert(const int index, const T& value) {
	if (index < 0 || index > length) {
		throw std::out_of_range("Index out of range");
	}
	DoubleNode<T>* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	// 在 current 后插入新节点
	if (!current) {
		throw std::out_of_range("Index out of range");
	}
	auto* node = static_cast<DoubleNode<T> *>(malloc(sizeof(DoubleNode<T>)));
	if (!node) {
		throw std::bad_alloc();
	}
	node->data = value;
	node->prev = current;
	node->next = current->next;
	if (node->next) {
		node->next->prev = node;
	}
	current->next = node;
	++length;
}

template <typename T>
void DLinkList<T>::remove(const int index, T& value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	DoubleNode<T>* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	DoubleNode<T>* to_delete = current->next;
	if (!to_delete) {
		throw std::out_of_range("Index out of range");
	}
	current->next = to_delete->next;
	// current->next 可能为空
	if (current->next) {
		current->next->prev = current;
	}
	value = to_delete->data;
	free(to_delete);
	--length;
}

template <typename T>
T& DLinkList<T>::at(const int index) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	DoubleNode<T>* current = head->next;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->data;
}

template <typename T>
int DLinkList<T>::locate(const T& value) const {
	DoubleNode<T>* current = head->next;
	for (int i = 0; current != nullptr && i < length; current = current->next, ++i) {
		if (current->data == value) {
			return i;
		}
	}
	return -1;
}

template <typename T>
bool DLinkList<T>::empty() const {
	return length == 0;
}

template <typename T>
size_t DLinkList<T>::size() const {
	return length;
}

template <typename T>
void DLinkList<T>::print() const {
	DoubleNode<T>* current = head->next;
	std::cout << this->name << " (Length: " << length << "): ";
	while (current) {
		std::cout << *current << " ";
		current = current->next;
	}
}

template <typename T>
void DLinkList<T>::insert_next_node(DoubleNode<T>* node, const T& value) {
	auto* current = static_cast<DoubleNode<T> *>(malloc(sizeof(DoubleNode<T>)));
	current->data = value;
	current->prev = node;
	current->next = node->next;
	if (current->next) {
		current->next->prev = current;
	}
	node->next = current;
	++length;
}

template <typename T>
void DLinkList<T>::insert_prior_node(DoubleNode<T>* node, const T& value) {
	auto* current = static_cast<DoubleNode<T> *>(malloc(sizeof(DoubleNode<T>)));
	if (!current) {
		throw std::bad_alloc();
	}
	current->data = value;
	current->next = node;
	current->prev = node->prev;
	// 前面有头节点，一定不会为 nullptr
	current->prev->next = current;
	node->prev = current;
	++length;
}

template <typename T>
void DLinkList<T>::delete_node(DoubleNode<T>* node, T& value) {
	DoubleNode<T>* prior = node->prev;
	value = node->data;
	prior->next = node->next;
	if (prior->next) {
		prior->next->prev = prior;
	}
	free(node);
	--length;
}

template <typename T>
DoubleNode<T>* DLinkList<T>::find_node(const int index) const {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	DoubleNode<T>* current = head->next;
	for (int i = 0; i < index; ++i, current = current->next) {}
	return current;
}