#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "renderer.h"
#include "utils.h"

#define TRANS_COLOR_END(C) ((((C) & 0xFF) << 16) | ((C) & 0xFF00) | (((C) & 0xFF0000) >> 16))
#define WILL_REFRESH(_x,_y,_w,_h) \
	{ if (SurfaceHandle == -1) { \
		Rect _rr; _rr.x = (_x); _rr.y = (_y); _rr.w = (_w); _rr.h = (_h); \
		scn->Refresh(&_rr); \
	} }
#define MIN(A,B) (((A)<=(B))?(A):(B))

Renderer::Renderer()
{
	for (int i = 0; i < 9; i++)
	{
		this->SurfacePool[i] = NULL;
	}
	for (int i = 0; i < 10; i++)
	{
		this->DrawRenderer[i] = NULL;
	}
	SetPenColor(-1, 0xFFFFFF);
}

Renderer::~Renderer()
{
	for (int i = 0; i < 10; i++)
		if (this->DrawRenderer[i] != NULL)
			SDL2Function::DestroyRenderer(this->DrawRenderer[i]);
}

SDL_Surface *Renderer::CreateSurface(int width, int height)
{
	return SDL2Function::CreateRGBSurface(0, width, height);
}

int Renderer::AllocSurface()
{
	for (int i = 0; i < 9; i++)
	{
		if (this->SurfacePool[i] == NULL)
		{
			int width, height;
			scn->GetScreenSize(&width, &height);
			this->SurfacePool[i] = CreateSurface(width, height);
			SDL2Draw::FillRect(this->SurfacePool[i], NULL, SDL2Function::MapRGB(SDL2Function::GetFormat(this->SurfacePool[i]),0x00, 0x00, 0x00));
			return i;
		}
	}
	return -1;
}

void Renderer::FreeSurface(int index)
{
	if (index >= 0 && index < 9)
	{
		SDL2Function::FreeSurface(this->SurfacePool[index]);
		this->SurfacePool[index] = NULL;
	}
}

int Renderer::RequestResourceHandle()
{
	int i = 0;
	for(map<int, SDL_Surface*>::iterator it = this->ResPool.begin(); it != this->ResPool.end(); it++, i++)
	{
		if (it->second == NULL)
		{
			return it->first;
		}
	}
	this->ResPool[i] = NULL;
	return i;
}

int Renderer::LoadPicture(const char *FileName, unsigned int index)
{
    //replace
    const char* utf8_filename = Utils::GB2312toUTF8(FileName);
    //string str_filename = new string
	FILE *fp = fopen(utf8_filename, "rb");
	if (fp == NULL)
	{
		return -1;
	}

	unsigned int ResOffset = 4 * (index - 1), Size, ResCount;
	unsigned short width, height;
	fread(&ResCount, 4, 1, fp);
	fseek(fp, ResOffset, SEEK_CUR);
	fread(&ResOffset, 4, 1, fp);
	fseek(fp, ResOffset, SEEK_SET);
	fread(&Size, 4, 1, fp);
	//TODO
	Size = Size - 12;
	fread(&width,2, 1, fp);
    fread(&height, 2, 1, fp);
    //TODO
    fseek(fp, 4, SEEK_CUR);
	void *data = malloc(Size);
	fread(data, 1, Size, fp);

	//这是RLB文件的读取方式
	//SDL_Surface *res = SDL2Function::LoadBMP_RW(SDL2Function::RWFromConstMem(data, Size), 1);
    int depth = 32;
    int pitch = 2*width;
    SDL_Surface *res = SDL_CreateRGBSurfaceWithFormatFrom(data, width, height, depth, pitch, SDL_PIXELFORMAT_RGB565);
    Utils::Log(SDL_GetError());
	int i = RequestResourceHandle();
	this->ResPool[i] = res;
	//Log("载入lib: 图片高宽为：%d, %d\n", height, width);
	return i;
}

