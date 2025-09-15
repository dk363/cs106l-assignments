#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>    // std::vector
#include <utility>   // std::pair


void andExample(int x) {
    int num = x; 
    int& ref = num;
    ref = 10;
    std::cout << ref << std::endl;
    std::cout << num << std::endl;
}

void squareN(int& n) {
    n = std::pow(n, 2);
}

void shift(std::vector<std::pair<int, int>> &nums) {
    for (auto [num1, num2] : nums) {
        num1++;
        num2++;
        std::cout << num1 << std::endl;
        std::cout << num2 << std::endl;
    }
}

void foo() {
    std::string initial_quote = "Bjarne Stroustrup C makes it easy to shoot yourself in the foot";
    std::stringstream ss;
    ss << initial_quote;

    std::string first;
    std::string last;
    std::string language, extracted_quote;

    ss >> first >> last >> language >> extracted_quote;

    std::cout << first << " " << last << " said this: " << language << " " << extracted_quote << std::endl;
}

void cinExample() {
    double pi;
    std::string name;
    double tao;
    std::cin >> pi;
    std::getline(std::cin, name);
    std::getline(std::cin, name);
    std::cin >> tao;
    std::cout << pi << " " << name << " " << tao << std::endl;

}
int main() {
    cinExample();
    return 0;
}

// bx + c == 0
// x = -c / b
std::pair<bool, std::pair<double, double>> solveQuadratic(int a, int b, int c) {
    if (a == 0) {
        return {true, {-c / b, -c / b}};
    }
    bool has_solution = false;
    double del = sqrt(b * b - 4 * b * c);
    if (del > 0) {
        return {true, {}};
    } else if (del == 0) {
        return {true, {}};
    } else {
        // del < 0
        return {false, {-1, -1}};
    }
}

