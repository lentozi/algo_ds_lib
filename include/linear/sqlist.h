#pragma once

#include <string>


template <typename T>
class SqList : public LinearStructure<T> {
private:
	T* data;			// �洢���Ա�Ԫ�ص�����
	size_t length;		// ��ǰ���Ա���
	size_t capacity;		// ��ǰ���Ա�����

public:
	SqList(std::string name, size_t initial_capacity = 10);
	~SqList();
	void insert(int index, const T& value) override;
	void remove(int index, T& value) override;
	T& at(int index) override;
	int locate(const T& value) const override;
	bool empty() const override;
	size_t size() const override;
	void print() const override;
};

#include "sqlist.tpp"
