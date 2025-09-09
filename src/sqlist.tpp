#include <cstdlib>
#include <stdexcept>
#include <iostream>

template <typename T>
SqList<T>::SqList(std::string name, size_t initial_capacity)
    : length(0), capacity(initial_capacity) {
    if (initial_capacity == 0) {
	  throw std::invalid_argument("Initial capacity must be greater than 0");
    }
    data = (T*)std::malloc(capacity * sizeof(T));
    this->name = name;
}

template <typename T>
SqList<T>::~SqList() {
    free(data);
}

template <typename T>
void SqList<T>::insert(int index, const T& value) {
    if (index < 0 || index > length) {
	  throw std::out_of_range("Index out of range");
    }
    if (length >= capacity) {
	  // 扩容
	  capacity *= 2;
	  T* new_data = (T*)std::malloc(capacity * sizeof(T));
	  if (!new_data) {
		  throw std::bad_alloc();
	  }
	  for (size_t i = 0; i < length; ++i) {
		new_data[i] = data[i];
	  }
	  free(data);
	  data = new_data;
    }

    // �ƶ�Ԫ�����ڳ�λ��
    for (size_t i = length; i > index; --i) {
	  data[i] = data[i - 1];
    }

    // ������Ԫ��
    data[index] = value;
    ++length;
}

template <typename T>
void SqList<T>::remove(int index, T& value) {
    if (index < 0 || index >= length) {
	  throw std::out_of_range("Index out of range");
    }
    value = data[index];
    // �ƶ�Ԫ�������ȱ
    for (size_t i = index; i < length - 1; ++i) {
	  data[i] = data[i + 1];
    }
    --length;
}

template <typename T>
T& SqList<T>::at(int index) {
    if (index < 0 || index >= length) {
	  throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
int SqList<T>::locate(const T& value) const {
    for (int i = 0; i < length; ++i) {
	  if (data[i] == value) {
		return i;
	  }
    }
    return -1; // δ�ҵ�
}

template <typename T>
bool SqList<T>::empty() const {
    return length == 0;
}

template <typename T>
size_t SqList<T>::size() const {
    return length;
}

template <typename T>
void SqList<T>::print() const {
	std::cout << this->name << " (Length: " << length << ", Capacity: " << capacity << "): ";
	for (size_t i = 0; i < length; ++i) {
		std::cout << data[i] << " ";
	}
}