#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum{
    ES_VARINT=0x10,
    ES_VARFLOAT=0x11,
    ES_VARSTRING=0x12,
};

struct Variable
{
    string name;
    // 模式：0:单个变量  >0:变量数组
    int mode;
    // 类型：INT/REAL/STRING
    int type;
    // 数组的大小
    int size;
    // 在栈中相对sp的偏移
    int spos;
    vector<int> array;
};

class VariableSet {
protected:

    //TODO 是否符合需求
    vector<Variable*> vars;
    //变量个数，是否在栈中
    int count, in_stack;
public:
    int stackp;
    VariableSet() : count(0), in_stack(0) {}
    int RegVar(const string& name, int type, int* array, int off = 0);
    int Pos(string name);
    string VarName(string name, int type);
};