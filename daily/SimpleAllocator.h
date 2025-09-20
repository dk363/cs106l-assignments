#include <new>
#include <iostream>
#include <climits>

namespace SimpleSTL {
    // 分配内存
    template <class T> 
    inline T* _allocate(std::size_t size, T*) {
        T* tmp = static_cast<T*>(::operator new(size * sizeof(T)));
        return tmp;
    }

    // 释放内存
    template <class T> 
    inline void _deallocate(T* buffer) {
        // :: 表示全局作用域
        ::operator delete(buffer);
    }

    /**
     * 构造对象
     * int* raw = static_cast<int*>(::operator new(sizeof(int)));
     * _construct(raw, 42); // 在raw 指向的内存里 构造一个 int 值为 42
     */
    template <class T1, class T2>
    inline void _construct(T1* p, const T2& value) {
        new(p) T1(value);
    }

    // 将该指针指向的对象销毁
    template <class T>
    inline void _destroy(T* ptr) {
        if (ptr != nullptr) {
            ptr->~T();
        }
    }

    template <class T>
    class allocator {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type; // 表示两个元素之间的距离
        
        // rebind allovator of type U
        // 举个例子来说
        // list<int>
        // 这里面存储的是 listNode 
        // 而不是 int
        // 所以在传入 int 的时候 
        // 我们 rebind 到 listNode 
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        pointer allocate(size_type n, const void* hint = 0) {
            // pointer == T*
            // 这里是告诉 _allocate T* 的类型
            // 但是 value = 0 这里完全没有用到
            return _allocate(static_cast<difference_type>(n), (pointer)0);
        }

        void deallocate(pointer p, size_type n) {
            // 如果实现使用内存池 自定义分配器
            // 才需要知道 n 来决定释放策略
            _delallocate(p);
        }
        
        void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        void destroy(pointer p) {
            _destroy(p);
        }

        pointer address(reference x) {
            return (pointer)&x;
        }

        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }

        size_type max_size() const {
            return (size_type)(UINT_MAX / sizeof(T));
        }
    };
}