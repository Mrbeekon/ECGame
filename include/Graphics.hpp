#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "ec.hpp"

// Colour to denote transparency without alpha byte
#define RGBTRANSPARENT   0xFF00FF

// Use in the place of a series of 3 parameters to acquire r, g, and b
// values from an integer colour, c.
#define INTRGB(c)   ((c) >> 16 & 0xff), ((c) >> 8 & 0xff), ((c) & 0xff)

// Use in the place of a series of 3 parameters to acquire a, r, g, and b
// values from an integer colour, c.
#define INTARGB(c)  ((c) >> 24 & 0xff), ((c) >> 16 & 0xff), ((c) >> 8 & 0xff), ((c) & 0xff)

// Acquire a particular channel value from an integer
#define INTA(c)     ((c) >> 24 & 0xff)
#define INTR(c)     ((c) >> 16 & 0xff)
#define INTG(c)     ((c) >> 8 & 0xff)
#define INTB(c)     ((c) & 0xff)

// Acquire an integer from rgb channel values
#define RGBINT(r, g, b)     ((r) << 16 | (g) << 8 | (b))

// Acquire an integer from argb channel values
#define ARGBINT(a, r, g, b) ((a) << 24 | (r) << 16 | (g) << 8 | (b))

// Colour channels within a 32-bit integer
#define CH_A        0xff000000
#define CH_R        0x00ff0000
#define CH_G        0x0000ff00
#define CH_B        0x000000ff

// Tab size for text rendering
#define TABSIZE     4

// 16 Basic Colours
#define COL_BLACK       0x000000
#define COL_DARKBLUE    0x000080
#define COL_DARKGREEN   0x008000
#define COL_DARKCYAN    0x008080
#define COL_DARKRED     0x800000
#define COL_DARKMAGENTA 0x800080
#define COL_DARKYELLOW  0x808000
#define COL_GREY        0xC0C0C0 // <--- These two are meant to be 'backwards'
#define COL_DARKGREY    0x808080 // <-'
#define COL_BLUE        0x0000FF
#define COL_GREEN       0x00FF00
#define COL_CYAN        0x00FFFF
#define COL_RED         0xFF0000
#define COL_MAGENTA     0xFFFF00
#define COL_YELLOW      0xFFFF00
#define COL_WHITE       0xFFFFFF

class Graphics;

class Bitmap
{
public:
    uint width, height;

    Bitmap(uint width, uint height);
    Bitmap(uint width, uint height, void* pixels);

    // Get the pixels of the bitmap
    void* get_pixels(void);

    // Create a Graphics object for this bitmap
    Graphics* create_graphics(void);

    // Destroy the bitmap object
    void destroy(void);
private:
    void* pixels;
};

class Graphics
{
public:
    Graphics(Bitmap* b); 

    // Set the colour of a pixel on the screen
    // specifying red, green, and blue values
    void set_pixel(int x, int y, byte r, byte g, byte b);

    // Set the colour of a pixel on the screen, using an integer colour
    // Unlike set_pixel(int, int, byte, byte, byte), this has checks to
    // ensure that the pixel is set within the bounds of the screen.
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

    // Draw either a horizontal or vertical line of length, l, from point (x, y).
    // Use for speed
    void draw_line_flat(int x, int y, int l, bool vertical, int c);

    // Draw a bitmap
    void draw_bitmap(int x, int y, Bitmap* b);
    
    void draw_string(int x, int y, const char* str, int c);

    // Destroys this graphics object
    void destroy(void);
private:
    Bitmap* bitmap;
};

/* Static Global Functions */

// Return the additional blend of two colours
static int col_add(int c1, int c2);

// The first colour becomes the additional blend of the two colours
static void col_add(int* c1, int c2);

// Returns the alpha blend of two colours, with a blend degree of 50%
static int col_blh(int c1, int c2);

// The first colour becomes the alpha blend of the two colours, 
// with a blend degree of 50%
static void col_blh(int* c1, int c2);

// Returns the alpha blend of two colours, with a
// specified degree of blending
static int col_bl(int c1, int c2, byte a);

// The first colour becomes the alpha blend of the
// two colours, with a specified degree of blending
static void col_bl(int* c1, int c2, byte a);

#endif
