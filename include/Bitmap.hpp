#ifndef BITMAP_H
#define BITMAP_H

#include "ECStd.hpp"
#include "Graphics.hpp"

// Forward declare the Graphics class
class Graphics;

class Bitmap
{
public:
    uint width, height;

    // Create an empty bitmap of the specified width and height
    Bitmap(uint width, uint height);

    // Specify an existing pixel array to create the bitmap from
    Bitmap(uint width, uint height, void* pixels);
    
    // Get the pixels of the bitmap
    void* get_pixels(void);

    // Get the pixels of the bitmap as an int* (saves an extra cast)
    int* get_pixels_int(void);

    // Set the colour of a pixel in the bitmap
    // specifying red, green, and blue values
    void set_pixel(int x, int y, byte r, byte g, byte b);

    // Set the colour of a pixel in the bitmap, using an integer colour.
    // Unlike set_pixel(int, int, byte, byte, byte), this has checks to
    // ensure that the pixel is set within the bounds of the bitmap.
    void set_pixel(int x, int y, int c);

    // Returns the integer colour of a pixel in the bitmap
    int get_pixel(int x, int y);

    // Create a Graphics object for this bitmap
    Graphics* create_graphics(void);

    // Destroy the bitmap object
    void destroy(void);
private:
    void* pixels;
};

#endif
