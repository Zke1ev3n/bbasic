//
// Created by liangyulin on 2021/6/18.
//
#include <SDL2/SDL.h>

#include "bbvm.h"
#include "utils.h"

int BBVM::Init() {

    scn_ = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);
    Utils::Log("Virtual Memory...");
    vmem_ = (unsigned char *)malloc(MEMSIZE);
    if (vmem_ == NULL)
    {
        Utils::Error("Cannot create virtual memory.");
        return -1;
    }
    memset(vmem_, '\0', MEMSIZE);

    //TODO 这里暂时未找到更好的渲染器和显示器同步的方法，直接传实例了
    renderer_ = new Renderer(scn_);
    input_ = new input();
    storage_ = new Storage();

    status_ = true;

    return 0;
}

void BBVM::Run() {

    this->rp = this->rf = 0;
    this->r0 = this->r1 = 0;
    this->r2 = this->r3 = 0;
    this->rb = StateBase;
    this->rs = this->rb + 1000;

    while (status_ == true)
    {
        //接收事件
        input_->PollEvents();
        if (Exec() == false) status_ = false;
    }
    scn_->NewLine();
}

void BBVM::Exit() {
    scn_->Display("bbvm exit");

    delete this->StrMan;

    delete input_;
    delete renderer_;
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
    fseek(fp, 0, SEEK_SET);

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

    StateBase = size;

    //加载文件
    fread(vmem_, size, 1, fp);
    fclose(fp);

    return size;
}

static union _conv
{
    unsigned int i;
    float f;
} conv;

const unsigned int CmdLengthMap[] = {1, 10, 5, 5, 10, 10, 5, 6, 5, 1, 10, 10, 0, 0, 0, 1};
const char *OpCode[] = {"noop", "ld", "push", "pop", "in", "out", "jmp", "jpc", "call", "ret", "cmp", "cal", "", "", "", "exit"};
const unsigned int TypeSize[] = {4, 2, 1, 4, 4};

BBVM::BBVM()
{
    this->regs[0] = &this->rp;
    this->regs[1] = &this->rf;
    this->regs[2] = &this->rs;
    this->regs[3] = &this->rb;
    this->regs[4] = &this->r0;
    this->regs[5] = &this->r1;
    this->regs[6] = &this->r2;
    this->regs[7] = &this->r3;
    this->StrMan = new StringManager();
    this->StateBase = 0;
}

bool BBVM::GetFlag(unsigned char Flag)
{
    switch(Flag)
    {
        case NZ:
            return (this->rf & Z) == 0;
        case Z:
            return (this->rf & Z) != 0;
        case BE:
            return ((this->rf & B) | (this->rf & Z)) != 0;
        case B:
            return (this->rf & B) != 0;
        case AE:
            return ((this->rf & A) | (this->rf & Z)) != 0;
        case A:
            return (this->rf & A) != 0;
        default:
            CoreCrash("Unpredictable flag: %d", Flag);
            return false;
    }
}

void BBVM::PutFlag(unsigned char Flag)
{
    if (Flag == Z || Flag == A || Flag == B)
    {
        this->rf = Flag;
    } else {
        CoreCrash("Unpredictable flag: %d", Flag);
    }
}

void BBVM::CoreDump()
{
    FILE *fp = fopen("anvm.dump", "w+");
    fprintf(fp, "[Register]\n"
                "rp=0x%08X rf=0x%08X rs=0x%08X rb=0x%08X\n"
                "r0=0x%08X r1=0x%08X r2=0x%08X r3=0x%08X\n\n",
            this->rp, this->rf, this->rs, this->rb,
            this->r0, this->r1, this->r2, this->r3);
    fprintf(fp, "[Flags]\n"
                "Z=%d A=%d B=%d\n",
            GetFlag(Z), GetFlag(A), GetFlag(B));
    fprintf(fp, "\n\n[Memory]\n--Address----0--1--2--3--4--5--6--7--8--9--A--B--C--D--E--F");
    for (int i = 0; i < MEMSIZE; i++)
    {
        if ((i & 0xF) == 0)
        {
            fprintf(fp, "\n0x%08X: ", i);
        }
        fprintf(fp, "%02X ", vmem_[i]);
    }
    fprintf(fp, "\n\n=== end dump ===\n");
    fclose(fp);
}

