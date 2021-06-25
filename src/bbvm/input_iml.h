#pragma once
#include "input.h"

class InputImpl : public Input
{
private:
    //键盘状态
    const Uint8* key_states;

    inline int __escape_charactor(int keymod, int key);
    void ShownKeyboard();
    void HiddenKeyboard();

public:
	InputImpl();
	~InputImpl();

	void HandleEvents();
    bool KeyPressed(int key);
    int WaitKey(bool OnlyKeyboard=false);

};
