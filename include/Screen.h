#pragma once
#include "stdafx.h"

class Screen
{
public:
    int width, height;
    Screen(int w, int h); 
    ~Screen(void);
    void SetPixel(int x, int y, byte r, byte g, byte b);
    void SetPixel(int x, int y, int c);
    void Clear(int c);  
    void DrawRectangle(int x, int y, int w, int h, int fc, int bc, int bt);
    void DrawCircle(int x, int y, int r, int c);
    void DrawLine(int x0, int y0, int x1, int y1, int c);
    SDL_Surface* GetSurface(void);
    static int ColFromRGB(byte r, byte g, byte b);
    static int ColFromARGB(byte a, byte r, byte g, byte b);
private:	
    SDL_Surface* surface;
};
