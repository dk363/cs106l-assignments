#pragma once
#include <stdexcept>

template <typename T>
class Box {
public:
    Box();                         // 默认构造
    Box(const T& value);           // 自定义构造
    ~Box();

    bool empty() const;            // 是否为空
    T getValue() const;            // getter
    void setValue(const T& another); // setter
    void clear();                  // 清空

private:
    bool _empty;
    T _value;
};
#include "class.cpp"
