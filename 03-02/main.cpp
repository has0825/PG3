#include <iostream>

template <typename T1, typename T2>
class PairCalc {
public:
    T1 val1;
    T2 val2;

    PairCalc(T1 a, T2 b) : val1(a), val2(b) {}

    auto Min() {
        return (val1 < val2) ? val1 : val2;
    }
};

int main() {

    PairCalc<int, int> p1(10, 20);
    std::cout << "1. <int, int> (10, 20) -> " << p1.Min() << std::endl;

    PairCalc<float, float> p2(3.5f, 1.2f);
    std::cout << "2. <float, float> (3.5, 1.2) -> " << p2.Min() << std::endl;

    PairCalc<double, double> p3(100.123, 50.999);
    std::cout << "3. <double, double> (100.123, 50.999) -> " << p3.Min() << std::endl;

    std::cout << "--------------------------------" << std::endl;

    PairCalc<int, float> p4(5, 5.5f);
    std::cout << "4. <int, float> (5, 5.5) -> " << p4.Min() << std::endl;

    PairCalc<int, double> p5(10, 3.14);
    std::cout << "5. <int, double> (10, 3.14) -> " << p5.Min() << std::endl;

    PairCalc<float, double> p6(9.9f, 9.99);
    std::cout << "6. <float, double> (9.9, 9.99) -> " << p6.Min() << std::endl;

    return 0;
}