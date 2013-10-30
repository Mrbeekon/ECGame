#include "Graphics.hpp"

const byte ASCIIFONT[12 * 95] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 30, 30, 30, 12, 12, 0, 12, 12,
    0, 0, 0, 102, 102, 102, 36, 0, 0, 0, 0, 0, 0, 0, 0, 54, 54, 127, 54, 54, 
    54, 127, 54, 54, 0, 0, 12, 12, 62, 3, 3, 30, 48, 48, 31, 12, 12, 0, 0, 0,
    0, 35, 51, 24, 12, 6, 51, 49, 0, 0, 0, 14, 27, 27, 14, 95, 123, 51, 59, 
    110, 0, 0, 0, 12, 12, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 48, 24, 12, 6, 6, 6,
    12, 24, 48, 0, 0, 0, 6, 12, 24, 48, 48, 48, 24, 12, 6, 0, 0, 0, 0, 0, 102,
    60, 255, 60, 102, 0, 0, 0, 0, 0, 0, 0, 24, 24, 126, 24, 24, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 28, 28, 6, 0, 0, 0, 0, 0, 0, 127, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 28, 28, 0, 0, 0, 0, 64, 96, 48, 24, 12, 6, 3, 1,
    0, 0, 0, 62, 99, 115, 123, 107, 111, 103, 99, 62, 0, 0, 0, 8, 12, 15, 12,
    12, 12, 12, 12, 63, 0, 0, 0, 30, 51, 51, 48, 24, 12, 6, 51, 63, 0, 0, 0, 
    30, 51, 48, 48, 28, 48, 48, 51, 30, 0, 0, 0, 48, 56, 60, 54, 51, 127, 48,
    48, 120, 0, 0, 0, 63, 3, 3, 3, 31, 48, 48, 51, 30, 0, 0, 0, 28, 6, 3, 3, 
    31, 51, 51, 51, 30, 0, 0, 0, 127, 99, 99, 96, 48, 24, 12, 12, 12, 0, 0, 0,
    30, 51, 51, 51, 30, 51, 51, 51, 30, 0, 0, 0, 30, 51, 51, 51, 62, 24, 24, 
    12, 14, 0, 0, 0, 0, 0, 28, 28, 0, 0, 28, 28, 0, 0, 0, 0, 0, 0, 28, 28, 0,
    0, 28, 28, 24, 12, 0, 0, 48, 24, 12, 6, 3, 6, 12, 24, 48, 0, 0, 0, 0, 0,
    0, 126, 0, 126, 0, 0, 0, 0, 0, 0, 6, 12, 24, 48, 96, 48, 24, 12, 6, 0, 0,
    0, 30, 51, 48, 24, 12, 12, 0, 12, 12, 0, 0, 0, 62, 99, 99, 123, 123, 123,
    3, 3, 62, 0, 0, 0, 12, 30, 51, 51, 51, 63, 51, 51, 51, 0, 0, 0, 63, 102, 
    102, 102, 62, 102, 102, 102, 63, 0, 0, 0, 60, 102, 99, 3, 3, 3, 99, 102, 
    60, 0, 0, 0, 31, 54, 102, 102, 102, 102, 102, 54, 31, 0, 0, 0, 127, 70, 6,
    38, 62, 38, 6, 70, 127, 0, 0, 0, 127, 102, 70, 38, 62, 38, 6, 6, 15, 0, 0,
    0, 60, 102, 99, 3, 3, 115, 99, 102, 124, 0, 0, 0, 51, 51, 51, 51, 63, 51, 
    51, 51, 51, 0, 0, 0, 30, 12, 12, 12, 12, 12, 12, 12, 30, 0, 0, 0, 120, 48,
    48, 48, 48, 51, 51, 51, 30, 0, 0, 0, 103, 102, 54, 54, 30, 54, 54, 102,
    103, 0, 0, 0, 15, 6, 6, 6, 6, 70, 102, 102, 127, 0, 0, 0, 99, 119, 127, 
    127, 107, 99, 99, 99, 99, 0, 0, 0, 99, 99, 103, 111, 127, 123, 115, 99, 
    99, 0, 0, 0, 28, 54, 99, 99, 99, 99, 99, 54, 28, 0, 0, 0, 63, 102, 102, 
    102, 62, 6, 6, 6, 15, 0, 0, 0, 28, 54, 99, 99, 99, 115, 123, 62, 48, 120,
    0, 0, 63, 102, 102, 102, 62, 54, 102, 102, 103, 0, 0, 0, 30, 51, 51, 3, 
    14, 24, 51, 51, 30, 0, 0, 0, 63, 45, 12, 12, 12, 12, 12, 12, 30, 0, 0, 0,
    51, 51, 51, 51, 51, 51, 51, 51, 30, 0, 0, 0, 51, 51, 51, 51, 51, 51, 51,
    30, 12, 0, 0, 0, 99, 99, 99, 99, 107, 107, 54, 54, 54, 0, 0, 0, 51, 51, 
    51, 30, 12, 30, 51, 51, 51, 0, 0, 0, 51, 51, 51, 51, 30, 12, 12, 12, 30,
    0, 0, 0, 127, 115, 25, 24, 12, 6, 70, 99, 127, 0, 0, 0, 60, 12, 12, 12, 
    12, 12, 12, 12, 60, 0, 0, 0, 0, 1, 3, 6, 12, 24, 48, 96, 64, 0, 0, 0, 60,
    48, 48, 48, 48, 48, 48, 48, 60, 0, 0, 8, 28, 54, 99, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 12, 12, 24, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 30, 48, 62, 51, 51, 110, 0, 0, 0, 7, 6, 6, 62, 102,
    102, 102, 102, 59, 0, 0, 0, 0, 0, 0, 30, 51, 3, 3, 51, 30, 0, 0, 0, 56,
    48, 48, 62, 51, 51, 51, 51, 110, 0, 0, 0, 0, 0, 0, 30, 51, 63, 3, 51, 30,
    0, 0, 0, 28, 54, 6, 6, 31, 6, 6, 6, 15, 0, 0, 0, 0, 0, 0, 110, 51, 51,
    51, 62, 48, 51, 30, 0, 7, 6, 6, 54, 110, 102, 102, 102, 103, 0, 0, 0, 24,
    24, 0, 30, 24, 24, 24, 24, 126, 0, 0, 0, 48, 48, 0, 60, 48, 48, 48, 48,
    51, 51, 30, 0, 7, 6, 6, 102, 54, 30, 54, 102, 103, 0, 0, 0, 30, 24, 24, 
    24, 24, 24, 24, 24, 126, 0, 0, 0, 0, 0, 0, 63, 107, 107, 107, 107, 99, 0,
    0, 0, 0, 0, 0, 31, 51, 51, 51, 51, 51, 0, 0, 0, 0, 0, 0, 30, 51, 51, 51, 
    51, 30, 0, 0, 0, 0, 0, 0, 59, 102, 102, 102, 102, 62, 6, 15, 0, 0, 0, 0, 
    110, 51, 51, 51, 51, 62, 48, 120, 0, 0, 0, 0, 55, 118, 110, 6, 6, 15, 0,
    0, 0, 0, 0, 0, 30, 51, 6, 24, 51, 30, 0, 0, 0, 0, 4, 6, 63, 6, 6, 6, 54, 
    28, 0, 0, 0, 0, 0, 0, 51, 51, 51, 51, 51, 110, 0, 0, 0, 0, 0, 0, 51, 51, 
    51, 51, 30, 12, 0, 0, 0, 0, 0, 0, 99, 99, 107, 107, 54, 54, 0, 0, 0, 0, 0,
    0, 99, 54, 28, 28, 54, 99, 0, 0, 0, 0, 0, 0, 102, 102, 102, 102, 60, 48,
    24, 15, 0, 0, 0, 0, 63, 49, 24, 6, 35, 63, 0, 0, 0, 56, 12, 12, 6, 3, 6, 
    12, 12, 56, 0, 0, 0, 24, 24, 24, 24, 0, 24, 24, 24, 24, 0, 0, 0, 7, 12, 
    12, 24, 48, 24, 12, 12, 7, 0, 0, 0, 206, 91, 115, 0, 0, 0, 0, 0, 0, 0, 0,
};

