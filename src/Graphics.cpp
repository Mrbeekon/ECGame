#include "Graphics.hpp"
#include "AsciiFont.hpp" // Included here so that it isn't included for any
                         // includers of Graphics.hpp (many)

/*** Graphics ***/

Graphics::Graphics(Bitmap* b) 
{
    bitmap = b;
}

void Graphics::set_pixel(int x, int y, byte r, byte g, byte b)
{
    bitmap->set_pixel(x, y, r, g, b);
}

void Graphics::set_pixel(int x, int y, int c)
{
    bitmap->set_pixel(x, y, c);
}

int Graphics::get_pixel(int x, int y)
{
    return bitmap->get_pixel(x, y);
}

void Graphics::clear(int c)
{
    for (uint i = 0; i < bitmap->width * bitmap->height; i++) {
        int* p = (int*)(bitmap->get_pixels()) + i;
        *p = c;
    }
}
    
void Graphics::draw_rectangle(int x, int y, int w, int h, int c, int t)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            if ((yy < t) | (yy >= h - t) | (xx < t) | (xx >= w - t))
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

void Graphics::draw_bitmap_unscaled(int x, int y, Bitmap* b)
{
    for (uint yy = 0; yy < b->height; yy++) {
        for (uint xx = 0; xx < b->width; xx++) {
            set_pixel(x + xx, y + yy, b->get_pixel(xx, yy));
        }
    }
}

void Graphics::draw_bitmap(int x, int y, int width, int height, Bitmap* b, ScaleType st)
{
    switch (st) {
    case SCALETYPE_NONE: 
        draw_bitmap_unscaled(x, y, b);
        break;
    case SCALETYPE_TILE: 
        _draw_bitmap__scaletype_tile(x, y, width, height, b);
        break;
    case SCALETYPE_CENTRE:
        _draw_bitmap__scaletype_centre(x, y, width, height, b); 
        break;
    case SCALETYPE_STRETCH:
        _draw_bitmap__scaletype_stretch(x, y, width, height, b);
        break;
    case SCALETYPE_ZOOM: 
        _draw_bitmap__scaletype_zoom(x, y, width, height, b);
        break;
    }
}

void Graphics::draw_string(int x, int y, const char* str, int c)
{
    // i is the index of the current character in the string,
    // j is the horizontal position of the current character on screen
    // k is the vertical position of the current character on screen
    for (uint i = 0, j = 0, k = 0; i < strlen(str); i++, j++) {
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
                    set_pixel(xx + x + (j << 3), yy + y + k * 12, 
                              ((b[yy] >> xx) & 0x1) == 0x1 ? c : 0);
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

void Graphics::_draw_bitmap__scaletype_none(int x, int y, int width, int height, Bitmap* b)
{
    for (int yy = 0; yy < height; yy++) {
        for (int xx = 0; xx < width; xx++) {
            set_pixel(x + xx, y + yy, b->get_pixel(xx, yy));
        }
    }
}

void Graphics::_draw_bitmap__scaletype_tile(int x, int y, int width, int height, Bitmap* b)
{
    for (int yy = 0; yy < height; yy++) {
        for (int xx = 0; xx < width; xx++) {
            set_pixel(x + xx, y + yy, b->get_pixel(xx % b->width, yy % b->height));
        }
    }
}

void Graphics::_draw_bitmap__scaletype_centre(int x, int y, int width, int height, Bitmap* b)
{
    // Unimplemented
}

void Graphics::_draw_bitmap__scaletype_stretch(int x, int y, int width, int height, Bitmap* b)
{
    // Unimplemented
}

void Graphics::_draw_bitmap__scaletype_zoom(int x, int y, int width, int height, Bitmap* b)
{
    // Unimplemented
}

/* Global Functions */

int col_add(int c1, int c2)
{
    int c = (c1 & 0xfefefe) + (c2 & 0xfefefe);
    return c | ((c >> 8) & 0x010101) * 0xFF;
}

void col_add(int* c1, int c2)
{
    int c = (*c1 & 0xfefefe) + (c2 & 0xfefefe);
    *c1 = c | ((c >> 8) & 0x010101) * 0xFF;
}

int col_blh(int c1, int c2)
{
    return ((c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

void col_blh(int* c1, int c2)
{
    *c1 = ((*c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

int col_bl(int c1, int c2, byte a)
{
    uint cc1 = (uint)c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    return (int)
            ((((cc1 & 0xff00ff) * uf + (cc2 & 0xff00ff) * a) & 0xff00ff00) |
            (((cc1 & 0x00ff00) * uf + (cc2 & 0x00ff00) * a) & 0x00ff0000)) >> 8;
}

void col_bl(int* c1, int c2, byte a)
{
    uint cc1 = (uint)*c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    *c1 = (int)
            ((((cc1 & 0xff00ff) * uf + (cc2 & 0xff00ff) * a) & 0xff00ff00) |
            (((cc1 & 0x00ff00) * uf + (cc2 & 0x00ff00) * a) & 0x00ff0000)) >>8;
}
