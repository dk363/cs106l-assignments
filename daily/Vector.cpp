#include <stdexcept>

template <typename T>
Vector<T>::Vector() {
    _size = 0;
    _capacity = 4;
    _data = new T[_capacity];
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

template <typename T>
void Vector<T>::resize() {
    auto newData = new T[_capacity * 2];
    for (size_t i = 0; i < _size; ++i) {
        newData[i] = data[i];
    }
    delete[] _data;
    _capacity *= 2;
    _data = newData;
}

template <typename T>
void Vector<T>::push_back(const T& val) {
    if (_size == _capacity) {
        resize();
    }

    _data[size] = val;
    ++_size;
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("index out of range!");
    }

    return _data[index];
}

template <typename T> 
T& Vector<T>::operate[](size_t index) {
    return _data[index];
}

template <typename T>
size_t Vector<T>::size() {
    return _size;
}

template <typename T>
bool Vector<T>::empty() {
    return _size == 0;
}

template <typename T>
Vector<T>::iterator Vector<T>::begin() {
    return _data;
}

template <typename T>
Vector<T>::iterator Vector<T>::end() {
    return _data + _size;
}