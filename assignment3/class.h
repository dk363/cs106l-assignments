/* This line makes sure that if another file #includes Vector.h
 * more than once, it will be as if it included it only once.
 *
 * Multiple includes can happen if, for example, we #include Vector.h
 * and also #include another file that itself #includes Vector.h
 * 
 * #pragma once is technically not part of the C++ language, but is a
 * compiler extension that virtually all compilers support
 */
#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
  private:
  size_t _size;
  size_t _capacity;
  T* _data;

  void resize() {
    size_t newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < _size; ++i) {
        newData[i] = _data[i];
    }
    delete[] _data;
    _capacity = newCapacity;
    _data = newData;
}

public:
  using iterator = T*;

  Vector() : _size(0), _capacity(4), _data(new T[_capacity]) {}

  ~Vector()
  {
    delete[] _data;
  }

  void push_back(const T& value)
  {
    if (_size == _capacity) {
      resize();
    }

    _data[_size] = value;
    _size++;
  }

  T& at(size_t index)
  {
    if (index >= _size) 
    {
      throw std::out_of_range("out of range!");  
    }

    return _data[index];
  }

  T& operator[](size_t index)
  {
    return _data[index];
  }

  size_t size() const
  {
    return _size;
  }

  bool empty() const
  {
    return _size == 0;
  }

  iterator begin()
  {
    return _data;
  }

  iterator end()
  {
    return _data + _size;
  }

};
