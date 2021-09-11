//
// Created by 梁玉林 on 2021/6/9.
//

#ifndef BBC_CODEGEN_H
#define BBC_CODEGEN_H

#include <sstream>
#include "ast.h"
#include "variable_set.h"
#include "stringident.h"

class CodeGen:public ASTVisitor<CodeGen>{

    std::stringstream stream_;
    long LABEL_ID;

    VariableSet global;

    IStringIdent reference;	// GOTO语句用过的地址，用于检测是否地址没有被定义
    IStringIdent labels;	// 跳转地址
    IStringIdent strings;	// 程序里面的常量字符串

    DEFINE_AST_VISITOR_SUBCLASS_MEMBERS()

public:
    CodeGen() { LABEL_ID = 0; }
    DECLARE_VISIT_METHODS
    string GetStream();
};

#endif //BBC_CODEGEN_H
