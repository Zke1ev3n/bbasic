//
// Created by 梁玉林 on 2021/6/9.
//

#ifndef BBC_CODEGEN_H
#define BBC_CODEGEN_H

#include <sstream>
#include "ast.h"
#include "symbol.h"

class CodeGen:public ASTVisitor<CodeGen>{

    std::stringstream stream_;
    long LABEL_ID;

    VariableSet global;

    DEFINE_AST_VISITOR_SUBCLASS_MEMBERS()

public:
    CodeGen() { LABEL_ID = 0; }
    DECLARE_VISIT_METHODS
    string GetStream();
};

#endif //BBC_CODEGEN_H
