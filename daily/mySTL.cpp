template<typename T, typename Alloc = std::allocator<T>>
class SimpleVector {
public:
    using value_type = T;
    using allocator_type = Alloc;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    SimpleVector()
        : _data(nullptr), _size(0), _capacity(0), _alloc(Alloc()) {}


    /**
     * 禁止构造函数/转换函数被编译器隐式调用，只能显式写出来。
     * 避免误用：比如 std::vector<int> v(5); 表示“长度为 5 的 vector”，
     * 如果构造函数不是 explicit，就可能因为 vector v = 5; 
     * 被误解成“一个元素为 5 的 vector”。
     * 增强可读性：让读代码的人能一眼看出转换是有意为之
     */
    explicit SimpleVector(size_type n, const T& value = T())
        : _data(nullptr), _size(0), _capacity(0), _alloc(Alloc())
    {
        reserve(n);
        for (size_type i = 0; i < n; i++) {
            push_back(value);
        }
    }

    ~SimpleVector() {
        /**
         * 在 cpp 中 内存使用分为两步
         * 分配内存
         * 构造对象
         * 同样的 释放也要分为两步
         * 销毁对象 
         * 释放内存
         * 所以这里我们先销毁对象 然后释放内存
         */
        for (size_type i = 0; i < _size(); i++) {
            _alloc.destroy(_data + i);
        }
        if (_data) {
            _alloc.deallocate(_data, _capacity);
        }
    }

    reference operator[](size_type i) {
        return _data[i];
    }

    const_reference operator[](size_type i) const {
        return _data[i];
    }

    reference at(size_type i) {
        if (i >= _size) {
            throw std::out_of_range("Simplevector::at index out of range");
        }
        return _data[i];
    }

    const_reference at(size_type i) const {
        if (i >= _size) {
            throw std::out_of_range("Simplevector::at index out of range");
        }
        return _data[i];
    }

    size_type size() const {
        return _size;
    }

    size_type capacity() const {
        return _capacity;
    }

    bool empty() const {
        return _size == 0;
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            grow();
        }
        // 重新分配空间
        _alloc.construct(_data + _size, value);
        ++_size;
    } 

    void pop_back() {
        if (_size == 0) {
            throw std::out_of_range("Simplevector::pop_back out of range");
        }

        --_size;
        _alloc.destroy(_data + _size);
    }

    void reserve(size_type new_cap) {
        if (new_cap <= _capacity) return;
        pointer new_data = _alloc.allocate(new_cap);

        for (size_type i = 0; i < _size; i++) {
            _alloc.construct(new_data + i, std::move_if_noexpect(_data[i]));
            _alloc.destroy(_data + i);
        }

        if (_data) {
            // 如果这片内存非空
            _alloc.deallocate(_data, _capacity);
        }
        _data = new_data;
        _capacity = new_cap;
    }

    void clear() {
        for (size_type i = 0; i < _size; i++) {
            _alloc.destroy(_data + i);
        }

        // 这里只是需要清除数据
        // 而不是析构
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
}