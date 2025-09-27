/*
 * CS106L 作业 7：Unique Pointer
 * 创建者：Jacob Roberts-Baca
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "unique_ptr.h"

/**
 * @brief 一个单向链表节点，使用 `unique_ptr` 管理指向下一个节点的指针，从而自动释放内存。
 * @tparam T 节点中存储的值的类型。
 *
 * @note 完成本作业不需要对这个 struct 进行任何修改！
 */
template <typename T> struct ListNode {

  /** @brief 存储在节点中的值。 */
  T value;

  /** @brief 指向下一个节点的智能指针，可以为空。 */
  cs106l::unique_ptr<ListNode<T>> next;

  /**
   * @brief 构造一个单元素链表，将 `next` 设置为 `nullptr`。
   * @param value 节点中要存储的值。
   */
  ListNode(T value) : value(value), next(nullptr) {
    /* 这一行只是用于日志打印，以便我们看到构造函数何时运行！ */
    std::cout << "Constructing node with value '" << value << "'\n";
  }

  ~ListNode() {
    /* 这一行只是用于日志打印，以便我们看到析构函数何时运行！ */
    std::cout << "Destructing node with value '" << value << "'\n";
  }
};

/**
 * @brief 根据一个值的向量创建一个单向链表。
 * @param values 要存储在链表中的值。
 * @return 指向链表头节点的 `unique_ptr`。
 */
template <typename T> cs106l::unique_ptr<ListNode<T>> create_list(const std::vector<T>& values) {
  // 向量中的顺序需要保留
  // 对于空向量 return nullptr
  // 反向构建链表
  // std::move 将左值转换为右值 
  if (values.empty()) return nullptr;
  
  cs106l::unique_ptr<ListNode<T>> head = nullptr;
  for (int i = values.size() - 1; i >= 0; --i) {
    auto node = cs106l::make_unique<ListNode<T>>(values[i]);
    node->next = std::move(head);
    head = std::move(node);
  }
  return head;
}

/**
 * @brief 对链表中的每个元素应用一个函数。
 * @tparam T 链表中存储的值的类型。
 * @tparam Func 要应用的函数类型。
 * @param head 链表的头节点。
 * @paragraph func 要应用到每个元素的函数。
 */
template <typename T, typename Func>
void map_list(const cs106l::unique_ptr<ListNode<T>>& head, const Func& func) {
  if (!head)
    return;
  func(head->value);
  map_list(head->next, func);
}

/**
 * @brief 使用 `unique_ptr` 的单向链表示例。
 */
void linked_list_example() {
  std::vector<std::string> names{"Jacob", "Fabio", "Keith", "Chris", "Sean"};
  auto head = create_list(names);
  map_list(head, [](const std::string& name) { std::cout << name << "\n"; });
}

#include "autograder/utils.hpp"
