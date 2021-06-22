#pragma once
#include <string>
#include <vector>

#define KEYCODE_UP 38
#define KEYCODE_DOWN 40
#define KEYCODE_LEFT 37
#define KEYCODE_RIGHT 39
#define KEYCODE_SPACE 32
#define KEYCODE_ESCAPE 27
#define KEYCODE_ENTER 13
#define KEYCODE_BACKTRACE 8

using namespace std;

class Line
{
public:
	Point PrintPosition;
	string LineText;
};

class Input
{
private:
    //键盘状态
    const Uint8* key_states;
    SDL_Event event;

    inline int __escape_charactor(int keymod, int key);
    void ShownKeyboard();
    void HiddenKeyboard();

public:
	Input();
	~Input();

	void HandleEvents();
    bool KeyPressed(int key);
    int WaitKey(bool OnlyKeyboard=false);

};
