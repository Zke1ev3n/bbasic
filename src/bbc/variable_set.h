#pragma once

#include <string>
#include <map>
#include "ivector.h"
#include "ilister.h"
#include "symbol.h"

using namespace std;

class VariableSet {
protected:

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
        IVector<int> array;
    };

    ILister<Variable> vars;
    //变量个数，是否在栈中
    int count, in_stack;
public:
    int stackp;
    VariableSet() : count(0), in_stack(0) {}
    int RegVar(const string& name, int type, int* array, int off = 0);
    int Pos(string name);
    string VarName(string name, int type);

    string GetName(int index) { return vars[index]->name; }
    int GetMode(int index) { return vars[index]->mode; }
    int GetType(int index) { return vars[index]->type; }
    int GetPos(int index)  { return vars[index]->spos; }
    int GetSize(int index) { return vars[index]->size; }
    int GetCount() { return count; }

};