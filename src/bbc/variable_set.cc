//
// Created by liangyulin on 2021/9/3.
//

#include "variable_set.h"

string VariableSet::VarName(string name, int type){
    static string n;
    switch (type)
    {
        case 0x10:	n="VINT_"; break;
        case 0x11:	n="VFLO_"; break;
        case 0x12:	n="VSTR_"; break;
    }
    n.append(name);
    return n;
}

int VariableSet::RegVar(const string& name, int type, int* array, int off) {
    int i;
    for (i=0;i<count;i++)
        if (vars[i]->name==name) break;
    if (i<count) {
        if (vars[i]->type!=type) {
            //iserr<<"Variable type error\n";
            return -1;
        }
        if (array&&vars[i]->mode<=0) {
            //iserr<<"Variable types are not the same\n";
            return -2;
        }
        return i;
    }
    i=vars.Alloc();
    count++;
    vars[i]->name=name;
    vars[i]->type=type;
    vars[i]->mode=0;
    vars[i]->size=1;
    if (off) vars[i]->spos=off;
    else vars[i]->spos=stackp;
    if (array) {
        int j,size=1;
        vars[i]->array.AutoSize(1);
        for (j=0;array[j];j++) vars[i]->array[j]=array[j],size*=array[j];
        vars[i]->array[j]=0;
        vars[i]->mode=j;
        vars[i]->array.AutoSize(0);
        vars[i]->size=size;
        vars[i]->spos=vars[i]->spos-size*4+4;
    }
    stackp-=vars[i]->size*4;
    return i;
}
