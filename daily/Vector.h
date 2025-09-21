#pragma once

#include <cstddef> 

template <typename T>
class Vector {
public:
    using iterator = T*;

    Vector();
    ~Vector();

    void push_back();

    T& at(size_t index) const;
    T& operator[](size_t index);

    size_t size() const;
    bool empty() const;

    iterator begin();
    iterator end();
private:
    size_t _size;
    size_t _capacity;
    iterator _data;

    void resize();
};

#include "Vector.cpp"
