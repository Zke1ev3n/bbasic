//
// Created by 梁玉林 on 2021/6/9.
//

#ifndef BBC_CODEGEN_H
#define BBC_CODEGEN_H

#include <sstream>
#include "ast.h"

class CodeGen:public ASTVisitor<CodeGen>{

    Scope *top_scope_;
    std::ostringstream stream_;

    DEFINE_AST_VISITOR_SUBCLASS_MEMBERS()
    DECLARE_VISIT_METHODS

public:
    CodeGen() : top_scope_(nullptr) { }

    void gen(Program *program);
};

#endif //BBC_CODEGEN_H
