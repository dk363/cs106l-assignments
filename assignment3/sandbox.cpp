// sandbox.cpp

/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
/*
 * CS106L 作业3：创建一个类
 * 由Fabio Ibanez创建，Jacob Roberts-Baca修改。
 */
#include "class.h"
#include <iostream>

void sandbox();

void sandbox() {
    Vector<int> vector;
    for (int i = 0; i < 5; i++) {
        vector.push_back(106);
    }

    for (const auto& element : vector) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}