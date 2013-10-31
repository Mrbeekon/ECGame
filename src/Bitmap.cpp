#include "Bitmap.hpp"

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

int* Bitmap::get_pixels_int(void)
{
    return (int*)pixels;
}

void Bitmap::set_pixel(int x, int y, byte r, byte g, byte b)
{
    int* p = (int*)(pixels) + x + y * width;
    *p = RGBINT(r, g, b);
}

void Bitmap::set_pixel(int x, int y, int c)
{
    if ((x < 0) | (y < 0) | (x >= (int)width) | (y >= (int)height))
        return;
    set_pixel(x, y, INTRGB(c));
}

int Bitmap::get_pixel(int x, int y)
{
    return (int)((int*)(pixels))[x + y * width];
}

Graphics* Bitmap::create_graphics(void)
{
    return new Graphics(this);
}

void Bitmap::destroy(void)
{
    delete this;
}
