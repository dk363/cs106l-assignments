#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief 一个智能指针，它拥有一个对象，并在超出作用域时删除该对象。
 * @tparam T 要管理的对象类型。
 * @note 这个类是 `std::unique_ptr` 的简化版本。
 */
template <typename T> class unique_ptr {
private:
  T* _ptr;
  /* STUDENT TODO: unique_ptr 需要跟踪哪些数据？ */

public:
  /**
   * @brief 使用给定指针构造一个新的 `unique_ptr`。
   * @param ptr 要管理的指针。
   * @note 你应该尽量避免直接使用这个构造函数，而使用 `make_unique()`。
   */
  unique_ptr(T* ptr) : _ptr(ptr) {}

  /**
   * @brief 使用 `nullptr` 构造一个新的 `unique_ptr`。
   */
  unique_ptr(std::nullptr_t) : _ptr(nullptr) {}

  /**
   * @brief 构造一个空的 `unique_ptr`。
   * @note 默认情况下，`unique_ptr` 指向 `nullptr`。
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief 解引用 `unique_ptr` 并返回对象的引用。
   * @return 对象的引用。
   */
  T& operator*() {
    return *_ptr;
  }

  /**
   * @brief 解引用 `unique_ptr` 并返回对象的 const 引用。
   * @return 对象的 const 引用。
   */
  const T& operator*() const {
    return *_ptr;
  }

  /**
   * @brief 返回 `unique_ptr` 管理的对象的指针。
   * @note 这允许通过 `->` 操作符访问管理对象的成员。
   * @return 指向对象的指针。
   */
  T* operator->() {
    return _ptr;
  }

  /**
   * @brief 返回 `unique_ptr` 管理的对象的 const 指针。
   * @note 这允许通过 `->` 操作符访问管理对象的成员。
   * @return 指向对象的 const 指针。
   */
  const T* operator->() const {
    return _ptr;
  }

  /**
   * @brief 返回 `unique_ptr` 是否非空。
   * @note 这允许我们在 if 语句中使用 `unique_ptr`。
   * @return 如果 `unique_ptr` 非空返回 `true`，否则返回 `false`。
   */
  operator bool() const {
    return _ptr != nullptr;
  }

  /** STUDENT TODO: In the space below, do the following:
   * - Implement a destructor
   * - Delete the copy constructor
   * - Delete the copy assignment operator
   * - Implement the move constructor
   * - Implement the move assignment operator
   */
  /** STUDENT TODO: 在下面的空白处完成以下内容：
   * - 实现析构函数
   * - 删除拷贝构造函数
   * - 删除拷贝赋值运算符
   * - 实现移动构造函数
   * - 实现移动赋值运算符
   */
  ~unique_ptr() {
    delete _ptr;
  }

  unique_ptr(const unique_ptr& ptr) = delete;
  unique_ptr& operator=(const unique_ptr& ptr) = delete;

  unique_ptr(unique_ptr&& other) : _ptr(other._ptr) {
    other._ptr = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& other) {
    if (this == &other) return *this;

    delete this->_ptr;
    this->_ptr = other._ptr;
    other._ptr = nullptr;

    return *this;
  }
};

  /**
   * @brief 使用给定参数创建一个新的 unique_ptr。
   * @example auto ptr = make_unique<int>(5);
   * @tparam T 要创建 unique_ptr 的类型。
   * @tparam Args 传递给 T 构造函数的参数类型。
   * @param args 传递给 T 构造函数的参数。
   */
  template <typename T, typename... Args> 
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  
}
