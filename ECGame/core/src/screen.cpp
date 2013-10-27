#include "Screen.h"

Screen::Screen(uint w, uint h) 
{
    width = w;
    height = h;
    surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    clear(0);
}

Screen::~Screen(void)
{
    delete surface;
}

SDL_Surface* Screen::get_surface(void)
{
    return surface;
}

void Screen::set_pixel(int x, int y, byte r, byte g, byte b)
{
    unsigned int* pixel = (unsigned int*)(surface->pixels) + x + y * width;
    *pixel = SDL_MapRGB(surface->format, r, g, b);
}

void Screen::set_pixel(int x, int y, int c)
{
    if (x < 0 | y < 0 | x >= width | y >= height)
        return;
    set_pixel(x, y, INTRGB(c));
}

int Screen::get_pixel(int x, int y)
{
    return 0; // TODO: Work out how to get the colour of a pixel currently on the screen
}

void Screen::clear(int c)
{
    for (int i = 0; i < width * height; i++) {
        unsigned int* pixel = (unsigned int*)(surface->pixels) + i;
        *pixel = SDL_MapRGB(surface->format, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff);
    }
}
    
void Screen::draw_rectangle(int x, int y, int w, int h, int c, int t)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            if (yy < t | yy >= h - t | xx < t | xx >= w - t)
                set_pixel(x + xx, y + yy, c);
}

void Screen::fill_rectangle(int x, int y, int w, int h, int c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            set_pixel(x + xx, y + yy, c);
}

void Screen::draw_circle(int x, int y, int r, int c)
{
    for (double d = 0.0; d < PI * 2.0; d += PI / 180.0)
        set_pixel(x + r + sin(d) * r, y + r + cos(d) * r, c);
}

void Screen::fill_circle(int x, int y, int r, int c)
{
    for (int yy = -r; yy < r; yy++)
        for (int xx = -r; xx < r; xx++)
            if (yy * yy + xx * xx < r * r)
                set_pixel(x + r + xx, y + r + yy, c);
}

void Screen::draw_line(int x0, int y0, int x1, int y1, int c)
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

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
using namespace boost::python;

// Boost.python definitions to expose classes to Python
BOOST_PYTHON_MODULE(screen) {
    boost::python::class_<Screen>("Screen", init<unsigned int, unsigned int>())
    ;
};