void BBVM::CoreCrash(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    Utils::vError(fmt, ap);
    va_end(ap);
    CoreDump();
    exit(0);
}

unsigned int BBVM::GetReg(unsigned int Reg)
{
    if (Reg <= 7)
    {
        return *this->regs[Reg];
    }
    else
    {
        CoreCrash("Unknow register id: %d", Reg);
        return 0;
    }
}

void BBVM::PutReg(unsigned int Reg, unsigned int Data, unsigned int Size)
{
    if (Reg <= 7)
    {
        // It's magic, do not change!
        unsigned long Mask = ~((0xFFFFFFFF << Size * 4) << Size * 4);
        (*this->regs[Reg]) = ((*this->regs[Reg]) & ~Mask) | (Data & Mask);
    }
    else
    {
        CoreCrash("Unknow register id: %d", Reg);
    }
}

unsigned int BBVM::GetMem(unsigned int Addr)
{
    if (Addr <= MEMSIZE - 4)
    {
        return *(int*)(vmem_ + Addr);
    }
    else
    {
        CoreCrash("Cannot read in: 0x%8X", Addr);
        return 0;
    }
}

void BBVM::PutMem(unsigned int Addr, unsigned int Data, unsigned int Size)
{
    if (Addr <= MEMSIZE - 4)
    {
        // It's magic, do not change!
        unsigned long Mask = ~((0xFFFFFFFF << Size * 4) << Size * 4);
        (*(int*)(vmem_ + Addr)) = ((*(int*)(vmem_ + Addr)) & ~Mask) | (Data & Mask);
    }
    else
    {
        CoreCrash("Cannot write in: 0x%8X", Addr);
    }
}

unsigned int BBVM::GetData(unsigned char Addressing, unsigned int Argument)
{
    switch(Addressing)
    {
        case 0:
            return GetReg(Argument);
        case 1:
            return GetMem(GetReg(Argument));
        case 2:
            return Argument;
        case 3:
            return GetMem(Argument);
        default:
            CoreCrash("Unknow addressing: %d", Addressing);
            return 0;
    }
}

void BBVM::PutData(unsigned char Addressing, unsigned int Argument, unsigned int Data, unsigned int DataType)
{
    unsigned int Size = TypeSize[DataType];
    switch(Addressing)
    {
        case 0:
            PutReg(Argument, Data, Size);
            break;
        case 1:
            PutMem(GetReg(Argument), Data, Size);
            break;
        case 2:
            break;
        case 3:
            PutMem(Argument, Data, Size);
            break;
        default:
            CoreCrash("Unknow addressing: %d", Addressing);
    }
}

void BBVM::Push(unsigned int Data)
{
    PutData(REG_EX, RS, Data, DWORD);
    this->rs -= 4;
}

unsigned int BBVM::Pop()
{
    this->rs += 4;
    return GetData(REG_EX, RS);
}

