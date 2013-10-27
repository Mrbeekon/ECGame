#include "Graphics.hpp"

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

/*** Graphics ***/

Graphics::Graphics(Bitmap* b) 
{
    bitmap = b;
}

Graphics* Graphics::set_pixel(int x, int y, byte r, byte g, byte b)
{
    int* p = (int*)(bitmap->get_pixels()) + x + y * bitmap->width;
    *p = RGBINT(r, g, b);
    return this;
}

Graphics* Graphics::set_pixel(int x, int y, int c)
{
    if (x < 0 | y < 0 | x >= bitmap->width | y >= bitmap->height)
        return this;
    set_pixel(x, y, INTRGB(c));
    return this;
}

int Graphics::get_pixel(int x, int y)
{
    return (int)((int*)(bitmap->get_pixels()))[x + y * bitmap->width];
}

Graphics* Graphics::clear(int c)
{
    for (int i = 0; i < bitmap->width * bitmap->height; i++) {
        int* p = (int*)(bitmap->get_pixels()) + i;
        *p = c;
    }
    return this;
}
    
Graphics* Graphics::draw_rectangle(int x, int y, int w, int h, int c, int t)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            if (yy < t | yy >= h - t | xx < t | xx >= w - t)
                set_pixel(x + xx, y + yy, c);
    return this;
}

Graphics* Graphics::fill_rectangle(int x, int y, int w, int h, int c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            set_pixel(x + xx, y + yy, c);
    return this;
}

Graphics* Graphics::draw_circle(int x, int y, int r, int c)
{
    for (double d = 0.0; d < PI * 2.0; d += PI / 180.0)
        set_pixel(x + r + sin(d) * r, y + r + cos(d) * r, c);
    return this;
}

Graphics* Graphics::fill_circle(int x, int y, int r, int c)
{
    for (int yy = -r; yy < r; yy++)
        for (int xx = -r; xx < r; xx++)
            if (yy * yy + xx * xx < r * r)
                set_pixel(x + r + xx, y + r + yy, c);
    return this;
}

Graphics* Graphics::draw_line(int x0, int y0, int x1, int y1, int c)
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
    return this;
}

Graphics* Graphics::draw_bitmap(int x, int y, Bitmap* b)
{
    for (int yy = 0; yy < b->height; yy++)
        for (int xx = 0; xx < b->width; xx++) {
            int* p = (int*)(b->get_pixels()) + xx + yy * b->width;
            set_pixel(x + xx, y + yy, *p);
        }
    return this;
}


Graphics* Graphics::draw_string(int x, int y, char* str[], int c)
{
    return this;
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
    return (int)((((c1 & 0xff00ff) * uf + (c2 & 0xff00ff) * a) & 0xff00ff00) |
                (((c1 & 0x00ff00) * uf + (c2 & 0x00ff00) * a) & 0x00ff0000)) >> 8;
}

static void col_bl(int* c1, int c2, byte a)
{
    uint cc1 = (uint)*c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    *c1 = (int)((((*c1 & 0xff00ff) * uf + (c2 & 0xff00ff) * a) & 0xff00ff00) |
               (((*c1 & 0x00ff00) * uf + (c2 & 0x00ff00) * a) & 0x00ff0000)) >> 8;
}
