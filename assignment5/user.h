/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
    User(const std::string& name);
    void add_friend(const std::string& name);
    std::string get_name() const;
    size_t size() const;
    void set_friend(size_t index, const std::string& name);

    /**
    * STUDENT TODO:
    * Your custom operators and special member functions will go here!
    */
    /**
    * 学生待办事项：
    * 您的自定义运算符和特殊成员函数将放在这里！
    */
    friend std::ostream& operator << (std::ostream& out, const User& user);

    ~User();

    User(const User& other);

    User& operator=(const User& other);

    User(User&& user) = delete;

    User& operator=(User&& user) = delete;

    User& operator+=(User& other);

    bool operator<(const User& rhs) const;
private:
    std::string _name;
    std::string* _friends;
    size_t _size;
    size_t _capacity;
};