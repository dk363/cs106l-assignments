#include "user.h"

#include <string>
#include <ostream>
/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
std::ostream& operator << (std::ostream& out, const User& user) {
  out << "User(name=" << user._name << ", friends=[";
  std::string* friends = user._friends;
  for (size_t i = 0; i < user._size; ++i) {
    out << friends[i];
    if (i != user._size - 1) {
      out << ", ";
    }
  }
  out << "])";
  return out;
}

User::~User() {
  delete[] _friends;
}

// 两种拷贝方式都应该是深拷贝
// 因为如果指向同一块内存
// 对其中一个指针的操作会影响另一个指针
User::User(const User& other) :
_name(other._name), _friends(new std::string[other._capacity]),
_size(other._size), _capacity(other._capacity) {
  std::copy(other._friends, other._friends + other._size, _friends);
}

User& User::operator=(const User& other) {
  if (this == &other) {
    return *this;
  }

  delete[] _friends;
  _name = other._name;
  _size = other._size;
  _capacity = other._capacity;

  _friends = new std::string[_capacity];
  std::copy(other._friends, other._friends + _size, _friends);
  return *this;
}

User &User::operator+=(User &other) {
  this->add_friend(other._name);
  other.add_friend(this->_name);
  return *this;
}

bool User::operator<(const User &rhs) const {
  return this->get_name() < rhs.get_name();
}

