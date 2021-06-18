#pragma once
#include "lexer.h"
#include "symbol.h"
#include "ast.h"
#include "exception.h"

class Parser {
    Lexer* lexer_;
    //当前token的类型
    Token current_token_;
    //前看
    Token next_token_;

    //全局符号
    SymbolTable* global_;
    //所有函数
    vector<Function*> functions_;
    Function* current_func_;
    int func_count_;

public:
    Program* ParseProgram();
    vector<Line*> ParseLines();
    Line* ParseLine();
    Statement* ParseStatement();
    VariableDeclaration* ParseVariableDeclare();
    AssignVariable* ParseAssignVariable();
    IFStatement* ParseIFStatement();
    Expression* ParseExpression();
    Expression* ParseTerm();
    Expression* ParseFactor();

public:
    Parser(Lexer* lexer): lexer_(lexer){};
    int GetVariableType();

    Token NextToken();
    Token LookAhead();

};