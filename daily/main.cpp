#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    double pi;
    double tao;
    std::string name;
    std::cin >> pi;
    std::cin >> name;
    std::cin >> tao;
    std::cout << "my name is " << name 
    << "\ntao is: " << tao 
    << "\npi is: " << pi << '\n';
    return 0;
}