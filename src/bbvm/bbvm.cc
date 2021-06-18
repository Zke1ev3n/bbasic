//
// Created by liangyulin on 2021/6/18.
//
#include <SDL2/SDL.h>

#include "bbvm.h"
#include "utils.h"


int BBVM::Start() {
    scn_ = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    Utils::Log("Screen Device...OK!\n");
    Utils::Log("Memory...");
    vmem_ = (unsigned char *)malloc(MEMSIZE);
    if (vmem_ == NULL)
    {
        Utils::Error("Cannot create virtual memory.");
        return -1;
    }
    memset(vmem_, '\0', MEMSIZE);
    Utils::Log("OK!\nLoad Bootstrap...");
//    int binlen = LoadFile(_binFile, vmem);
//    if (binlen == -1)
//    {
//        Error("Cannot load [%s] to memory.", _binFile);
//        return -1;
//    }
    Utils::Log("OK!\nCPU...");
    cpu_ = new Cpu();
    Utils::Log("OK!\nGPU...");
    gpu_ = new Gpu();
    Utils::Log("OK!\nKeyboard...");
    input_ = new Input();
    Utils::Log("OK!\nStorage...");
    storage_ = new Storage();
    Utils::Log("OK!\nBooting...\n");
//    cpu_->StateBase = binlen;
//
//    cpu_->Run(vmem);

    power_ = true;

    return 0;
}

void BBVM::Run() {

    //cpu_->StateBase = binlen;
    //TODO 内存和CPU分离，参考其他模拟器设计
    cpu_->Init(vmem_);
    Uint32 frame_start, frame_end;
    Uint32 must_delay;

    while (power_ == true)
    {
        frame_start = SDL_GetTicks();
        //接收事件
        input_->PollEvents();
        if (cpu_->Run() == false) break;
        //gpu_->Render();
        //screen->Draw();

        frame_end = SDL_GetTicks();
        must_delay = (1000 / FPSNEED) - (frame_end - frame_start);
        if (must_delay > 10)
            SDL_Delay(must_delay);

    }
    scn_->NewLine();
}

int BBVM::Exit() {
    scn_->Display("bbvm exit");

    delete input_;
    delete cpu_;
    delete gpu_;
    delete storage_;
    delete scn_;
}

BBVM::~BBVM() {
    BBVM::Exit();
}

int BBVM::LoadBinFile(const char *filepath) {
    char header[16];
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        Utils::Log("Cannot open %s", filepath);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    fread(header, 16, 1, fp);
    //校验
    if (header[0]=='B' && header[1]=='B' && header[2]=='E'){
        if(header[7]!=0x40) bin_version_ = 20;
        size -= 16;
        fseek(fp, 16, SEEK_SET);
    }else {
        bin_version_ = 19;
        fseek(fp, 0, SEEK_SET);
    }

    if (ferror(fp) != 0)
    {
        return -1;
    }

    //加载文件
    fread(vmem_, size, 1, fp);
    fclose(fp);

    return size;
}