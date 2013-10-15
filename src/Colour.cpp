#include "Colour.h"

static int rgb_col(byte r, byte g, byte b)
{
    return r << 16 | g << 8 | b;
}

static int argb_col(byte a, byte r, byte g, byte b)
{
    return a << 24 | r << 16 | g << 8 | b;
}
