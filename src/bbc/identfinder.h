//
// Created by liangyulin on 2021/9/5.
//

#ifndef BBASIC_IDENTFINDER_H
#define BBASIC_IDENTFINDER_H

#include "ivector.h"

class IIdentFinder	// 小型C式链表词法分析器
{
public:
    struct IIdentLink	// 分析结果
    {
        char   Type;
        int    Value;
        long   iValue;
        float  fValue;
        char  *sValue;
        struct IIdentLink *Next;
    };
protected:
    IIdentLink *root;
    IVector<IIdentLink> list;
    int Count;
    int Clear();
public:
    enum IdentMode { KeyWord=0,Ident=1,Integer=2,Float=3,String=4,Operator=5 };
    IIdentFinder();
    ~IIdentFinder();
    virtual int FindIdent(const char *s,char **key_words,int HighCase=0);
    IIdentFinder::IIdentLink* operator[](int i);
    int GetCount();
};

#endif //BBASIC_IDENTFINDER_H
