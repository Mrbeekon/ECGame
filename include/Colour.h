#pragma once
#include "stdafx.h"

#define INTRGB(c)   c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff
#define INTARGB(c)  c >> 24 & 0xff, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff

static int RgbCol(byte r, byte g, byte b);
static int ArgbCol(byte a, byte r, byte g, byte b);
