//
// Created by liangyulin on 2021/6/21.
//
// ---- SDL2Function ----
#include "sdl.h"

void SDL2Function::DestroyRenderer(SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
}

SDL_Surface *SDL2Function::CreateRGBSurface(Uint32 flags, int width, int height)
{
    return SDL_CreateRGBSurface(flags, width, height, 32, 0, 0, 0, 0);
}

SDL_PixelFormat *SDL2Function::GetFormat(SDL_Surface *surface)
{
    return surface->format;
}

Uint32 SDL2Function::MapRGB(const SDL_PixelFormat *format, Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_MapRGB(format, r, g, b);
}

void SDL2Function::FreeSurface(SDL_Surface *surface)
{
    SDL_FreeSurface(surface);
}

SDL_Surface *SDL2Function::LoadBMP_RW(SDL_RWops *src, int freesrc)
{
    return SDL_LoadBMP_RW(src, freesrc);
}

SDL_RWops *SDL2Function::RWFromConstMem(const void *mem, int size)
{
    return SDL_RWFromConstMem(mem, size);
}

int SDL2Function::GetSurfaceWidth(SDL_Surface *surface)
{
    return surface->w;
}

int SDL2Function::GetSurfaceHeight(SDL_Surface *surface)
{
    return surface->h;
}

void *SDL2Function::GetSurfacePixels(SDL_Surface *surface)
{
    return surface->pixels;
}

bool SDL2Function::MustLock(SDL_Surface *surface)
{
    return MustLock(surface);
}

int SDL2Function::LockSurface(SDL_Surface *surface)
{
    return SDL_LockSurface(surface);
}

void SDL2Function::UnlockSurface(SDL_Surface *surface)
{
    SDL_UnlockSurface(surface);
}

SDL_Renderer *SDL2Function::CreateSoftwareRenderer(SDL_Surface * surface)
{
    return SDL_CreateSoftwareRenderer(surface);
}

int SDL2Function::SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int SDL2Function::GetRenderDrawColor(SDL_Renderer *renderer, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    return SDL_GetRenderDrawColor(renderer, r, g, b, a);
}

int SDL2Function::GetAllowCharNum(const char *str)
{
    //int FreeChar = 0, len = strlen(str);
    int FreeChar = 0;
    int len = Utils::GetGB2312Count(str);
    int fw = scn->GetFontWidth(), sw, sh, x = scn->GetDispPosition().x;
    scn->GetScreenSize(&sw, &sh);
    for (int i = 0; i < len && x <= sw && str[i] != '\n'; i++)
    {
        FreeChar++; x += fw;
        if ((str[i - 1] & 0x80) != 0) { FreeChar++; i++; x += fw; }
    }
    return FreeChar;
}

// ---- SDL2Draw ----

int SDL2Draw::FillRect(SDL_Surface *dst, const Rect *rect, Uint32 color)
{
    int retv;
    if (rect != NULL)
    {
        SDL_Rect _rect;
        _rect.x = rect->x; _rect.y = rect->y; _rect.w = rect->w; _rect.h = rect->h;
        retv = SDL_FillRect(dst, &_rect, color);
    } else {
        retv = SDL_FillRect(dst, NULL, color);
    }
    return retv;
}

int SDL2Draw::RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    int retv = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    return retv;
}

void SDL2Draw::RenderPresent(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}

int SDL2Draw::RenderDrawRect(SDL_Renderer *renderer, const Rect *rect)
{
    SDL_Rect _rect;
    _rect.x = rect->x; _rect.y = rect->y; _rect.w = rect->w; _rect.h = rect->h;
    return SDL_RenderDrawRect(renderer, &_rect);
}

int SDL2Draw::BlitSurfaceWithColorKey(SDL_Surface *src, const Rect *srcrect, SDL_Surface *dst, Rect *dstrect, Uint32 ColorKey)
{
    SDL_Rect __src_rect, __dest_rect;
    int __ret_value;
    //__src_rect.x = srcrect->x; __src_rect.y = srcrect->y; __src_rect.w = srcrect->w; __src_rect.h = srcrect->h;
    //__src_rect.x = dstrect->x; __src_rect.y = dstrect->y; __src_rect.w = dstrect->w; __src_rect.h = dstrect->h;
    if(srcrect != NULL) {
        __src_rect.x = srcrect->x; __src_rect.y = srcrect->y; __src_rect.w = srcrect->w; __src_rect.h = srcrect->h;
    }
    __dest_rect.x = dstrect->x; __dest_rect.y = dstrect->y; __dest_rect.w = dstrect->w; __dest_rect.h = dstrect->h;
    SDL_SetColorKey(src, SDL_TRUE, ColorKey);
    if(srcrect != NULL) {
        __ret_value = SDL_BlitSurface(src, &__src_rect, dst, &__dest_rect);
    }else{
        __ret_value = SDL_BlitSurface(src, NULL, dst, &__dest_rect);
    }
    //int __ret_value = SDL_BlitSurface(src, &__src_rect, dst, &__dest_rect);
    SDL_SetColorKey(src, SDL_FALSE, ColorKey);
    return __ret_value;
}


