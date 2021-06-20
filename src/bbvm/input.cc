#include "screen.h"
#include "input.h"
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

#define SDLK_RETURN '\r'
#define SDLK_ESCAPE '\033'
#define SDLK_BACKSPACE '\b'

input::input()
{
    key_states = SDL_GetKeyboardState(NULL);
}

input::~input()
{
}

void input::PollEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

}

//这里不需要监听到何时按下和抬起
//https://stackoverflow.com/questions/56435371/using-sdl-pollevent-vs-sdl-pumpevents
bool input::KeyPressed(int key) {

    switch (key) {
        case 38:
            key = SDL_SCANCODE_UP;
            break;
        case 40:
            key = SDL_SCANCODE_DOWN;
            break;
        case 37:
            key = SDL_SCANCODE_LEFT;
            break;
        case 39:
            key = SDL_SCANCODE_RIGHT;
            break;
        default:
            key = SDL_GetScancodeFromKey(key);
            break;
    }

    return key_states[key];
}

void input::ShownKeyboard()
{
    if (SDL_HasScreenKeyboardSupport() == SDL_TRUE)
        SDL_StartTextInput();
}

void input::HiddenKeyboard()
{
    if (SDL_HasScreenKeyboardSupport() == SDL_TRUE)
        SDL_StopTextInput();
}

//TODO 优化
int input::WaitKey(bool OnlyKeyboard)
{
    SDL_Event event;
    while(true) {
        SDL2Input::ShownKeyboard();
        if (SDL_WaitEvent(&event) != 0) {
            //if (event.type == SDL_KEYDOWN && SDL_IsTextInputActive() == SDL_FALSE) {
            if (event.type == SDL_KEYDOWN) {
                int kc = __escape_charactor(event.key.keysym.mod, event.key.keysym.sym);
                if (kc != 0)
                    return kc;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && OnlyKeyboard == false) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                return ((y * 65536) + x) | 0x80000000;
            } else if (event.type == SDL_QUIT) {
                exit(0);
            }
//			else if (event.type == SDL_TEXTINPUT) {
//				int kc = __escape_charactor(event.key.keysym.mod, event.text.text[0]);
//				if (kc != 0)
//					return kc;
//			}
        }
    }
}