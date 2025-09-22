#include "class.h"

template <typename T>
Box<T>::Box() {
    _empty = true;   // 默认是空的
}

template <typename T>
Box<T>::Box(const T& value) {
    _empty = false;
    _value = value;
}

template <typename T>
Box<T>::~Box() {}

template <typename T>
bool Box<T>::empty() const {
    return _empty;
}

template <typename T>
T Box<T>::getValue() const {
    if (_empty) {
        throw std::runtime_error("Attempted to access value from an empty Box!");
    }
    return _value;
}

template <typename T>
void Box<T>::setValue(const T& another) {
    _value = another;
    _empty = false;   // 设置后不再为空
}

template <typename T>
void Box<T>::clear() {
    _empty = true;
}
