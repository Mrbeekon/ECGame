#include "Colour.h"

static int RgbCol(byte r, byte g, byte b)
{
    return r << 16 | g << 8 | b;
}

static int ArgbCol(byte a, byte r, byte g, byte b)
{
    return a << 24 | r << 16 | g << 8 | b;
}

static int AvgCol(int c)
{
    return AvgCol(INTRGB(c));
}

static int AvgCol(byte r, byte g, byte b)
{
    byte ac = (r + g + b) / 3;
    return ac << 16 | ac << 8 | ac;
}
