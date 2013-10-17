#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <cmath>
#include "SDL/SDL.h"
#include "c_types.h"
#include "Colour.h"

// Used by certain methods to denote transparency
#define RGBTRANSPARENT   0xFF00FF

class Screen
{
public:
    int width, height;
    Screen(uint w, uint h); 
    ~Screen(void);

    // Set the colour of a pixel on the screen
    // specifying red, green, and blue values
    void set_pixel(int x, int y, byte r, byte g, byte b);

    // Set the colour of a pixel on the screen, using an integer colour
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

    // Returns a pointer to the SDL_Surface
    SDL_Surface* get_surface(void);
private:	
    SDL_Surface* surface;
};

#endif
