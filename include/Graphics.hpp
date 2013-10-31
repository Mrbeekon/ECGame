#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "ec.hpp"
#include "Bitmap.hpp"

// Forward declare the Bitmap class
class Bitmap;

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

// Tab size for text rendering
#define TABSIZE     4

// 16 Basic Colours
const int COL[16] = {
    0x000000, 
    0x000080, 
    0x008000, 
    0x008080, 
    0x800000, 
    0x800080, 
    0x808000, 
    0xC0C0C0, 
    0x808080, 
    0x0000FF, 
    0x00FF00, 
    0x00FFFF, 
    0xFF0000, 
    0xFFFF00, 
    0xFFFF00, 
    0xFFFFFF
};

#define COL_BLACK       COL[0]
#define COL_DARKBLUE    COL[1]
#define COL_DARKGREEN   COL[2]
#define COL_DARKCYAN    COL[3]
#define COL_DARKRED     COL[4]
#define COL_DARKMAGENTA COL[5]
#define COL_DARKYELLOW  COL[6]
#define COL_GREY        COL[7] // <--- These two are meant to be 'backwards'
#define COL_DARKGREY    COL[8] // <-'
#define COL_BLUE        COL[9]
#define COL_GREEN       COL[10]
#define COL_CYAN        COL[11]
#define COL_RED         COL[12]
#define COL_MAGENTA     COL[13]
#define COL_YELLOW      COL[14]
#define COL_WHITE       COL[15]

// Bitmap drawing scale type
typedef enum
{
    SCALETYPE_NONE,    // Draws the bitmap in the given region
    SCALETYPE_TILE,    // Fills the region with a tile arrangement of the drawn bitmap
    //-[Unimplemented]-//
    SCALETYPE_CENTRE,  // Centres the bitmap in the given region
    SCALETYPE_STRETCH, // Stretches the bitmap to fill the region [Unimplemented]
    SCALETYPE_ZOOM,    // Resize the bitmap to fill the region, maintaining aspect ratio
    //-----------------//
} ScaleType;

class Graphics
{
public:
    Graphics(Bitmap* b); 

    // Set the colour of a pixel on the screen
    // specifying red, green, and blue values
    void set_pixel(int x, int y, byte r, byte g, byte b);

    // Set the colour of a pixel on the screen, using an integer colour.
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
    // Use for speed. Set 'vertical' as true to draw a horizontal line, otherwise
    // it will be horizontal.
    void draw_line_flat(int x, int y, int l, bool vertical, int c);

    // Draw a bitmap without any form of scaling 
    void draw_bitmap_unscaled(int x, int y, Bitmap* b);

    // Draw a bitmap with the specified scale type
    void draw_bitmap(int x, int y, int width, int height, Bitmap* b, ScaleType st);
    
    // Draw a string of text to the screen
    void draw_string(int x, int y, const char* str, int c);

    // Destroys this graphics object
    void destroy(void);
private:
    Bitmap* bitmap;

    // Not a duplicated of Graphics::draw_bitmap_unscaled -- this allows for clipping
    void _draw_bitmap__scaletype_none(int x, int y, int width, int height, Bitmap* b);

    void _draw_bitmap__scaletype_tile(int x, int y, int width, int height, Bitmap* b);

    void _draw_bitmap__scaletype_centre(int x, int y, int width, int height, Bitmap* b);

    void _draw_bitmap__scaletype_stretch(int x, int y, int width, int height, Bitmap* b);

    void _draw_bitmap__scaletype_zoom(int x, int y, int width, int height, Bitmap* b);
};

/* Global Functions */

// Return the additional blend of two colours
int col_add(int c1, int c2);

// The first colour becomes the additional blend of the two colours
void col_add(int* c1, int c2);

// Returns the alpha blend of two colours, with a blend degree of 50%
int col_blh(int c1, int c2);

// The first colour becomes the alpha blend of the two colours, 
// with a blend degree of 50%
void col_blh(int* c1, int c2);

// Returns the alpha blend of two colours, with a
// specified degree of blending
int col_bl(int c1, int c2, byte a);

// The first colour becomes the alpha blend of the
// two colours, with a specified degree of blending
void col_bl(int* c1, int c2, byte a);

#endif
