#pragma once

#include "Common.h"

class Color
{
public:
    byte r = 0, g = 0, b = 0;

    Color() = default;
    inline Color(byte r, byte g, byte b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    inline byte & operator[] (int index)
    {
        switch (index) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: throw Exception();
        }
    }

    inline String terminalColor() const
    {
        return "\033[48;2;" + str(b) + ";" + str(g) + ";" + str(r) + "m";
    }

    inline String terminalPixel() const
    {
        return "\033[48;2;" + str(b) + ";" + str(g) + ";" + str(r) + "m ";
    }

    inline bool operator == (const Color & rhs) const
    {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    inline bool operator != (const Color & rhs) const
    {
        return r != rhs.r || g != rhs.g || b != rhs.b;
    }
};
