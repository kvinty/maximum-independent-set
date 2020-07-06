#include <iostream>
#include <vector>

#include <mis.hpp>

int main() {
    int n = 5;
    std::vector<std::array<int, 2>> edges = {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};

    for (int i : mis_solve(n, edges)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
