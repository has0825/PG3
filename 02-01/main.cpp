#include <iostream>
using namespace std;

template <typename T>
T Min(T a, T b) {
    return (a < b) ? a : b;
}

int main() {
    // int型
    int a = 10, b = 20;
    cout << "Min(int): " << Min(a, b) << endl;

    // float型
    float x = 3.14f, y = 1.59f;
    cout << "Min(float): " << Min(x, y) << endl;

    // double型
    double p = 2.718, q = 3.14159;
    cout << "Min(double): " << Min(p, q) << endl;

    return 0;
}
