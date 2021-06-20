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

class Line
{
public:
	Point PrintPosition;
	string LineText;
};

class input
{
private:
    //键盘状态
    const Uint8* key_states;

	unsigned char *GetKeyString();
	vector<Line*> *InputBuffer;
	int InputNewline(Point Ptr, int ScnWidth, int CharWidth);

public:
	input();
	~input();

	void PollEvents();

	unsigned int GetInteger();
	unsigned char *GetString();
	float GetFloat();

    bool KeyPressed(int key);
    unsigned char GetKeycode();

};
