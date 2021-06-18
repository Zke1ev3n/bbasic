//
// Created by liangyulin on 2021/6/18.
//

#ifndef BBASIC_BBVM_H
#define BBASIC_BBVM_H

#include "Cpu.h"
#include "Gpu.h"
#include "Screen.h"
#include "Input.h"
#include "Storage.h"

//默认的小机分辨率
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 320;


//默认的小机最大内存
#define MEMSIZE (2*1024*1024)

//默认帧数
#define FPSNEED 24

class BBVM{
private:
    bool power_ = false;
    int bin_version_;
    Cpu *cpu_;
    Screen *scn_;
    unsigned char *vmem_;
    Input *input_;
    Gpu *gpu_;
    Storage *storage_;


public:
    int Start();
    void Run();
    int Exit();
    int LoadBinFile(const char* filepath);
    ~BBVM();

};


#endif //BBASIC_BBVM_H
