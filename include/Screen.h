#pragma once
#include "stdafx.h"

#define RGBTRANSPARENT      0xFF00FF    // Used by certain methods to denote transparency, eg: the fill colour on DrawRectangle()

class Screen
{
public:
    int width, height;
    Screen(int w, int h); 
    ~Screen(void);
    void SetPixel(int x, int y, byte r, byte g, byte b);        // Set the colour of a pixel on the screen, specifying red, green, and blue values
    void SetPixel(int x, int y, int c);                         // Set the colour of a pixel on the screen, using an integer colour
    int GetPixel(int x, int y);                                 // Returns the integer colour of a pixel on the screen
    void Clear(int c);                                          // Clear the screen with a solid colour
    void DrawRectangle(int x, int y, int w, int h, int fc, int bc, int bt); // fc: fill colour, bc: border colour, bt: border thickness
    void DrawCircle(int x, int y, int r, int c);                // Draw a filled circle with radius r
    void DrawLine(int x0, int y0, int x1, int y1, int c);       // Draw a line between (x0, y0) and (x1, y1)
    SDL_Surface* GetSurface(void);                              // Returns a pointer to the SDL_Surface
private:	
    SDL_Surface* surface;
};
