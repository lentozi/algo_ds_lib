#pragma once
#include <stdexcept>
#include <iostream>

template<typename T>
SqList<T>::SqList(std::string name, size_t initial_capacity)
	: length(0) {
	if (initial_capacity == 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	data = new ExpandList<T>(initial_capacity);
	this->name = name;
}

template<typename T>
SqList<T>::~SqList() {
	delete data;
}

template<typename T>
void SqList<T>::insert(int index, const T &value) {
	if (index < 0 || index > length) {
		throw std::out_of_range("Index out of range");
	}

	for (size_t i = length; i > index; --i) {
		(*data)[i] = (*data)[i - 1];
	}

	(*data)[index] = value;
	++length;
}

template<typename T>
void SqList<T>::remove(int index, T &value) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	value = (*data)[index];

	for (size_t i = index; i < length - 1; ++i) {
		(*data)[i] = (*data)[i + 1];
	}
	--length;
}

template<typename T>
T &SqList<T>::at(int index) {
	if (index < 0 || index >= length) {
		throw std::out_of_range("Index out of range");
	}
	return (*data)[index];
}

template<typename T>
int SqList<T>::locate(const T &value) const {
	for (int i = 0; i < length; ++i) {
		if ((*data)[i] == value) {
			return i;
		}
	}
	return -1;
}

template<typename T>
bool SqList<T>::empty() const {
	return length == 0;
}

template<typename T>
size_t SqList<T>::size() const {
	return length;
}

template<typename T>
void SqList<T>::print() const {
	std::cout << this->name << " (Length: " << length << "): ";
	for (size_t i = 0; i < length; ++i) {
		std::cout << (*data)[i] << " ";
	}
}
