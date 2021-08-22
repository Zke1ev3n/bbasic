#include "codegen.h"
#include "utils.h"


void CodeGen::VisitProgram(Program *node) {
    //获取当前的scope
    //top_scope_ = node->belonging_scope();
    //Output.VarArg("CALL LABEL%d ; For initialization\n",label);
    //stream_ << Utils::FormatString("CALL LABEL%d ; For initialization\n",label);
    stream_ << "Output<<\"\\n;================ MAIN PROG ==================\\n\";";
    for(auto line: node->lines()) {
        VisitLine(line);
    }
    stream_<<"EXIT\n";
    //TODO export func
    //TODO DATA
    stream_<<"\n;================ FUNCTIONS ==================\n";
    //top_scope_ = top_scope_->get_enclosing_scope();
}

void CodeGen::VisitLine(Line *node) {
    //TODO make label
    visit(node->statement());
}

void CodeGen::VisitAssignVariable(AssignVariable *node) {

    //右边的表达式
    visit(node->expr());
    //lvalue
    visit(node->target());
}

void CodeGen::VisitBinaryOperation(BinaryOperation *node) {
    string opr;
    visit(node->left());
    visit(node->right());
    stream_<<"POP r1\n";
    stream_<<"POP r0\n";
    switch(node->op().type_) {
        case TokenType::T_PLUS:
            opr = "ADD"; break;
        case TokenType::T_SUB:
            opr = "SUB"; break;
        case TokenType::T_MULTIPLY:
            opr = "MUL"; break;
        case TokenType::T_DIVIDE:
            opr = "DIV"; break;
    }
    //TODO 支持float和string类型
    stream_<<"CAL int " << opr << " r0, r1\n";
    stream_<<"PUSH r0\n";
}

void CodeGen::VisitLiteral(Literal *node) {
    //立即数
    stream_<<Utils::FormatString("PUSH %ld\n", node->value());
}

void CodeGen::VisitVariableProxy(VariableProxy *node) {
    //if(instack)
    if(node->target()->is_global()) {
        //output.VarArg("PUSH [%s]\n",vars[i]->name.GetString());
        stream_ << Utils::FormatString("PUSH [%s]\n", node->target()->get_name().c_str());
    }else{
        stream_<<"LD int r0,rb\n";
        //TODO 相对栈底
        stream_<<Utils::FormatString("CAL int ADD r0,%d\n", node->target()->get_index());
        stream_<<"PUSH [r0]\n";
    }
}