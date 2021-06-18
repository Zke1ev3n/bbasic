#pragma once
#include <string>
#include <vector>

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
    const uint8_t *key_states;

	unsigned char *GetKeyString();
	vector<Line*> *InputBuffer;
	int InputNewline(Point Ptr, int ScnWidth, int CharWidth);

public:
	Input();
	~Input();

	void PollEvents();


	unsigned int GetInteger();
	unsigned char *GetString();
	float GetFloat();
};