void Renderer::FreePicture(int Handle)
{
	SDL_Surface *ptr = this->ResPool[Handle];
	if (ptr != NULL)
	{
		SDL2Function::FreeSurface(ptr);
		this->ResPool[Handle] = NULL;
	}
}

SDL_Surface *Renderer::GetSurface(int handle)
{
	return (handle == -1)? scn->GetScreenSurface() : this->SurfacePool[handle];
}

void Renderer::DrawPicture(int page, int pic, int dx, int dy, int w, int h, int x, int y, int mode)
{
	if (this->ResPool.find(pic)->second == NULL || (page < -1 || page > 8))
	{
		return ;
	}
	SDL_Surface *DestSurface = GetSurface(page);
	SDL_Surface *SrcSurface = this->ResPool[pic];
	Rect SrcRect, DestRect;
	SrcRect.x = x; SrcRect.y = y; SrcRect.h = h; SrcRect.w = w;
	DestRect.x = dx; DestRect.y = dy; DestRect.h = h; DestRect.w = w;

	SDL2Draw::BlitSurfaceWithColorKey(SrcSurface, &SrcRect, DestSurface, &DestRect, SDL2Function::MapRGB(SDL2Function::GetFormat(SrcSurface), 0xFF, 0x00, 0xFF));
	int SurfaceHandle = page;
	WILL_REFRESH(dx, dy, w, h);

}

void Renderer::CloneSurface(int SrcSurfaceHandle, int DestSurfaceHandle, int x, int y)
{
	SDL_Surface *SrcSurface = GetSurface(SrcSurfaceHandle), *DestSurface = GetSurface(DestSurfaceHandle);
//	Rect CloneRect;
//	CloneRect.x = 0; CloneRect.y = 0; CloneRect.w = SDL2Function::GetSurfaceWidth(SrcSurface) - x; CloneRect.h = SDL2Function::GetSurfaceHeight(SrcSurface) - y;
//
//	SDL2Draw::BlitSurfaceWithColorKey(SrcSurface, NULL, DestSurface, &CloneRect, SDL2Function::MapRGB(SDL2Function::GetFormat(SrcSurface), 0xFF, 0x00, 0xFF));
//
//	if (DestSurfaceHandle == -1)
//		scn->Refresh();
    //TODO 这里优化
    int wid = 240;
    int hgt = 320;
    int cx = 0, cy = 0;

    if(x < 0){
        cx -= x;
        wid += x;
        if(wid < 1) return;
        x = 0;
    }
    if(y < 0){
        cy -= y;
        hgt += y;
        if(hgt < 1) return;
        y = 0;
    }
    int real_wid = SDL2Function::GetSurfaceWidth(SrcSurface) - cx;
    int real_hgt = SDL2Function::GetSurfaceHeight(SrcSurface) - cy;

    wid = wid > real_wid ? real_wid : wid;
    hgt = hgt > real_hgt ? real_hgt : hgt;
    Rect SrcRect, DstRect;

    SrcRect.x = cx; SrcRect.y = cy; SrcRect.w = wid; SrcRect.h = hgt;
    DstRect.x = x; DstRect.y = y; DstRect.w = wid; DstRect.h = hgt;
	SDL2Draw::BlitSurfaceWithColorKey(SrcSurface, &SrcRect, DestSurface, &DstRect, SDL2Function::MapRGB(SDL2Function::GetFormat(SrcSurface), 0xFF, 0x00, 0xFF));

	if (DestSurfaceHandle == -1)
		scn->Refresh();

}

