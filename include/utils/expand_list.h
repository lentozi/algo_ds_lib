#pragma once
#include <cstdlib>
#include <iostream>

template <typename T>
class ExpandList {
private:
	T* data;
	size_t capacity;

public:
	ExpandList(size_t initial_capacity)
		: capacity(initial_capacity) {
		data = (T*)malloc(initial_capacity * sizeof(T));
	}

	~ExpandList() {
		free(data);
	}

	T& operator[](int index) {
		if (index < 0) {
			throw std::out_of_range("Index out of range");
		}
		// 扩容
		if (index >= capacity) {
			std::cout << "expand list" << std::endl;
			size_t new_capacity = capacity * 2;
			T* new_data = (T*)calloc(new_capacity, sizeof(T));
			for (int i = 0; i < capacity; ++i) {
				new_data[i] = data[i];
			}
			capacity = new_capacity;
			free(data);
			data = new_data;
		}
		return data[index];
	}
};