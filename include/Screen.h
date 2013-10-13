#include <SDL/SDL.h>

class Screen
{
public:
    int width, height;
    Screen(int w, int h); 
    ~Screen(void);
    void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    void SetPixel(int x, int y, int c);
    void Clear(int c);  
    void DrawRectangle(int x, int y, int w, int h, int fc, int bc, int bt);
    void DrawCircle(int x, int y, int r, int c);
    void DrawLine(int x0, int y0, int x1, int y1, int c);
    SDL_Surface* GetSurface(void);
private:	
    SDL_Surface* surface;
};
