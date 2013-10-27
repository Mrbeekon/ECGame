#include <cmath>
#include "SDL/SDL.h"

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed byte
typedef unsigned short      ushort;     // Unsigned short
typedef unsigned int        uint;       // Unsigned int
typedef unsigned long       ulong;      // Unsigned long
typedef ushort              WORD;       // A 16-bit word
typedef uint                DWORD;      // A 32-bit word
typedef unsigned long long  QWORD;      // A 64-bit word

#define PI                  3.1415926535897

// Check to see if value, v, contains flag, f
// (Use in place of boolean expression)
#define HASFLAG(v, f)       v & f == f

// [Experimental] Declare an enum member with
// a value suitable for being a flag
#define DECFLAG(f)          f = 1 << f


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
    
    Screen(uint w, uint h) 
    {
        width = w;
        height = h;
        surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
        clear(0);
    }

    ~Screen(void)
    {
        delete surface;
    }

    SDL_Surface* get_surface(void)
    {
        return surface;
    }

    void set_pixel(int x, int y, byte r, byte g, byte b)
    {
        unsigned int* pixel = (unsigned int*)(surface->pixels) + x + y * width;
        *pixel = SDL_MapRGB(surface->format, r, g, b);
    }

    void set_pixel(int x, int y, int c)
    {
        if (x < 0 | y < 0 | x >= width | y >= height)
            return;
        set_pixel(x, y, INTRGB(c));
    }

    int get_pixel(int x, int y)
    {
        return 0; // TODO: Work out how to get the colour of a pixel currently on the screen
    }

    void clear(int c)
    {
        for (int i = 0; i < width * height; i++) {
            unsigned int* pixel = (unsigned int*)(surface->pixels) + i;
            *pixel = SDL_MapRGB(surface->format, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff);
        }
    }
        
    void draw_rectangle(int x, int y, int w, int h, int c, int t)
    {
        for (int yy = 0; yy < h; yy++)
            for (int xx = 0; xx < w; xx++)
                if (yy < t | yy >= h - t | xx < t | xx >= w - t)
                    set_pixel(x + xx, y + yy, c);
    }

    void fill_rectangle(int x, int y, int w, int h, int c)
    {
        for (int yy = 0; yy < h; yy++)
            for (int xx = 0; xx < w; xx++)
                set_pixel(x + xx, y + yy, c);
    }

    void draw_circle(int x, int y, int r, int c)
    {
        for (double d = 0.0; d < PI * 2.0; d += PI / 180.0)
            set_pixel(x + r + sin(d) * r, y + r + cos(d) * r, c);
    }

    void fill_circle(int x, int y, int r, int c)
    {
        for (int yy = -r; yy < r; yy++)
            for (int xx = -r; xx < r; xx++)
                if (yy * yy + xx * xx < r * r)
                    set_pixel(x + r + xx, y + r + yy, c);
    }

    void draw_line(int x0, int y0, int x1, int y1, int c)
    {
        int dx = abs(x1 - x0),
            dy = abs(y1 - y0),
            sx = x0 < x1 ? 1 : -1,
            sy = y0 < y1 ? 1 : -1,
            err = dx - dy;
        while (true) {
            set_pixel(x0, y0, c);
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = err << 1;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (x0 == x1 && y0 == y1) {
                set_pixel(x0, y0, c);
                break;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
private:
    SDL_Surface* surface;
};

extern Screen screen;

