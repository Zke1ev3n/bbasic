//
// Created by liangyulin on 2021/9/5.
//

#include <string>
#include "identfinder.h"

IIdentFinder::IIdentFinder()
{
    root=NULL;
    Count=0;
}

IIdentFinder::~IIdentFinder()
{
    list.SetLength(0);
    Clear();
}

int IIdentFinder::Clear()
{
    for (IIdentLink *p;root;root=p)
    {
        if (root->sValue) delete root->sValue;
        p=root->Next;
        delete root;
    }
    Count=0;
    return 0;
}

int IIdentFinder::FindIdent(const char *str,char **key_words,int HighCase)
{
    IIdentLink *root=NULL;
    IIdentLink *prev=root,*n;
    char buffer[256];
    char **key=key_words;
    char *d[2]={ 0,0 };
    int len=strlen(str);
    int i,p,m,c,point,j;

    if (!str) return -1;
    if (!key) key=d;
    Clear();
    for (i=0,p=0,m=0,c=0;i<len;)
    {
        switch (m)
        {
            case 0:
                if (isspace(str[i])) i++;
                else if (isalpha(str[i])||str[i]=='_') m=1, c++;
                else if (isalnum(str[i])) m=2, c++, point=0;
                else if (str[i]=='$'&&((str[i+1]>='0'&&str[i+1]<='9')||(str[i+1]>='A'&&str[i+1]<='F')||(str[i+1]>='a'&&str[i+1]<='f'))) m=3, i++, c++;
                else if (str[i]=='\"') m=4, c++;
                else if (str[i]==';'||str[i]=='\'') m=5;
                else m=6, c++;
                break;
            case 1:
                buffer[p]=str[i];
                p++; i++;
                if (isalnum(str[i])||isalpha(str[i])||str[i]=='_');
                else {
                    if (HighCase) {
                        for (int k=0;k<p;k++) if (buffer[k]>='a'&&buffer[k]<='z') buffer[k]-='a'-'A';
                    }
                    buffer[p]=0, p=m=0;
                    n=new IIdentLink;
                    if (n)
                    {
                        n->Type=Ident;
                        n->Next=NULL;
                        for (j=0;key[j];j++) if (strcmp(buffer,key[j])==0) break;
                        if (key[j]) n->Type=KeyWord, n->Value=j;
                        n->sValue=new char[strlen(buffer)+1];
                        if (n->sValue) strcpy(n->sValue,buffer);
                        else { delete n; n=NULL; }
                        if (n) { if (prev) prev->Next=n; else root=n; prev=n; }
                    }
                }
                break;
            case 2:
                buffer[p]=str[i];
                p++; i++;
                if (isalnum(str[i]));
                else if (str[i]=='.'&&point==0) point=1;
                else {
                    buffer[p]=0, p=m=0;
                    n=new IIdentLink;
                    if (n) {
                        if (!point) n->Type=Integer, n->iValue=atol(buffer);
                        else n->Type=Float, n->fValue=(float)atof(buffer);
                        n->Next=NULL;
                        n->sValue=new char[strlen(buffer)+1];
                        if (n->sValue) strcpy(n->sValue,buffer);
                        if (prev) prev->Next=n; else root=n;
                        prev=n;
                    }
                }
                break;
            case 3:
                buffer[p]=str[i];
                p++; i++;
                if ((str[i]>='0'&&str[i]<='9')||(str[i]>='A'&&str[i]<='F')||(str[i]>='a'&&str[i]<='f'));
                else {
                    buffer[p]=0; p=m=0;
                    n=new IIdentLink;
                    if (n) {
                        n->Type=Integer;
                        n->Next=NULL;
                        sscanf(buffer,"%lx",&n->iValue);
                        n->sValue=new char[strlen(buffer)+3];
                        if (n->sValue) {
                            n->sValue[0]='$';
                            strcpy(n->sValue+1,buffer);
                        }
                        if (prev) prev->Next=n; else root=n;
                        prev=n;
                    }
                }
                break;
            case 4:
                buffer[p]=str[i];
                p++; i++;
                if (str[i]=='\"') {
                    buffer[p]='\"', buffer[p+1]=0, i++, p=m=0;
                    n=new IIdentLink;
                    if (n) {
                        n->Type=String;
                        n->Next=NULL;
                        n->sValue=new char[strlen(buffer)+3];
                        if (n->sValue) { strcpy(n->sValue,buffer); if (prev) prev->Next=n; else root=n; prev=n; }
                        else free(n);
                    }
                }
                break;
            case 5:
                i++; if (str[i]=='\n')  m=0;
                break;
            case 6:
                buffer[p]=str[i];
                buffer[p+1]=0;
                i++; p=m=0;
                n=new IIdentLink;
                if (n) {
                    n->Type=Operator;
                    n->Next=NULL;
                    n->Value=buffer[0];
                    n->sValue=new char[strlen(buffer)+3];
                    if (n->sValue) n->sValue[0]=buffer[0],n->sValue[1]=0;
                    if (prev) prev->Next=n; else root=n;
                    prev=n;
                }
                break;
        }
    }
    this->root=root;
    for (Count=0,n=root;n;n=n->Next) Count++;
    list.SetLength(Count);
    for (n=root,i=0;i<Count&&n;n=n->Next,i++) list[i]=*n;
    return Count;
}

int IIdentFinder::GetCount()
{
    return Count;
}

IIdentFinder::IIdentLink* IIdentFinder::operator[](int i)
{
    static IIdentLink Default={String,0,0,0,"",&Default};
    if (Count<1) Default.Next=&Default;
    if (i>=Count||i<0) return &Default;
    return &list[i];
}