/*** Bitmap ***/

Bitmap::Bitmap(uint width, uint height)
{
    this->width = width;
    this->height = height;
    this->pixels = (void*)(new int[width * height]);
    this->create_graphics()->clear(0);
}

Bitmap::Bitmap(uint width, uint height, void* pixels)
{
    this->width = width;
    this->height = height;
    this->pixels = pixels;
}

void* Bitmap::get_pixels(void)
{
    return pixels;
}

Graphics* Bitmap::create_graphics(void)
{
    return new Graphics(this);
}

void Bitmap::destroy(void)
{
    delete this;
}

/*** Graphics ***/

Graphics::Graphics(Bitmap* b) 
{
    bitmap = b;
}

void Graphics::set_pixel(int x, int y, byte r, byte g, byte b)
{
    int* p = (int*)(bitmap->get_pixels()) + x + y * bitmap->width;
    *p = RGBINT(r, g, b);
}

void Graphics::set_pixel(int x, int y, int c)
{
    if (x < 0 | y < 0 | x >= bitmap->width | y >= bitmap->height)
        return;
    set_pixel(x, y, INTRGB(c));
}

int Graphics::get_pixel(int x, int y)
{
    return (int)((int*)(bitmap->get_pixels()))[x + y * bitmap->width];
}

void Graphics::clear(int c)
{
    for (int i = 0; i < bitmap->width * bitmap->height; i++) {
        int* p = (int*)(bitmap->get_pixels()) + i;
        *p = c;
    }
}
    
