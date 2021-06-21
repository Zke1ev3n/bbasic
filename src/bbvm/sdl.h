//
// Created by liangyulin on 2021/6/21.
//

#ifndef BBASIC_SDL_H
#define BBASIC_SDL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Rect
{
    int x;
    int y;
    int w;
    int h;
} Rect;

class SDL2Function
{
public:
    static void DestroyRenderer(SDL_Renderer *renderer);
    static SDL_Surface *CreateRGBSurface(Uint32 flags, int width, int height);
    static SDL_PixelFormat *GetFormat(SDL_Surface *surface);
    static Uint32 MapRGB(const SDL_PixelFormat *format, Uint8 r, Uint8 g, Uint8 b);
    static void FreeSurface(SDL_Surface *surface);
    static SDL_Surface *LoadBMP_RW(SDL_RWops *src, int freesrc);
    static SDL_RWops *RWFromConstMem(const void *mem, int size);
    static int GetSurfaceWidth(SDL_Surface *surface);
    static int GetSurfaceHeight(SDL_Surface *surface);
    static void *GetSurfacePixels(SDL_Surface *surface);
    static bool MustLock(SDL_Surface *surface);
    static int LockSurface(SDL_Surface * surface);
    static void UnlockSurface(SDL_Surface * surface);
    static SDL_Renderer *CreateSoftwareRenderer(SDL_Surface *surface);
    static int SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    static int GetRenderDrawColor(SDL_Renderer *renderer, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
    static int GetAllowCharNum(const char *str);
};

class SDL2Draw
{
public:
    static int FillRect(SDL_Surface *dst, const Rect *rect, Uint32 color);
    static int BlitSurfaceWithColorKey(SDL_Surface *src, const Rect *srcrect, SDL_Surface *dst, Rect *dstrect, Uint32 ColorKey);
    static int RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
    static void RenderPresent(SDL_Renderer *renderer);
    static int RenderDrawRect(SDL_Renderer *renderer, const Rect *rect);
};

#endif //BBASIC_SDL_H
