//
// Created by liangyulin on 2021/9/5.
//

#include <string>
#include "stringident.h"

IStringIdent::IStringIdent()
{
    Count=0;
    Error=0;
    Strings.SetLength(0);
    Strings.AutoSize(1);
}
IStringIdent::~IStringIdent()
{
    Clear();
}
void IStringIdent::Clear()
{
    for (int i=0;i<Strings.GetLength();i++)
        if (Strings[i].string) delete Strings[i].string;
    Strings.SetLength(0);
    Count=0;
    Error=0;
}
void IStringIdent::Add(char *string,int id)
{
    if (Strings.SetLength(Count+1)) { Error++; return; }
    Strings[Count].string=new char[strlen(string)+1];
    if (!Strings[Count].string) { Error++; return; }
    strcpy(Strings[Count].string,string);
    Strings[Count].id=id;
    Count++;
}

char *IStringIdent::String(int index)
{
    if (index<0||index>=Count) { Error++; return NULL; }
    return Strings[index].string;
}

int IStringIdent::Id(int index)
{
    if (index<0||index>=Count) { Error++; return -1; }
    return Strings[index].id;
}
char *IStringIdent::Id2Str(int id)
{
    for (int i=0;i<Count;i++) if (id==Strings[i].id) return Strings[i].string;
    return NULL;
}
int IStringIdent::Index(int id)
{
    for (int i=0;i<Count;i++) if (id==Strings[i].id) return i;
    return -1;
}
int IStringIdent::GetCount()
{
    return Count;
}
int IStringIdent::Id(char *filename)
{
    for (int i=0;i<Count;i++) if (strcmp(filename,Strings[i].string)==0) return Strings[i].id;
    return -1;
}
int IStringIdent::Index(char *filename)
{
    for (int i=0;i<Count;i++) if (strcmp(filename,Strings[i].string)==0) return i;
    return -1;
}