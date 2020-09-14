#include <iostream>

#include "../sketch/color.hpp"

void check(const std::string &testName, const Color &color, size_t expected, size_t actual)
{
    std::cout << "test: " << testName << " " << (expected == actual ? "(PASS)" : "(FAIL)")
              << "\n"
              << "  - input: " << color << "\n"
              << "  - expected: " << expected << "\n"
              << "  - got: " << actual << "\n";
}

int main()
{
    auto bins = Bins(2, 2.0f);

    auto c1 = Color(100.0f, 100.0f, 100.0f);
    auto c2 = Color(50.0f, 100.0f, 150.0f);
    auto c3 = Color(99.0f, 99.0f, 99.0f);
    auto c4 = Color(200.0f, 200.0f, 200.0f);

    check("insert 1st bin", c1, 0, bins.getBin(c1));
    check("insert 2nd bin", c2, 1, bins.getBin(c2));
    check("match 1st bin", c3, 0, bins.getBin(c3));
    check("insert overflow", c4, 2, bins.getBin(c4));
}
