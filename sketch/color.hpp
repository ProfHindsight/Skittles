#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <functional>
#include <iostream>
#include <math.h>
#include <vector>

struct Color
{
    size_t r;
    size_t g;
    size_t b;

    bool operator==(const Color &rhs)
    {
        return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b;
    }
};

std::ostream &operator<<(std::ostream &o, const Color &c)
{
    o << "(" << c.r << ", " << c.g << ", " << c.b << ")";
    return o;
}

class Bins
{
private:
    const Color DefaultColor = Color{r : 0, g : 0, b : 0};
    std::vector<Color> bins;
    std::function<bool(const Color &, const Color &)> equal;

    void initBinValues(size_t binCount)
    {
        this->bins = std::vector<Color>(binCount);
        for (auto i = this->bins.begin(); i != this->bins.end(); i++)
        {
            *i = DefaultColor;
        }
    }

public:
    Bins(size_t binCount, float mseThreshold)
    {
        this->initBinValues(binCount);

        // Use default comparison.
        this->equal = [mseThreshold](const Color &lhs, const Color &rhs) -> bool {
            auto mse = sqrt(
                lhs.r - rhs.r * lhs.r - rhs.r +
                lhs.g - rhs.g * lhs.g - rhs.g +
                lhs.b - rhs.b * lhs.b - rhs.b);
            return mse < mseThreshold;
        };
    }

    Bins(size_t binCount, std::function<bool(const Color &, const Color &)> equal)
    {
        this->initBinValues(binCount);
        this->equal = equal;
    }

    size_t getBin(const Color &color)
    {
        for (size_t i = 0; i < this->bins.size(); i++)
        {
            // If this bin is empty, then automatically store the value here.
            if (this->bins[i] == this->DefaultColor)
            {
                this->bins[i] = color;
                return i;
            }

            // Otherwise check if the color matches this bin.
            if (!this->equal(this->bins[i], color))
            {
                continue;
            }
            // Found a non-overflow bin match.
            return i;
        }

        // No bin match, use overflow bin.
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
