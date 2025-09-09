#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class ExpandList {
private:
      T* data;
      size_t capacity;

      void expand(size_t min_capacity) {
            size_t new_capacity = std::max(capacity * 2, min_capacity);
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < capacity; ++i) {
                  new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
      }

public:
      ExpandList(size_t initial_capacity = 4)
            : capacity(initial_capacity), data(new T[initial_capacity]) {
      }

      ~ExpandList() {
            delete[] data;
      }

      T& operator[](size_t index) {
            if (index >= capacity) {
                  std::cout << "expand list" << std::endl;
                  expand(index + 1);
            }
            return data[index];
      }

      const T& operator[](size_t index) const {
            if (index >= capacity) {
                  throw std::out_of_range("Index out of range");
            }
            return data[index];
      }

      size_t get_capacity() const {
            return capacity;
      }
};
