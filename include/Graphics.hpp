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

// Allows for the basic colours to be acquired via an index number
const int COL[16] = { // Index Number:
    COL_BLACK,        // 0
    COL_DARKBLUE,     // 1
    COL_DARKGREEN,    // 2    
    COL_DARKCYAN,     // 3
    COL_DARKRED,      // 4
    COL_DARKMAGENTA,  // 5
    COL_DARKYELLOW,   // 6
    COL_GREY,         // 7
    COL_DARKGREY,     // 8
    COL_BLUE,         // 9
    COL_GREEN,        // A
    COL_CYAN,         // B
    COL_RED,          // C
    COL_MAGENTA,      // D
    COL_YELLOW,       // E
    COL_WHITE,        // F
};

// Bitmap drawing scale type
typedef enum
{
    SCALETYPE_NONE,    // Draws the bitmap in the given region
    SCALETYPE_TILE,    // Fills the region with a tile arrangement of the drawn bitmap
    SCALETYPE_STRETCH, // Stretches the bitmap to fill the region [Unimplemented]
} ScaleType;

// Font glyph drawing attributes
typedef struct
{
    int col = 0;
    bool bold = false;      // Unimplemented
    bool italic = false;
    bool strike = false;
    bool underline = false;
    bool shadow = false;    // Unimplemented
    bool punched = false;
} GlyphAtt;

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

    // Draw a font glyph
    void draw_font_glyph(int x, int y, char ch, GlyphAtt ga, byte* buff);
    
    // Draw a string of text to the screen
    void draw_string(int x, int y, std::string str, int c);

    // Destroys this graphics object
    void destroy(void);

/* Static */
    
    // Returns the length of the longest line in a string
    static
    int measure_string_longest_line(std::string str);

    // Returns the number of lines in a string
    static
    int measure_string_line_count(std::string str);

    // Measure the width of the string on screen
    // taking into account escape characters
    static
    int measure_string_width(std::string str);

    // Measure the height of the string on screen
    // taking into account escape characters
    static
    int measure_string_height(std::string str);

    // Return the additional blend of two colours
    static 
    int col_add(int c1, int c2);

    // The first colour becomes the additional blend of the two colours
    static 
    void col_add(int* c1, int c2);

    // Returns the alpha blend of two colours, with a blend degree of 50%
    static
    int col_blh(int c1, int c2);

    // The first colour becomes the alpha blend of the two colours, 
    // with a blend degree of 50%
    static
    void col_blh(int* c1, int c2);

    // Returns the alpha blend of two colours, with a
    // specified degree of blending
    static 
    int col_bl(int c1, int c2, byte a);

    // The first colour becomes the alpha blend of the
    // two colours, with a specified degree of blending
    static
    void col_bl(int* c1, int c2, byte a);

private:
    Bitmap* bitmap;

    void _draw_bitmap__scaletype_none(int x, int y, int width, int height, Bitmap* b);
    void _draw_bitmap__scaletype_tile(int x, int y, int width, int height, Bitmap* b);
    void _draw_bitmap__scaletype_stretch(int x, int y, int width, int height, Bitmap* b);
    void _andescproc(std::string andescstr, GlyphAtt* ga);
};

#endif
