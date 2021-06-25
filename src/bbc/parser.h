#pragma once
#include "lexer.h"
#include "scope.h"
#include "ast.h"
#include "exception.h"

class Parser {
    Lexer* lexer_;
    //当前token的类型
    Token current_token_;
    //前看
    Token next_token_;

    Scope *top_;

private:

    VariableProxy* LocalVariable();

    //scope control
    void EnterScope();
    void LeaveScope();

    int GetVariableType();
    Token NextToken();
    Token LookAhead();

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
    Parser(Lexer* lexer): lexer_(lexer),  top_(nullptr) {};
    Program* ParseProgram();


};