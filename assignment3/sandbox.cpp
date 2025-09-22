// sandbox.cpp

/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
/*
 * CS106L 作业3：创建一个类
 * 由Fabio Ibanez创建，Jacob Roberts-Baca修改。
 */
#include <iostream>

#include "class.h"

void sandbox() {
    Box<int> box;

    std::cout << (box.empty() ? "yes" : "no") << std::endl;

    box.setValue(42);
    std::cout << box.getValue() << std::endl;

    box.clear();
    std::cout << (box.empty() ? "yes" : "no") << std::endl;

}