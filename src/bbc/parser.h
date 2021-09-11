#pragma once
#include "lexer.h"
#include "ast.h"
#include "exception.h"
#include "symbol.h"

class Parser {
    Lexer* lexer_;
    //当前token的类型
    Token current_token_;
    //前看
    Token next_token_;

private:

    VariableProxy* LocalVariable();

    int GetVariableType();
    Token NextToken();
    Token LookAhead();

    vector<Line*> ParseLines();
    Line* ParseLine();
    Statement* ParseStatement();
    VariableDeclaration* ParseVariableDeclare();
    AssignVariable* ParseAssignVariable();
    IFStatement* ParseIFStatement();
    PrintStatement* ParsePrintStatement();
    Expression* ParseExpression();
    Expression* ParseAddSubExpression();
    Expression* ParseTerm();
    Expression* ParseFactor();

public:
    Parser(Lexer* lexer): lexer_(lexer) {};
    Program* ParseProgram();
};