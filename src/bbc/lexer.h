#pragma once
#include <string>
#include <fstream>
#include <istream>
#include "token.h"

using namespace std;

class Lexer {
    istream* fin_;
    int line_ = 1;
    int column_ = 0;

    Token next_;
    Token lookahead_;

    inline char getc();
    public:
        Lexer(istream* fin) :fin_(fin) {}
        //解析
        Token Lex();
        Token LookAhead();
        Token NextToken();
};