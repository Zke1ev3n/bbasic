//
// Created by liangyulin on 2021/9/3.
//

#include "symbol.h"

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
    Variable* var = new Variable();
    var->name=name;
    var->type=type;
    var->mode=0;
    var->size=1;
    if (off) var->spos=off;
    else var->spos=stackp;
    if (array) {
        int j,size=1;
        //var->array.AutoSize(1);
        //TODO ???
        var->array.resize(sizeof(array));
        //自动扩容
        for (j=0;array[j];j++) var->array[j]=array[j],size*=array[j];
        var->array[j]=0;
        var->mode=j;
        //var->array.AutoSize(0);
        var->size=size;
        var->spos=var->spos-size*4+4;
    }
    stackp-=var->size*4;
    vars.push_back(var);
    count++;

    return i;

}
