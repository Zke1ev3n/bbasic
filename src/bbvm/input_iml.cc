#include "screen.h"
#include "input_iml.h"
#include <SDL2/SDL.h>

#define SDLK_RETURN '\r'
#define SDLK_ESCAPE '\033'
#define SDLK_BACKSPACE '\b'

InputImpl::InputImpl()
{
    key_states = SDL_GetKeyboardState(NULL);
}

InputImpl::~InputImpl()
{
}

void InputImpl::HandleEvents() {

    SDL_Event event1;
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT){
        SDL_Log("SDL_QUIT");
        exit(0);
    }
}

//这里不需要监听到何时按下和抬起
//https://stackoverflow.com/questions/56435371/using-sdl-pollevent-vs-sdl-pumpevents
bool InputImpl::KeyPressed(int key) {

    SDL_PumpEvents();

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

void InputImpl::ShownKeyboard()
{
    if (SDL_HasScreenKeyboardSupport() == SDL_TRUE)
        SDL_StartTextInput();
}

void InputImpl::HiddenKeyboard()
{
    if (SDL_HasScreenKeyboardSupport() == SDL_TRUE)
        SDL_StopTextInput();
}

inline bool _isalpha(int c)
{
    c = c % 0xFF;
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//TODO 优化
inline int InputImpl::__escape_charactor(int keymod, int key)
{
    if (key == SDLK_CAPSLOCK)
        return 0;
    if(key == SDLK_UP){
        return 38;
    }
    if(key == SDLK_DOWN){
        return 40;
    }
    if(key == SDLK_LEFT){
        return 37;
    }
    if(key == SDLK_RIGHT){
        return 39;
    }
    if ((keymod & KMOD_CAPS) != 0 && _isalpha(key))
        if ((keymod & KMOD_SHIFT) == 0)
            return key + 'A' - 'a';
        else
            return key;
    else
        return key;
}


//TODO 会阻塞主线程
int InputImpl::WaitKey(bool OnlyKeyboard)
{
    SDL_Event event;
    while(true) {
        //ShownKeyboard();
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