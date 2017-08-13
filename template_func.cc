#include <iostream>

template <typename T>
int compare(const T& v1, const T& v2) {
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    }
    return 0;
}

template <typename T> inline int compare2(const T& v1, const T& v2) {
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    }
    return 0;
}

int main() {
    std::string a = "c";
    std::string b = "b";
    std::cout << compare2(3, 2) << std::endl;
    std::cout << compare2(a, b) << std::endl;
    std::cout << compare2("c", "b") << std::endl;
    std::cout << (a > b) << std::endl;
    return 0;
}
