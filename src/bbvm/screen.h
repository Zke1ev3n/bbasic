#pragma once

#include "config.h"
#include "sdl.h"

typedef uint32_t Uint32;
typedef uint8_t Uint8;
struct SDL_Window;
struct SDL_Surface;
struct SDL_Point;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_RWops;

class Screen
{
private:
    int width, height;
    int FontWidth, FontHeigth;
    SDL_Window *MainWnd;
    SDL_Surface *ScreenSurface, *buffer;
    SDL_Surface *screen_surface_;
    void *Font, *DebugFont;
    void *RefreshThread;
    char *FontFile;
    bool Transparent;
    Uint32 TextColor, BackgroundColor;
    Point OutputPosition;

    void __set_font(const char *FontFile, const int Size);
    Rect ShowText(SDL_Surface *Text, int x, int y, int width, int height, SDL_Surface *Dest);
    bool IsUTF8(const void *Str, long Size);
    void CheckPosition();
    void DrawDebugLayer(SDL_Surface *dst, float FPS);
public:
    Screen(int width, int height);
    Screen(int width, int height, SDL_Surface* screen_surface);
    ~Screen();

    void StartRefreshThread();
    void Refresh(Rect *RefRect = NULL);
    void Delay(int ticks);
    void SetScreenSize(unsigned int width, unsigned int height);
    void GetScreenSize(int *width, int *height);
    void CleanScreen();
    void Display(const char *Text, int x = -1, int y = -1);
    void Display(const int Integer, int x = -1, int y = -1);
    void Display(const float Float, int x = -1, int y = -1);
    void Display(const char Charactor, int x = -1, int y = -1);
    void NewLine();
    void SetTransparent(bool value);
    Point GetDispPosition();
    void SetDispPosition(int x, int y);
    SDL_Surface *GetScreenSurface();
    void SetTextLocation(int l, int r);
    void SetTextColor(Uint32 FrontColor, Uint32 BackColor);
    void SetFont(int FontID);
    int GetFontWidth();
    int GetFontHeigth();
    SDL_Window *GetMainWindow();

};
