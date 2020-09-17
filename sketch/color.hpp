#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <math.h>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color()
    {
        this->r = 0xFF;
        this->g = 0xFF;
        this->b = 0xFF;
    }

    Color(float r, float g, float b)
    {
        this->from(r, g, b);
    }

    void from(float r, float g, float b)
    {
        this->r = uint8_t(r);
        this->g = uint8_t(g);
        this->b = uint8_t(b);
    }

    bool operator==(const Color &rhs)
    {
        return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b;
    }
};

class Bins
{
private:
    const Color DefaultColor = Color();
    Color *bins;
    Color blankColor = DefaultColor;
    size_t binCount;
    bool (*equal)(const Color &, const Color &);

    bool isBlank(const Color &color)
    {
        return this->equal(color, this->blankColor);
    }

public:
    Bins(size_t binCount, bool (*equal)(const Color &, const Color &))
    {
        this->binCount = binCount;
        this->bins = new Color[binCount];
        this->equal = equal;
    }

    ~Bins()
    {
        this->bins = nullptr;
        delete[] this->bins;
    }
    
    void setBlank(Color color)
    {
        this->blankColor = color;
    }

    uint8_t size()
    {
        return this->binCount + 1;
    }

    size_t getBin(const Color &color)
    {
        if (this->isBlank(color))
        {
            return -1;
        }

        for (size_t i = 0; i < this->binCount; i++)
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
        return this->binCount;
    }
};

#endif
