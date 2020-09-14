#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <functional>
#include <iostream>
#include <vector>

struct Color
{
    size_t r;
    size_t g;
    size_t b;
};

std::ostream &operator<<(std::ostream &o, const Color &c)
{
    o << "(" << c.r << ", " << c.g << ", " << c.b << ")";
    return o;
}

class Bins
{
private:
    std::vector<Color> bins;
    std::function<bool(const Color &, const Color &)> compare;

public:
    Bins(size_t count)
    {
        // Initialize bin values.
        const Color defaultColor = Color{r : 0, g : 0, b : 0};
        this->bins = std::vector<Color>(count);
        for (auto i = this->bins.begin(); i != this->bins.end(); i++)
        {
            *i = defaultColor;
        }
    }

    size_t getBin(const Color &color)
    {
        for (size_t i = 0; i < this->bins.size(); i++)
        {
            if (!this->compare(this->bins[i], color))
            {
                continue;
            }
            // Use a non-overflow bin.
            return i;
        }

        // Use the overflow bin.
        return this->bins.size();
    }

    friend std::ostream &operator<<(std::ostream &o, const Bins &b);
};

std::ostream &operator<<(std::ostream &o, const Bins &b)
{
    o << "[ ";
    for (auto i = b.bins.begin(); i != b.bins.end(); i++)
    {
        o << *i << " ";
    }
    o << "]";
    return o;
}

#endif
