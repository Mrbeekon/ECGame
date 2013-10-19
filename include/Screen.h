#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "ec.h"

// Used by certain methods to denote transparency
#define RGBTRANSPARENT   0xFF00FF

// Use in the place of ...byte r, byte g, byte, b... to acquire such values
// from int c.
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

// Gets a colour integer from red, green, and blue byte values
static int rgb_col(byte r, byte g, byte b);
// Gets a colour integer from alpha, red, green, and blue byte values
static int argb_col(byte a, byte r, byte g, byte b);

class Screen
{
public:
    int width, height;
    Screen(uint w, uint h); 
    ~Screen(void);

    // Set the colour of a pixel on the screen
    // specifying red, green, and blue values
    void set_pixel(int x, int y, byte r, byte g, byte b);

    // Set the colour of a pixel on the screen, using an integer colour
    void set_pixel(int x, int y, int c);

    // Returns the integer colour of a pixel on the screen
    int get_pixel(int x, int y);

    // Clear the screen with a solid colour
    void clear(int c);

    // Draws the outline of a rectangle
    void draw_rectangle(int x, int y, int w, int h, int c, int t);

    // Fills in a rectangular area
    void fill_rectangle(int x, int y, int w, int h, int c);

    // Draw the outline of a circle with radius r
    void draw_circle(int x, int y, int r, int c);

    // Draw a filled circle with radius r
    void fill_circle(int x, int y, int r, int c);

    // Draw a line between (x0, y0) and (x1, y1)
    void draw_line(int x0, int y0, int x1, int y1, int c);

    // Returns a pointer to the SDL_Surface
    SDL_Surface* get_surface(void);
private:	
    SDL_Surface* surface;
};

#endif
