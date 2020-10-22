#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> vec{ {1, 2, 3}, {4, 5, 6}};

    for (std::vector<int> v : vec) {
        for (int i : v) {
           std::cout << i << "\n";
        }
    }
}