void Renderer::CloneSurface(int x, int y, int width, int height, int cx, int cy, int DestSurfaceHandle, int SrcSurfaceHandle)
{
    SDL_Surface *SrcSurface = GetSurface(SrcSurfaceHandle), *DestSurface = GetSurface(DestSurfaceHandle);
    Rect SrcRect, CloneRect;
    SrcRect.x = cx; SrcRect.y = cy; SrcRect.w = width; SrcRect.h = height;
    CloneRect.x = x; CloneRect.y = y; CloneRect.w = width; CloneRect.h = height;

    SDL2Draw::BlitSurfaceWithColorKey(SrcSurface, &SrcRect, DestSurface, &CloneRect, SDL2Function::MapRGB(SDL2Function::GetFormat(SrcSurface), 0xFF, 0x00, 0xFF));

    if (DestSurfaceHandle == -1)
        scn->Refresh();
}

void Renderer::FillSurface(int SurfaceHandle, int x, int y, int w, int h, int color)
{
	Rect DrawRect;
	DrawRect.x = x; DrawRect.y = y; DrawRect.w = w; DrawRect.h = h;

	SDL2Draw::FillRect(GetSurface(SurfaceHandle), &DrawRect, color);
	WILL_REFRESH(x, y, w, h);
}

Uint32 Renderer::__get_pixel(SDL_Surface *Surface, int x, int y)
{
	Uint32 pixel = *((Uint32*)SDL2Function::GetSurfacePixels(Surface) + y * SDL2Function::GetSurfaceWidth(Surface) + x);
	return TRANS_COLOR_END(pixel);
}

void Renderer::__put_pixel(SDL_Surface *Surface, int x, int y, Uint32 pixel)
{
	*((Uint32*)SDL2Function::GetSurfacePixels(Surface) + y * SDL2Function::GetSurfaceWidth(Surface) + x) = TRANS_COLOR_END(pixel);
}

void Renderer::WritePixel(int SurfaceHandle, int x, int y, int color)
{
	SDL_Surface *OptSurface = GetSurface(SurfaceHandle);
	if (SDL2Function::MustLock(OptSurface) && SDL2Function::LockSurface(OptSurface) < 0)
		return ;

    if ((x >= 0 && x < SDL2Function::GetSurfaceWidth(OptSurface)) && (y >= 0 && y < SDL2Function::GetSurfaceHeight(OptSurface)))
	{
		__put_pixel(OptSurface, x, y, color);
	}

	if (SDL2Function::MustLock(OptSurface))
		SDL2Function::UnlockSurface(OptSurface);
	WILL_REFRESH(x - 1, y - 1, 3, 3);
}

unsigned int Renderer::ReadPixel(int SurfaceHandle, int x, int y)
{
	unsigned int ColorValue = 0;
	SDL_Surface *OptSurface = GetSurface(SurfaceHandle);
	if (SDL2Function::MustLock(OptSurface) && SDL2Function::LockSurface(OptSurface) < 0)
		return 0;

    if ((x >= 0 && x < SDL2Function::GetSurfaceWidth(OptSurface)) && (y >= 0 && y < SDL2Function::GetSurfaceHeight(OptSurface)))
	{
		ColorValue = __get_pixel(OptSurface, x, y);
	}

	if (SDL2Function::MustLock(OptSurface))
		SDL2Function::UnlockSurface(OptSurface);
	return ColorValue;
}

int Renderer::GetPictureWidth(int SurfaceHandle)
{
	if (this->ResPool.find(SurfaceHandle)->second == NULL)
		return 0;
	else
		return SDL2Function::GetSurfaceWidth(this->ResPool[SurfaceHandle]);
}

int Renderer::GetPictureHeigth(int SurfaceHandle)
{
	if (this->ResPool.find(SurfaceHandle)->second == NULL)
		return 0;
	else
		return SDL2Function::GetSurfaceHeight(this->ResPool[SurfaceHandle]);
}

