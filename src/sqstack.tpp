#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
SqStack<T>::SqStack(std::string name, size_t initial_capacity, const int max_size)
	: max_size(max_size) {
	if (initial_capacity == 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	data = new ExpandList<T>(initial_capacity);
	this->name = name;
}

template <typename T>
SqStack<T>::~SqStack() {
	delete data;
}

template <typename T>
void SqStack<T>::push(const T& value) {
	if (top + 1 == max_size) {
		throw std::out_of_range("Stack is full");
	}
	(*data)[++top] = value;
}

template <typename T>
void SqStack<T>::pop(T& value) {
	if (top == -1) {
		throw std::out_of_range("Stack is empty");
	}
	value = (*data)[top--];
}

template <typename T>
void SqStack<T>::get_top(T& value) const {
	if (top == -1) {
		throw std::out_of_range("Stack is empty");
	}
	value = (*data)[top];
}

template <typename T>
bool SqStack<T>::empty() const {
	return top == -1;
}

template <typename T>
size_t SqStack<T>::size() const {
	return top + 1;
}

template <typename T>
void SqStack<T>::print() const {
	std::cout << this->name << " (Length: " << top + 1 << "): ";
	for (size_t i = 0; i < top; ++i) {
		std::cout << (*data)[i] << " ";
	}
	std::cout << (*data)[top] << "(top)";
}