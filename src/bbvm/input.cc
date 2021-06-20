#include "screen.h"
#include "input.h"
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

#define SDLK_RETURN '\r'
#define SDLK_ESCAPE '\033'
#define SDLK_BACKSPACE '\b'

#define Keypress() (SDL2Input::KeyPress())
#define WaitKey(OnlyKeyboard) (SDL2Input::WaitKey((OnlyKeyboard)))

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

int input::InputNewline(Point CurInput, int ScnWidth, int CharWidth)
{
	int FreeChar = ((ScnWidth - CurInput.x + 1) - CharWidth) / CharWidth + 1;
	this->InputBuffer->push_back(new Line);
	this->InputBuffer->back()->PrintPosition = CurInput;
	this->InputBuffer->back()->LineText = "";
	return FreeChar;
}

unsigned char *input::GetString()
{
	return GetKeyString();
}

unsigned int input::GetInteger()
{
	return atoi((char *)GetKeyString());
}

float input::GetFloat()
{
	return atof((char *)GetKeyString());
}

bool input::KeyPressed(int key) {
    //TODO 优化？
    if(SDL_QuitRequested()){
        exit(0);
    }

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
