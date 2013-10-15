#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "stdafx.h"

#define RGBTRANSPARENT      0xFF00FF                            // Used by certain methods to denote transparency

class Screen
{
public:
    int width, height;
    Screen(int w, int h); 
    ~Screen(void);
    void set_pixel(int x, int y, byte r, byte g, byte b);       // Set the colour of a pixel on the screen, specifying red, green, and blue values
    void set_pixel(int x, int y, int c);                        // Set the colour of a pixel on the screen, using an integer colour
    int get_pixel(int x, int y);                                // Returns the integer colour of a pixel on the screen
    void clear(int c);                                          // Clear the screen with a solid colour
    void draw_rectangle(int x, int y, int w, int h, int c, int t);  // Draws the outline of a rectangle
    void fill_rectangle(int x, int y, int w, int h, int c);     // Fills in a rectangular area
    void draw_circle(int x, int y, int r, int c);               // Draw a filled circle with radius r
    void draw_line(int x0, int y0, int x1, int y1, int c);      // Draw a line between (x0, y0) and (x1, y1)
    SDL_Surface* get_surface(void);                             // Returns a pointer to the SDL_Surface
private:	
    SDL_Surface* surface;
};

#endif
