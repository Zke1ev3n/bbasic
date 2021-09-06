//
// Created by 梁玉林 on 2021/6/8.
//

#ifndef BBC_ASSEMBER_H
#define BBC_ASSEMBER_H
#include <vector>
#include <sstream>
#include "identfinder.h"
#include "stringident.h"
#include "ivector.h"

using namespace std;

typedef unsigned char vbyte;
typedef unsigned long vdword;

//汇编器
class Assembler {
protected:
    IIdentFinder IdentReader;	// 词法分析器
    IStringIdent LabelIdent;	// 申明地址记录器
    IStringIdent UseIdent;		// 使用地址记录器
    IVector<vbyte> Code;		// 代码生成记录器
    int  StackSize;				// 栈的大小
    char *KeyWords[20];

    enum SymbolType { SymReg=0,SymRegPoint=1,SymImm=2,SymImmPoint=3 };
    enum DataType   { DWord=0,Word=1,Byte=2,Float=3,Integer=4 };

    vdword SymType;
    vdword SymData;
    char   ErrorMsg[1024];
    int    SymError;
    int    SymPreType;
    char   SymIdent[1024];
    void   SetDWord(int ip,vdword value);
    int    GetSymbol(int IdentP);
    int    MakeOneSymbol(int ip,int IdentP);
    int    MakeTwoSymbol(int ip,int IdentP);

public:
    Assembler();
    int LoadAsm(stringstream &stream);
    int Output(string filename);
};

#endif //BBC_ASSEMBER_H
