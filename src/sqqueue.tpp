//
// Created by LengTouZai on 2025/9/11.
//
#pragma once

template<typename T>
SqQueue<T>::SqQueue(std::string name, size_t initial_capacity, const int max_size)
    : max_size(max_size) {
    if (initial_capacity <= 0) {
        throw std::invalid_argument("initial capacity must be greater than 0");
    }
    data = new ExpandList<T>(initial_capacity);
    this->name = name;
}

template<typename T>
SqQueue<T>::~SqQueue() {
    delete data;
}

template<typename T>
void SqQueue<T>::enqueue(const T &value) {
    if (max_size != -1 && (rear + 1) % max_size == front && flag == 1) {
        throw std::out_of_range("queue is full");
    }
    if ((rear + 1) % data->get_capacity() == front && flag == 1) {
        rear = rear + 1;
    } else {
        rear = (rear + 1) % data->get_capacity();
    }
    (*data)[rear] = value;
    flag = 1;
}

template<typename T>
void SqQueue<T>::dequeue(T &value) {
    if ((rear + 1) % data->get_capacity() == front && this->flag == 0) {
        throw std::out_of_range("queue is empty");
    }
    value = (*data)[front];
    front = (front + 1) % data->get_capacity();
    flag = 0;
}

template<typename T>
void SqQueue<T>::get_front(T &value) const {
    if ((rear + 1) % data->get_capacity() == front && this->flag == 0) {
        throw std::out_of_range("queue is empty");
    }
    value = (*data)[front];
}

template<typename T>
bool SqQueue<T>::empty() const {
    return (rear + 1) % data->get_capacity() == front && this->flag == 0;
}

template<typename T>
size_t SqQueue<T>::size() const {
    if ((rear + 1) % data->get_capacity() == front)
        return flag * data->get_capacity();
    return (rear - front + data->get_capacity() + 1) % data->get_capacity();
}

template<typename T>
void SqQueue<T>::print() const {
    std::cout << this->name << " (Length: " << size() << "): ";
    if (empty()) {
        std::cout << "empty";
        return;
    }
    int index = front;
    std::cout << (*data)[index] << "(front) ";
    index = (index + 1) % data->get_capacity();
    while (index != rear) {
        std::cout << (*data)[index] << " ";
        index = (index + 1) % data->get_capacity();
    }
    std::cout << (*data)[rear] << "(rear)";
}
