//
// Created by liangyulin on 2021/9/5.
//

#ifndef BBASIC_STRINGIDENT_H
#define BBASIC_STRINGIDENT_H

#include "ivector.h"

class IStringIdent					// 字符串编号表
{
protected:
    struct StringIdent
    {
        char *string;
        int id;
    };
    IVector<StringIdent> Strings;
    int Count;
public:
    int Error;
    IStringIdent();
    ~IStringIdent();
    void Clear();
    void Add(char *string,int id);
    char *String(int index);
    char *Id2Str(int id);
    int  Id(int index);
    int  Id(char *string);
    int  Index(int id);
    int  Index(char *string);
    int  GetCount();
};

#endif //BBASIC_STRINGIDENT_H
