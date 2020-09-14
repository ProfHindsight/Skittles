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

    auto c1 = Color{r : 100, g : 100, b : 100};
    auto c2 = Color{r : 50, g : 100, b : 150};
    auto c3 = Color{r : 99, g : 99, b : 99};
    auto c4 = Color{r : 200, g : 200, b : 200};

    check("insert 1st bin", c1, 0, bins.getBin(c1));
    check("insert 2nd bin", c2, 1, bins.getBin(c2));
    check("match 1st bin", c3, 0, bins.getBin(c3));
    check("insert overflow", c4, 2, bins.getBin(c4));
}
