#include "anvm.h"
#include "screen.h"
#include "Input.h"
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

#define SDLK_RETURN '\r'
#define SDLK_ESCAPE '\033'
#define SDLK_BACKSPACE '\b'

#define Keypress() (SDL2Input::KeyPress())
#define WaitKey(OnlyKeyboard) (SDL2Input::WaitKey((OnlyKeyboard)))

Input::Input()
{
    key_states = SDL_GetKeyboardState(NULL);
}

Input::~Input()
{
}

void Input::PollEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

}

int Input::InputNewline(Point CurInput, int ScnWidth, int CharWidth)
{
	int FreeChar = ((ScnWidth - CurInput.x + 1) - CharWidth) / CharWidth + 1;
	this->InputBuffer->push_back(new Line);
	this->InputBuffer->back()->PrintPosition = CurInput;
	this->InputBuffer->back()->LineText = "";
	return FreeChar;
}

unsigned char *Input::GetKeyString()
{
	this->InputBuffer = new vector<Line*>();
	bool Quit = false;
	int ScnWidth, ScnHeigth;
	int CharWidth = scn->GetFontWidth();
	scn->GetScreenSize(&ScnWidth, &ScnHeigth);
	int FreeChar = InputNewline(scn->GetDispPosition(), ScnWidth, CharWidth);
	while (Quit == false) {
		unsigned char Key = WaitKey(true);
		if (Key == SDLK_RETURN) {
			Quit = true;
		} else if (Key == SDLK_ESCAPE) {
			scn->NewLine();
			scn->Display("reinput:");
			for (unsigned int i = 0; i < this->InputBuffer->size(); i++) {
				delete this->InputBuffer->at(i);
			}
			this->InputBuffer->clear();
			FreeChar = InputNewline(scn->GetDispPosition(), ScnWidth, CharWidth);
		} else if (Key == SDLK_BACKSPACE) {
			Line *LinePtr = this->InputBuffer->back();
			if (LinePtr->LineText.length() == 0)
			{
				if (this->InputBuffer->size() >= 2)
				{
					delete LinePtr;
					this->InputBuffer->pop_back();
					LinePtr = this->InputBuffer->back();
					FreeChar = 0;
				}
			}
			int len = LinePtr->LineText.length(), dx = 0, dy = 0;
			if (len > 0) {
				LinePtr->LineText.erase(--len, 1);
			}
			if (scn->GetDispPosition().y <= 0 && LinePtr->PrintPosition.y > 0) {
				Point ptmp;
				ptmp.x = ptmp.y = 0;
				FreeChar = InputNewline(ptmp, ScnWidth, CharWidth);
				LinePtr = this->InputBuffer->back();
				dx = dy = 0;
			} else {
				dx = LinePtr->PrintPosition.x + len * CharWidth;
				dy = LinePtr->PrintPosition.y;
				FreeChar++;
			}
			scn->Display(" ", dx, dy);
			scn->SetDispPosition(dx, dy);
		} else if (isprint(Key) == 0) {
			continue ;
		} else {
			if (FreeChar == 0)
			{
				scn->NewLine();
				FreeChar = InputNewline(scn->GetDispPosition(),
											ScnWidth,
											CharWidth);
			}
			this->InputBuffer->back()->LineText.append(1, Key);
			FreeChar--;
			scn->Display((char)Key);
		}
	}
	string buf;
	for (vector<Line*>::iterator it = this->InputBuffer->begin(); it != this->InputBuffer->end(); it++) {
		buf.append((*it)->LineText);
		delete *it;
	}
	delete this->InputBuffer;
	scn->NewLine();
	return (unsigned char *)strdup(buf.c_str());
}

unsigned char *Input::GetString()
{
	return GetKeyString();
}

unsigned int Input::GetInteger()
{
	return atoi((char *)GetKeyString());
}

float Input::GetFloat()
{
	return atof((char *)GetKeyString());
}


bool Input::KeyPressed(int key) {
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
