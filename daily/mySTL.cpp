#include <memory>
#include <stdexcept>
#include <utility>

template<typename T, typename Alloc = std::allocator<T>>
class SimpleVector {  // Fixed class name
public:
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    SimpleVector()
        : _data(nullptr), _size(0), _capacity(0), _alloc(Alloc()) {}  // Fixed nullptr typo


    explicit SimpleVector(size_type n, const T& value = T())
        : _data(nullptr), _size(0), _capacity(0), _alloc(Alloc())
    {
        reserve(n);
        for (size_type i = 0; i < n; i++) {
            push_back(value);
        }
    }

    // Copy constructor
    SimpleVector(const SimpleVector& other)
        : _data(nullptr), _size(0), _capacity(0), _alloc(other._alloc) {
        reserve(other._size);
        for (size_type i = 0; i < other._size; ++i) {
            push_back(other._data[i]);
        }
    }

    // Copy assignment
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            clear();
            reserve(other._size);
            for (size_type i = 0; i < other._size; ++i) {
                push_back(other._data[i]);
            }
        }
        return *this;
    }

    // Move constructor
    SimpleVector(SimpleVector&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity), _alloc(std::move(other._alloc)) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // Move assignment
    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this != &other) {
            clear();
            if (_data) {
                _alloc.deallocate(_data, _capacity);
            }
            
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            _alloc = std::move(other._alloc);
            
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    ~SimpleVector() {
        clear();
        if (_data) {
            _alloc.deallocate(_data, _capacity);
        }
    }

    reference operator[](size_type i) {
        return _data[i];
    }

    const_reference operator[](size_type i) const {  // Fixed typo cosnt -> const
        return _data[i];
    }

    reference at(size_type i) {
        if (i >= _size) {
            throw std::out_of_range("SimpleVector::at index out of range");
        }
        return _data[i];
    }

    const_reference at(size_type i) const {
        if (i >= _size) {
            throw std::out_of_range("SimpleVector::at index out of range");
        }
        return _data[i];
    }

    size_type size() const {
        return _size;
    }

    size_type capacity() const {
        return _capacity;
    }

    bool empty() const {  // Added const qualifier
        return _size == 0;
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            grow();
        }
        _alloc.construct(_data + _size, value);
        ++_size;
    } 

    void pop_back() {
        if (_size == 0) {
            throw std::out_of_range("SimpleVector::pop_back out of range");
        }

        --_size;  // Fixed _size() to _size
        _alloc.destroy(_data + _size);
    }

    void reserve(size_type new_cap) {
        if (new_cap <= _capacity) return;
        
        pointer new_data = _alloc.allocate(new_cap);
        size_type constructed = 0;
        
        try {
            // 迁移旧元素
            for (size_type i = 0; i < _size; ++i) {
                _alloc.construct(new_data + i, std::move_if_noexcept(_data[i]));
                constructed++;
            }
        } catch (...) {
            // Cleanup if construction fails
            // 销毁已将构造好的元素
            for (size_type i = 0; i < constructed; ++i) {
                _alloc.destroy(new_data + i);
            }
            // 释放新分配的元素
            _alloc.deallocate(new_data, new_cap);
            // 抛出异常 让上一层处理
            throw;
        }

        // Destroy old elements
        for (size_type i = 0; i < _size; ++i) {
            _alloc.destroy(_data + i);
        }

        if (_data) {
            _alloc.deallocate(_data, _capacity);
        }
        
        _data = new_data;
        _capacity = new_cap;
    }

    void clear() {
        for (size_type i = 0; i < _size; ++i) {
            _alloc.destroy(_data + i);
        }
        _size = 0;
    }

private:
    pointer _data;
    size_type _size;
    size_type _capacity;
    allocator_type _alloc;

    void grow() {
        size_type new_cap = _capacity == 0 ? 1 : _capacity * 2;
        reserve(new_cap);
    }
};