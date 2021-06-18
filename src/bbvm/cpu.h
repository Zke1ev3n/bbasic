#pragma once
#include "String.h"

#define Z	1
#define B	2
#define BE	3
#define A	4
#define AE	5
#define NZ	6

#define RP	0
#define RF	1
#define RS	2
#define RB	3
#define R0	4
#define R1	5
#define R2	6
#define R3	7

#define REG		0
#define REG_EX	1
#define IMM		2
#define IMM_EX	3

#define DWORD	0
#define WORD	1
#define BYTE	2
#define FLOAT	3
#define INT		4

#define ADD		0
#define SUB		1
#define MUL		2
#define DIV		3
#define MOD		4

//是否是模拟器 0为模拟器，其他用型号
#define ENV_SIM 9388

class Cpu
{
private:
	unsigned int rp, rf, rs, rb, r0, r1, r2, r3;
	unsigned int *(regs[8]);
	unsigned char *vmem;
	StringManager *StrMan;
	unsigned int DataPtr;

	void CoreDump();
	bool GetFlag(unsigned char Flag);
	void PutFlag(unsigned char Flag);
	void CoreCrash(const char *fmt, ...);

	unsigned int GetReg(unsigned int Reg);
	void PutReg(unsigned int Reg, unsigned int Data, unsigned int Size);

	unsigned int GetMem(unsigned int Addr);
	void PutMem(unsigned int Addr, unsigned int Data, unsigned int Size);

	unsigned int GetData(unsigned char Addressing, unsigned int Argument);
	void PutData(unsigned char Addressing, unsigned int Argument, unsigned int Data, unsigned int DataType);

	void Push(unsigned int Data);
	unsigned int Pop();

	unsigned int InPort(unsigned int Port);
	void OutPort(unsigned int Port, unsigned int Argu);

public:
	Cpu();
	~Cpu();

	unsigned int StateBase;
	int Init(void *Args);
    bool Run();
};