void Renderer::SetPenColor(int SurfaceHandle, int Color)
{
	int _handle = SurfaceHandle + 1;
	if (_handle < 0 || _handle > 10)
		return ;
	SDL_Renderer *_renderer = SDL2Function::CreateSoftwareRenderer(GetSurface(SurfaceHandle));
	SDL2Function::SetRenderDrawColor(_renderer,
							(Color & 0xFF),
							(Color & 0xFF00) >> 8,
							(Color & 0xFF0000) >> 16,
							255);
	if (this->DrawRenderer[_handle] != NULL)
		SDL2Function::DestroyRenderer(this->DrawRenderer[_handle]);
	this->DrawRenderer[_handle] = _renderer;
}

void Renderer::MovePen(int SurfaceHandle, int x, int y)
{
	int _handle = SurfaceHandle + 1;
	if (_handle < 0 || _handle > 10)
		return ;
	this->StartDrawPoint[_handle].x = x;
	this->StartDrawPoint[_handle].y = y;
}

void Renderer::DrawLine(int SurfaceHandle, int x, int y)
{
	int _handle = SurfaceHandle + 1;
	if (_handle < 0 || _handle > 10)
		return ;
	int _x = this->StartDrawPoint[_handle].x, _y = this->StartDrawPoint[_handle].y;
	SDL2Draw::RenderDrawLine(this->DrawRenderer[_handle], _x, _y, x - 1, y);
	SDL2Draw::RenderPresent(this->DrawRenderer[_handle]);
	this->StartDrawPoint[_handle].x = this->StartDrawPoint[_handle].y = 0;

	WILL_REFRESH(MIN(x, _x), MIN(y, _y), abs(x - 1 - _x), abs(y - _y));
}

void Renderer::DrawRectangle(int SurfaceHandle, int x1, int y1, int x2, int y2)
{
	int _handle = SurfaceHandle + 1;
	if (_handle < 0 || _handle > 10)
		return ;
	Rect _rect;
	_rect.x = x1, _rect.y = y1; _rect.w = x2 - x1 + 1; _rect.h = y2 - y1 + 1;
	SDL2Draw::RenderDrawRect(this->DrawRenderer[_handle], &_rect);
	SDL2Draw::RenderPresent(this->DrawRenderer[_handle]);
	WILL_REFRESH(MIN(x1, x2), MIN(y1, y2), abs(x2 - x1), abs(y2 - y1));
}

void Renderer::__plot_circle_points(SDL_Surface *Surface, int xc, int yc, int x, int y, Uint32 c)
{
	__put_pixel(Surface, xc + x, yc + y, c);
	__put_pixel(Surface, xc - x, yc + y, c);
	__put_pixel(Surface, xc + x, yc - y, c);
	__put_pixel(Surface, xc - x, yc - y, c);
	__put_pixel(Surface, xc + y, yc + x, c);
	__put_pixel(Surface, xc - y, yc + x, c);
	__put_pixel(Surface, xc + y, yc - x, c);
	__put_pixel(Surface, xc - y, yc - x, c);
}

void Renderer::__bresenham_circle(SDL_Surface *Surface, int xc, int yc, int radius, Uint32 c)
{
	int x = 0, y = radius, p = 3 - 2 * radius;
	while(x < y)
	{
		__plot_circle_points(Surface, xc, yc, x, y, c);
		if(p<0) {
			p = p + 4 * x + 6;
		} else {
			p = p + 4 * (x - y) + 10;
			y -= 1;
		}
		x += 1;
	}
	if(x == y)
		__plot_circle_points(Surface, xc, yc, x, y, c);
}

void Renderer::DrawCircle(int SurfaceHandle, int x, int y, int r)
{
	int _handle = SurfaceHandle + 1;
	if (_handle < 0 || _handle > 10)
		return ;
	Uint8 _a, _r, _g, _b;
	SDL2Function::GetRenderDrawColor(this->DrawRenderer[_handle], &_r, &_g, &_b, &_a);
	Uint32 c = _r << 16 | _g << 8 | _b << 0;
	__bresenham_circle(GetSurface(SurfaceHandle), x, y, r, c);

	WILL_REFRESH(x - r - 1, y - r - 1, 2 * r + 1, 2 * r + 1);
}
