//
// Created by liangyulin on 2021/9/6.
//

#ifndef BBASIC_SYMBOL_H
#define BBASIC_SYMBOL_H
#include <string>
#include "ivector.h"

using namespace std;

enum {	ES_OPERATOR=0,ES_IMMINT=1,ES_IMMFLOAT=2,ES_CSTRING=3,	// 栈的类型
    ES_VARINT=0x10,ES_VARFLOAT=0x11,ES_VARSTRING=0x12,		// 全局变量
    ES_PTRINT=0x20,ES_PTRFLOAT=0x21,ES_PTRSTRING=0x22 };	// 指针变量

//仅对语法分析
//TODO 优化？和代码生成的定义统一
struct VariableSymbol {
    string name;
    // 模式：0:单个变量  >0:变量数组
    int mode;
    // 类型：INT/REAL/STRING
    int type;
    // 数组的大小
    int size;
    IVector<int> array;
};

#endif //BBASIC_SYMBOL_H
