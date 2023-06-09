//
// Created by liangyulin on 2021/9/6.
//

#ifndef BBASIC_ILISTER_H
#define BBASIC_ILISTER_H

template <class ClassType>
class ILister
{
protected:
    struct TypeRow
    {
        ClassType **data;
        int ColCount;
    };
    TypeRow *TypeRows;
    ClassType Nil;
    int RowCount;
    int AddRow();
public:
    int Error;
    ILister();
    virtual ~ILister();
    int Alloc();
    int Release(int handle);
    void Clear();
    ClassType* operator[](int handle);
};

template <class ClassType> ILister<ClassType>::ILister()
{
    RowCount=0;
    TypeRows=0;
    Error=0;
}

template <class ClassType> int ILister<ClassType>::AddRow()
{
    int NewIndex=0;
    if (!TypeRows) {
        TypeRows=new TypeRow;
        if (TypeRows==0) return -1;
        NewIndex=0;
    }  else {
        TypeRow *NewRows=new TypeRow[RowCount+1];
        if (!NewRows) return -1;
        for (int i=0;i<RowCount;i++) NewRows[i] = TypeRows[i];
        delete []TypeRows;
        TypeRows=NewRows;
        NewIndex=RowCount;
    }
    TypeRows[NewIndex].ColCount=0;
    TypeRows[NewIndex].data=new ClassType*[64];
    if (!TypeRows[NewIndex].data) return -2;
    for (int i=0;i<64;i++) TypeRows[NewIndex].data[i]=0;
    RowCount++;
    return 0;
}

template <class ClassType> int ILister<ClassType>::Alloc()
{
    int line,i;
    for (line=0;line<RowCount;line++) if (TypeRows[line].ColCount<64) break;
    if (line==RowCount) if (AddRow()) { Error++; return 0; }
    for (i=0;i<64;i++) if (TypeRows[line].data[i]==0) break;
    if (i==64) { Error++; return 0; }
    TypeRows[line].data[i]=new ClassType;
    if (!TypeRows[line].data[i]) { Error++; return 0; }
    TypeRows[line].ColCount++;
    return line*64+i;
}

template <class ClassType> int ILister<ClassType>::Release(int handle)
{
    int line=handle>>6;
    int index=handle&63;
    if (line<0||line>=RowCount) return -1;
    if (TypeRows[line].data[index]==0) return -2;
    delete TypeRows[line].data[index];
    TypeRows[line].data[index]=0;
    TypeRows[line].ColCount--;
    return 0;
}

template <class ClassType> ClassType* ILister<ClassType>::operator[](int handle)
{
    int line=handle>>6;
    int index=handle&63;
    if (line<0||line>=RowCount) { Error++; return &Nil; }
    if (index<0||TypeRows[line].data[index]==0) { Error++; return &Nil; }
    return TypeRows[line].data[index];
}

template <class ClassType> ILister<ClassType>::~ILister()
{
    for (int line=0;line<RowCount;line++) {
        for (int i=0;i<64;i++)
            if (TypeRows[line].data[i]) delete TypeRows[line].data[i];
        delete []TypeRows[line].data;
    }
    if (TypeRows) delete []TypeRows;
    TypeRows=0;
    RowCount=0;
}

template <class ClassType> void ILister<ClassType>::Clear()
{
    for (int line=0;line<RowCount;line++) {
        for (int i=0;i<64;i++)
            if (TypeRows[line].data[i]) {
                delete TypeRows[line].data[i];
                TypeRows[line].data[i]=0;
            }
        TypeRows[line].ColCount=0;
    }
    Error=0;
}

#endif //BBASIC_ILISTER_H
