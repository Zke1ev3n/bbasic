//
// Created by liangyulin on 2021/6/23.
//

#ifndef BBASIC_INPUT_H
#define BBASIC_INPUT_H

#include <string>

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

//输入设备的接口定义
class Input {

public:
    virtual void HandleEvents() = 0;
    virtual bool KeyPressed(int key) = 0;
    virtual int WaitKey(bool OnlyKeyboard=false) = 0;

};


#endif //BBASIC_INPUT_H