void Graphics::draw_rectangle(int x, int y, int w, int h, int c, int t)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            if (yy < t | yy >= h - t | xx < t | xx >= w - t)
                set_pixel(x + xx, y + yy, c);
}

void Graphics::fill_rectangle(int x, int y, int w, int h, int c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            set_pixel(x + xx, y + yy, c);
}

void Graphics::draw_circle(int x, int y, int r, int c)
{
    for (double d = 0.0; d < PI * 2.0; d += PI / 180.0)
        set_pixel(x + r + sin(d) * r, y + r + cos(d) * r, c);
}

void Graphics::fill_circle(int x, int y, int r, int c)
{
    for (int yy = -r; yy < r; yy++)
        for (int xx = -r; xx < r; xx++)
            if (yy * yy + xx * xx < r * r)
                set_pixel(x + r + xx, y + r + yy, c);
}

void Graphics::draw_line(int x0, int y0, int x1, int y1, int c)
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

void Graphics::draw_line_flat(int x, int y, int l, bool vertical, int c)
{
    if (vertical)
        for (int i = 0; i < l; i++)
            set_pixel(x, y + i, c);
    else
        for (int i = 0; i < l; i++)
            set_pixel(x + i, y, c);
}

void Graphics::draw_bitmap(int x, int y, Bitmap* b)
{
    for (int yy = 0; yy < b->height; yy++) {
        for (int xx = 0; xx < b->width; xx++) {
            int* p = (int*)(b->get_pixels()) + xx + yy * b->width;
            set_pixel(x + xx, y + yy, *p);
        }
    }
}

void Graphics::draw_string(int x, int y, const char* str, int c)
{
    // i is the index of the current character in the string,
    // j is the horizontal position of the current character on screen
    // k is the vertical position of the current character on screen
    for (int i = 0, j = 0, k = 0; i < strlen(str); i++, j++) {
        switch (str[i]) {
        case '\n':  // newline
            j = -1; // will be incremented on the next loop cycle
            k++;
            break;
        case '\t':  // tab
            j += TABSIZE - (j % TABSIZE);
            break;
        default:
            byte b[12];
            memcpy(b, ASCIIFONT + (str[i] - 32) * 12, 12);
            for (int yy = 0; yy < 12; yy++) {
                    for (int xx = 0; xx < 8; xx++) {
                    set_pixel(xx + x + (j << 3), yy + y + k * 12, (b[yy] >> xx) & 0x1 == 0x1 ? c : 0);
                }
            }
            break;
        }
    }
}

void Graphics::destroy(void)
{
    delete this;
}

/* Static Global Functions */

static int col_add(int c1, int c2)
{
    int c = (c1 & 0xfefefe) + (c2 & 0xfefefe);
    return c | ((c >> 8) & 0x010101) * 0xFF;
}

static void col_add(int* c1, int c2)
{
    int c = (*c1 & 0xfefefe) + (c2 & 0xfefefe);
    *c1 = c | ((c >> 8) & 0x010101) * 0xFF;
}

static int col_blh(int c1, int c2)
{
    return ((c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

static void col_blh(int* c1, int c2)
{
    *c1 = ((*c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

static int col_bl(int c1, int c2, byte a)
{
    uint cc1 = (uint)c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    return (int)
            ((((c1 & 0xff00ff) * uf + (c2 & 0xff00ff) * a) & 0xff00ff00) |
            (((c1 & 0x00ff00) * uf + (c2 & 0x00ff00) * a) & 0x00ff0000)) >> 8;
}

static void col_bl(int* c1, int c2, byte a)
{
    uint cc1 = (uint)*c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    *c1 = (int)
            ((((*c1 & 0xff00ff) * uf + (c2 & 0xff00ff) * a) & 0xff00ff00) |
            (((*c1 & 0x00ff00) * uf + (c2 & 0x00ff00) * a) & 0x00ff0000)) >>8;
}