bool BBVM::Exec()
{
    unsigned char Cmd = ((*(vmem_ + this->rp)) & 0xF0) >> 4;
    unsigned char Addr = 0, AddrSec = 0, Flag = 0, DataType = 0, CalType = 0;
    unsigned int Argu = 0, ArguSec = 0, CmdLen = CmdLengthMap[Cmd];
    switch(CmdLen)
    {
        case 1:
            break;
        case 5:		// X[Addressing] [Argument]
            Addr = (*(vmem_ + this->rp)) & 0x0F;
            Argu = *(int*)(vmem_ + this->rp + 1);
            break;
        case 6:		// X[Flag] [Addressing] [Argument]
            Flag = (*(vmem_ + this->rp)) & 0x0F;
            Addr = *(vmem_ + this->rp + 1);
            Argu = *(int*)(vmem_ + this->rp + 2);
            break;
        case 10:	// X[DataType|0] [0|CalType][Multi-Addressing] [Argument1] [Argument2]
            DataType = (*(vmem_ + this->rp)) & 0x0F;
            if (DataType > 4)
            {
                CoreCrash("Unknow data type:%d", DataType);
                return false;
            }
            CalType = ((*(vmem_ + this->rp + 1)) & 0xF0) >> 4;
            Addr = (*(vmem_ + this->rp + 1)) & 0x0F;
            AddrSec = Addr & 0x03;
            Addr >>= 2;
            Argu = *(int*)(vmem_ + this->rp + 2);
            ArguSec = *(int*)(vmem_ + this->rp + 6);
            break;
    }
    //Log("%s\n", CmdName[Cmd]);
    switch(Cmd)
    {
        case 0x0:		// NOOP
            this->rp += CmdLen;
            break;
        case 0x1:		// LD
            PutData(Addr, Argu, GetData(AddrSec, ArguSec), DataType);
            this->rp += CmdLen;
            break;
        case 0x2:		// PUSH
            Push(GetData(Addr, Argu));
            this->rp += CmdLen;
            break;
        case 0x3:		// POP
            PutData(Addr, Argu, Pop(), DataType);
            this->rp += CmdLen;
            break;
        case 0x4:		// IN
            PutData(Addr, Argu, InPort(GetData(AddrSec, ArguSec)), DataType);
            this->rp += CmdLen;
            break;
        case 0x5:		// OUT
            OutPort(GetData(Addr, Argu), GetData(AddrSec, ArguSec));
            this->rp += CmdLen;
            break;
        case 0x6:		// JMP
            this->rp = GetData(Addr, Argu);
            break;
        case 0x7:		// JPC
            if (GetFlag(Flag) == true)
            {
                this->rp = GetData(Addr, Argu);
            } else {
                this->rp += CmdLen;
            }
            break;
        case 0x8:		// CALL
            Push(this->rp + CmdLen);
            this->rp = GetData(Addr, Argu);
            break;
        case 0x9:		// RET
            this->rp = Pop();
            break;
        case 0xA:		// CMP
        {
            int op1 = (int)GetData(Addr, Argu), op2 = (int)GetData(AddrSec, ArguSec);
            switch(DataType)
            {
                case BYTE:
                    op1 &= 0xFF; op2 &= 0xFF;
                case WORD:
                    op1 &= 0xFFFF; op2 &= 0xFFFF;
                case DWORD: case INT:
                    if (op1 == op2) {PutFlag(Z);}
                    else if (op1 < op2) {PutFlag(B);}
                    else if (op1 > op2) {PutFlag(A);}
                    break;
                case FLOAT:
                {
                    float opf1, opf2;
                    conv.i = op1; opf1 = conv.f;
                    conv.i = op2; opf2 = conv.f;
                    if (opf1 == opf2) {PutFlag(Z);}
                    else if (opf1 < opf2) {PutFlag(B);}
                    else if (opf1 > opf2) {PutFlag(A);}
                }
                    break;
            }
        }
            this->rp += CmdLen;
            break;
        case 0xB:		// CAL
        {
            int op1 = (int)GetData(Addr, Argu), op2 = (int)GetData(AddrSec, ArguSec), result = 0;
            switch(DataType)
            {
                case BYTE:
                    op1 &= 0xFF; op2 &= 0xFF;
                case WORD:
                    op1 &= 0xFFFF; op2 &= 0xFFFF;
                case DWORD: case INT:
                    switch(CalType)
                    {
                        case ADD: result = op1 + op2; break;
                        case SUB: result = op1 - op2; break;
                        case MUL: result = op1 * op2; break;
                        case DIV: result = op1 / op2; break;
                        case MOD: result = op1 % op2; break;
                        default:
                            CoreCrash("Unknow operator: %d", CalType);
                    }
                    break;
                case FLOAT:
                {
                    float opf1, opf2, resultf = 0.0f;
                    conv.i = op1; opf1 = conv.f;
                    conv.i = op2; opf2 = conv.f;
                    switch(CalType)
                    {
                        case ADD: resultf = opf1 + opf2; break;
                        case SUB: resultf = opf1 - opf2; break;
                        case MUL: resultf = opf1 * opf2; break;
                        case DIV: resultf = opf1 / opf2; break;
                        default:
                            CoreCrash("Unknow operator: %d", CalType);
                    }
                    conv.f = resultf;
                    result = conv.i;
                }
                    break;
            }
            PutData(Addr, Argu, result, DataType);
        }
            this->rp += CmdLen;
            break;
        case 0xF:		// EXIT
            return false;
        default:
            CoreCrash("Unpredictable command on [0x%08X] :", rp);
            CoreDump();
            return false;
    }
    return true;
}

unsigned char* BBVM::GetIOString(int handle){
    if (StrMan->EffectiveHandle((int)handle) == true)
    {
        return StrMan->GetString(handle);
    } else {
        return (unsigned char *)vmem_ + handle;
    }
}