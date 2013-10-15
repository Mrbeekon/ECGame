#pragma once
#ifndef COLOUR_H
#define COLOUR_H

#include "stdafx.h"

// Use in the place of ...byte r, byte g, byte, b... to acquire such values from int c.
#define INTRGB(c)   c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff

// Ditto, with additional alpha channel (0xff000000)
#define INTARGB(c)  c >> 24 & 0xff, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff

#define INTA(c)     c >> 24 & 0xff
#define INTR(c)     c >> 16 & 0xff
#define INTG(c)     c >> 8 & 0xff
#define INTB(c)     c & 0xff

// Colour channels within a 32-bit integer
#define CH_ALPHA    0xff000000
#define CH_RED      0x00ff0000
#define CH_GREEN    0x0000ff00
#define CH_BLUE     0x000000ff

static int RgbCol(byte r, byte g, byte b);          // Gets a colour integer from red, green, and blue byte values
static int ArgbCol(byte a, byte r, byte g, byte b); // Gets a colour integer from alpha, red, green, and blue byte values

#endif
