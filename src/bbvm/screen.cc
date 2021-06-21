#if defined(__linux__) || defined(__APPLE__)
#	include <iconv.h>
#else
#	include <windows.h>
#endif
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>
#include "screen.h"
#include "utils.h"

#define DEBUG_LAYER 0

Screen::Screen(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    this->ScreenSurface = NULL;
    this->buffer = NULL;
    this->Transparent = false;
    this->FontFile = NULL;

	this->MainWnd = SDL_CreateWindow(VERSION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(this->MainWnd == NULL)
	{
		Utils::Error("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return ;
	}
	if (TTF_Init() == -1)
	{
		Utils::Error("Initialize ttf failure");
	} else {
		SetFont(0);
#if defined(__linux__) || defined(__APPLE__)
        this->DebugFont = TTF_OpenFont("./resource/simkai.ttf", 12);
#else
        this->DebugFont = TTF_OpenFont("C:\\Windows\\Fonts\\CONSOLA.TTF", 12);
#endif
		SetScreenSize(width, height);

		this->TextColor = SDL_MapRGB(this->ScreenSurface->format, 0xFF, 0xFF, 0xFF);
		this->BackgroundColor = SDL_MapRGB(this->ScreenSurface->format, 0x00, 0x00, 0x00);
	}
}

void Screen::Refresh(Rect *RefRect)
{
	static SDL_mutex *mutex;
	if (mutex == NULL)
		mutex = SDL_CreateMutex();
	//if (SDL_LockMutex(mutex) == 0)
	{
		int _w, _h;
		SDL_GetWindowSize(this->MainWnd, &_w, &_h);
		double Multi = (double)_w / this->width;
		SDL_Rect _rect, _r;
		_r.x = ((RefRect == NULL)? 0 : RefRect->x);
		_r.y = ((RefRect == NULL)? 0 : RefRect->y);
		_r.w = ((RefRect == NULL)? this->width : RefRect->w);
		_r.h = ((RefRect == NULL)? this->height : RefRect->h);
		_rect.x = _r.x * Multi;
		_rect.y = _r.y * Multi;
		_rect.w = _r.w * Multi;
		_rect.h = _r.h * Multi;
		SDL_BlitScaled(this->ScreenSurface, &_r, this->buffer, &_rect);

#if DEBUG_LAYER == 1
		DrawDebugLayer(this->buffer, 1000.0f / (SDL_GetTicks() - StartTime));
#endif // DEBUG_LAYER
		SDL_UpdateWindowSurface(this->MainWnd);
		SDL_UnlockMutex(mutex);
	}
}

void Screen::SetScreenSize(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    SDL_SetWindowSize(this->MainWnd, width, height);
    this->buffer = SDL_GetWindowSurface(this->MainWnd);
	this->ScreenSurface = SDL2Function::CreateRGBSurface(0, (int)width, (int)height);
	CleanScreen();
}

Screen::~Screen()
{
	//SDL2Input::HiddenKeyboard();
    //Destroy window
	SDL_DestroyWindow(this->MainWnd);
	//Quit SDL subsystems
	TTF_CloseFont((TTF_Font*)this->Font);
	TTF_Quit();
	SDL_Quit();
}

void Screen::DrawDebugLayer(SDL_Surface *dst, float FPS)
{
	SDL_Rect __debug_rect;
	SDL_Surface *layer;
	SDL_Color fg = {0, 0, 0}, bg = {0xFF, 0xFF, 0xFF};
	char buf[255];

	sprintf(buf, "[Debug Layer]");
	layer = TTF_RenderText_Shaded((TTF_Font*)this->DebugFont, buf, fg, bg);
	__debug_rect.w = layer->w; __debug_rect.h = layer->h;
	__debug_rect.x = dst->w - layer->w; __debug_rect.y = 0;
	SDL_BlitSurface(layer, NULL, dst, &__debug_rect);

	sprintf(buf, "FPS: %f", FPS);
	layer = TTF_RenderText_Shaded((TTF_Font*)this->DebugFont, buf, fg, bg);
	__debug_rect.x = dst->w - layer->w; __debug_rect.y += __debug_rect.h;
	__debug_rect.w = layer->w; __debug_rect.h = layer->h;
	SDL_BlitSurface(layer, NULL, dst, &__debug_rect);

	SDL_FreeSurface(layer);
	return ;
}

void Screen::__set_font(const char *FontFile, const int Size)
{
	if (this->FontFile != NULL)
		free(this->FontFile);
	if (FontFile != NULL)
		this->FontFile = strdup(FontFile);
	this->Font = TTF_OpenFont(this->FontFile, Size);
	if(this->Font == NULL) {
		Utils::Error("font open failure %s\n", SDL_GetError());
	}
	TTF_SizeText((TTF_Font*)this->Font, " ", &this->FontWidth, &this->FontHeigth);
}

void Screen::GetScreenSize(int *width, int *height)
{
	(*width) = this->width;
	(*height) = this->height;
}

Rect Screen::ShowText(SDL_Surface *Text, int x, int y, int width, int height, SDL_Surface *Dest)
{
	SDL_Rect textPosition;
	textPosition.x = x; textPosition.y = y;
	textPosition.w = (width == 0)? Text->w : width;
	textPosition.h = (height == 0)? Text->h : height;
	if (this->Transparent == false) {
		SDL_FillRect(this->ScreenSurface, &textPosition, this->BackgroundColor);
	}
	SDL_BlitSurface(Text, NULL, Dest, &textPosition);
	this->OutputPosition.x += Text->w;
	CheckPosition();
	Rect Ref;
	Ref.x = textPosition.x;
	Ref.y = textPosition.y;
	Ref.w = textPosition.w;
	Ref.h = textPosition.h;
	return Ref;
}

void Screen::CheckPosition()
{
	if (this->OutputPosition.x >= this->ScreenSurface->w)
	{
		NewLine();
	}
	if (this->OutputPosition.y >= this->ScreenSurface->h)
	{
		this->OutputPosition.x = 0;
		this->OutputPosition.y = 0;
		CleanScreen();
	}
}

void Screen::NewLine()
{
	this->OutputPosition.y += TTF_FontHeight((TTF_Font*)this->Font) - 1;
	this->OutputPosition.x = 0;
	CheckPosition();
}

void Screen::SetTransparent(bool value)
{
	this->Transparent = value;
}

void Screen::Display(const char *Text, int x, int y)
{
	if (x >= 0) this->OutputPosition.x = x;
	if (y >= 0) this->OutputPosition.y = y;
	for (int i = 0; i < (int)strlen(Text); i++)
	{
		if (Text[i] == 10)
		{
		    //换行
			NewLine();
		} else if (Text[i] == 9) {
		    //定位
			this->OutputPosition.x += this->FontWidth * 8;
			CheckPosition();
		} else {
		    //TODO BUG
			int len = GetAllowCharNum(Text);
			int index = Utils::GetGB2312Index(Text, len);
			char *t = (char*)malloc(index + 1);
			strncpy(t, Text + i, index);
			t[index] = '\0';
			i += index - 1;
			char *text = Utils::GB2312toUTF8(t);
			free(t);
			SDL_Surface *SDLText;
			SDL_Color FrontColor;
			Uint8 r, g, b;
			SDL_GetRGB(this->TextColor, this->ScreenSurface->format, &r, &g, &b);
			FrontColor.a = 255; FrontColor.r = r; FrontColor.g = g; FrontColor.b = b;
			SDLText = TTF_RenderUTF8_Solid((TTF_Font*)this->Font, text, FrontColor);
			Rect RefRect = ShowText(SDLText, this->OutputPosition.x, this->OutputPosition.y, 0, 0, this->ScreenSurface);
			this->Refresh(&RefRect);
		}
	}
}

void Screen::Display(const int Integer, int x, int y)
{
	char buf[16];
	sprintf(buf, "%d", Integer);
	Display(buf, x, y);
	return ;
}

void Screen::Display(const float Float, int x, int y)
{
	char buf[32];
	sprintf(buf, "%f", Float);
	Display(buf, x, y);
	return ;
}

void Screen::Display(const char Charactor, int x, int y)
{
	char buf[2];
	buf[0] = Charactor; buf[1] = '\0';
	Display(buf, x, y);
	return ;
}

void Screen::CleanScreen()
{
	//Fill the surface
	SDL_FillRect(this->ScreenSurface, NULL, SDL_MapRGB(this->ScreenSurface->format, 0x00, 0x00, 0x00));
	this->OutputPosition.x = this->OutputPosition.y = 0;
	this->Refresh();
}

Point Screen::GetDispPosition()
{
	return this->OutputPosition;
}

void Screen::SetDispPosition(int x, int y)
{
	this->OutputPosition.x = x;
	this->OutputPosition.y = y;
}

void Screen::Delay(int ticks)
{
	SDL_Delay((Uint32)ticks);
}

SDL_Surface *Screen::GetScreenSurface()
{
	return this->ScreenSurface;
}

void Screen::SetTextLocation(int l, int r)
{
	SetDispPosition(this->FontWidth * (r - 1), this->FontHeigth * (l - 1));
}

void Screen::SetTextColor(Uint32 FrontColor, Uint32 BackColor)
{
	this->TextColor = SDL_MapRGB(
								this->ScreenSurface->format,
								(FrontColor & 0x0000FF) >> 0,
								(FrontColor & 0x00FF00) >> 8,
								(FrontColor & 0xFF0000) >> 16);
	this->BackgroundColor = SDL_MapRGB(
								this->ScreenSurface->format,
								(BackColor & 0x0000FF) >> 0,
								(BackColor & 0x00FF00) >> 8,
								(BackColor & 0xFF0000) >> 16);
}

void Screen::SetFont(int FontID)
{
#if defined(__linux__) || defined(__APPLE__)
	static const char *__font_files[] = {"./resource/simsun.ttc", "./resource/simkai.ttf", "./resource/simhei.ttf"};
#else
	static const char *__font_files[] = {"C:\\Windows\\Fonts\\simsun.ttc", "C:\\Windows\\Fonts\\simkai.ttf", "C:\\Windows\\Fonts\\simhei.ttf"};
#endif
	static const int __font_size[] = {12, 16, 24};
	int Size = FontID / 3, Type = FontID % 3;
	char *FontType = strdup(__font_files[Type]);
	__set_font(FontType, __font_size[Size]);
}

int Screen::GetFontWidth()
{
	return this->FontWidth;
}

int Screen::GetFontHeigth()
{
	return this->FontHeigth;
}

SDL_Window *Screen::GetMainWindow()
{
	return this->MainWnd;
}

int Screen::GetAllowCharNum(const char *str)
{
    //int FreeChar = 0, len = strlen(str);
    int FreeChar = 0;
    int len = Utils::GetGB2312Count(str);
    int fw = GetFontWidth(), sw, sh, x = GetDispPosition().x;
    GetScreenSize(&sw, &sh);
    for (int i = 0; i < len && x <= sw && str[i] != '\n'; i++)
    {
        FreeChar++; x += fw;
        if ((str[i - 1] & 0x80) != 0) { FreeChar++; i++; x += fw; }
    }
    return FreeChar;
}