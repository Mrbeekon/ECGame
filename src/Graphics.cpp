#include "Graphics.hpp"
#include "AsciiFont.hpp"
// Included here so that it isn't included for any
// includers of Graphics.hpp (many)

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
    case SCALETYPE_STRETCH:
        _draw_bitmap__scaletype_stretch(x, y, width, height, b);
        break;
    }
}

void Graphics::draw_font_glyph(int x, int y, char ch, GlyphAtt ga, byte* buff)
{
    memcpy(buff, ASCIIFONT + (ch - 32) * 12, 12);
    for (int yy = 0; yy < 12; yy++) {
        for (int xx = 0; xx < 8; xx++) {
            if (((buff[yy] >> xx) & 0x1) == 0x1) {
                set_pixel(xx + x, yy + y, ga.col);
            }
        }
    }
}

void Graphics::draw_font_glyph(int x, int y, char ch, GlyphAtt ga)
{
    byte b[12];
    draw_font_glyph(x, y, ch, ga, b);
}

void Graphics::draw_string(int x, int y, std::string str, int c)
{
    byte b[12]; // Storage place for the current character's pixel bits
    uint len = str.length(); // Ensure we're not measuring the length of the
                             // string with every itteration of the loop
    GlyphAtt ga;
    ga.col = c;
    // i is the index of the current character in the string,
    // j is the horizontal position of the current character on screen
    // k is the vertical position of the current character on screen
    for (uint i = 0, j = 0, k = 0; i < len; i++) {
        switch (str[i]) {
        case '\n':  // newline
            j = 0;
            k++;
            break;
        case '\t':  // tab
            j += TABSIZE - (j % TABSIZE);
            break;
        case '&':
            if (str[++i] == '{') {
                std::string andescstr; // Store and-escape contents
                while (str[++i] != '}') {
                    andescstr.append(&str[i], &str[i+1]);
                }
                if (andescstr[0] == '0')
                    ga.col = COL[utils::hex_str_to_int(andescstr)];
                break;
            }
            else i--;
        default:
            draw_font_glyph(x + (j << 3), y + k * 12, str[i], ga, b);
            j++;
            break;
        }
    }    
}

void Graphics::destroy(void)
{
    delete this;
}

/* String Related Functions */

int Graphics::measure_string_longest_line(std::string str)
{
    ushort longest = 0;
    uint len = str.length();
    bool andescaped = false;
    for (uint i = 0, j = 0; i <= len; i++) {
        switch (str[i]) {
        case '\0':
        case '\n':
            if (j > longest)
                longest = j;
            j = 0;
            break;
        case '\t':
            j += TABSIZE - (j % TABSIZE);
            break;
        case '}':
            if (andescaped) {
                andescaped = false;
                break; 
            }
        case '&':
            if (str[i + 1] == '{') {
                andescaped = true;
                break;
            }
        default:
            if (!andescaped)
                j++;
            break;
        }
    }
    return longest;
}

int Graphics::measure_string_line_count(std::string str)
{
    ushort count = 0;
    uint len = str.length(); 
    for (uint i = 0; i < len; i++) {
        if (str[i] == '\n' || str[i] == '\0')
            count++;
    }
    return count;
}

int Graphics::measure_string_width(std::string str)
{
    return measure_string_longest_line(str) << 3;
}

int Graphics::measure_string_height(std::string str)
{
    return measure_string_line_count(str) * 12;
}

/* Static Functions */

int Graphics::col_add(int c1, int c2)
{
    int c = (c1 & 0xfefefe) + (c2 & 0xfefefe);
    return c | ((c >> 8) & 0x010101) * 0xFF;
}

void Graphics::col_add(int* c1, int c2)
{
    int c = (*c1 & 0xfefefe) + (c2 & 0xfefefe);
    *c1 = c | ((c >> 8) & 0x010101) * 0xFF;
}

int Graphics::col_blh(int c1, int c2)
{
    return ((c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

void Graphics::col_blh(int* c1, int c2)
{
    *c1 = ((*c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;
}

int Graphics::col_bl(int c1, int c2, byte a)
{
    uint cc1 = (uint)c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    return (int)
            ((((cc1 & 0xff00ff) * uf + (cc2 & 0xff00ff) * a) & 0xff00ff00) |
            (((cc1 & 0x00ff00) * uf + (cc2 & 0x00ff00) * a) & 0x00ff0000)) >> 8;
}

void Graphics::col_bl(int* c1, int c2, byte a)
{
    uint cc1 = (uint)*c1;
    uint cc2 = (uint)c2;
    int uf = 256 - a;
    *c1 = (int)
            ((((cc1 & 0xff00ff) * uf + (cc2 & 0xff00ff) * a) & 0xff00ff00) |
            (((cc1 & 0x00ff00) * uf + (cc2 & 0x00ff00) * a) & 0x00ff0000)) >>8;
}

/* Private Functions */

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

void Graphics::_draw_bitmap__scaletype_stretch(int x, int y, int width, int height, Bitmap* b)
{
    // Unimplemented
}
