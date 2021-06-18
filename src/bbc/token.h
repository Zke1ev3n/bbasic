#ifndef BBC_TOKEN_H
#define BBC_TOKEN_H

#include <map>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

/* token classes */
enum class TokenType {
    T_NONE,           /* no token has yet been identified */
    T_EOF,            /* end of file */
    T_EOL,            /* end of line */
    T_IDENTIFIER,     /* an identifier or keyword - token to be removed */
    T_INTEGER,        /* a numeric constant */
    T_FLOAT,          /* a float number */
    T_STRING,         /* a string constant */
    T_INTTYPE,        /* the int type */
    T_FLOATTYPE,      /* the float type */
    T_STRINGTYPE,     /* the string type */
    T_SHARP,          /* the sharp */
    T_DIM,            /* the DIM keyword */
    T_IF,             /* the IF keyword */
    T_THEN,           /* the THEN keyword */
    T_ELSE,           /* the ELSE keyword */
    T_GOTO,           /* the GOTO keyword */
    T_WHILE,          /* the WHILE keyword */
    T_WEND,           /* the WEND keyword */
    T_RETURN,         /* the RETURN keyword */
    T_END,            /* the END keyword */
    T_PRINT,          /* the PRINT keyword */
    T_INPUT,          /* the INPUT keyword */
    T_CLS,            /* the CLS keyword */
    T_DATA,           /* the data keyword */
    T_READ,           /* the read keyword */
    T_RESTORE,        /* the restore keyword */
    T_DECLARE,        /* the declare keyword */
    T_OPEN,           /* the open keyword */
    T_FOR,            /* the for keyword */
    T_BINARY,         /* the binary keyword */
    T_AS,             /* the as keyword */
    T_PUT,            /* the close keyword */
    T_GET,            /* the close keyword */
    T_CLOSE,          /* the close keyword */
    T_FUNCTION,       /* the function keyword */
    T_SUB,            /* the sub keyword */
    T_PLUS,           /* addition or unary positive */
    T_MINUS,          /* subtraction or unary negative */
    T_MULTIPLY,       /* multiplication */
    T_DIVIDE,         /* division */
    T_LPAREN,         /* ( */
    T_RPAREN,         /* ) */
    T_LBRACKET,       /* [ */
    T_RBRACKET,       /* ] */
    T_EQ,             /* = */
    T_NEQ,            /* <> or >< */
    T_LE,             /* < */
    T_LEQ,            /* <= */
    T_GE,             /* > */
    T_GEQ,            /* >= */
    T_COMMA,          /* , separator */
    T_SEMICOLON,      /* ; separator */
    T_COLON,          /* : separator */
    T_ILLEGAL         /* unrecognised characters */
};

// map used to associate the token type of a keyword
typedef std::map<std::string, TokenType> KeywordMap;
// map used to write the type of a token
typedef std::map<TokenType, std::string> TokenTypeMap;

struct Token {
    std::string lexeme_;
    union {
        int inum_;
        float fnum_;
    };

    int line_;
    int column_;
    TokenType type_;

    Token(): lexeme_(""), line_(0), column_(0), type_(TokenType::T_EOF){}
    Token(TokenType t, std::string word, int n, int line, int column) : type_(t), lexeme_(std::move(word)), inum_(n), line_(line), column_(column) {}
    Token(TokenType t, std::string word, float n, int line, int column) : type_(t), lexeme_(std::move(word)), fnum_(n), line_(line), column_(column) {}
    Token(TokenType t, std::string word, int line, int column) : type_(t), lexeme_(std::move(word)),line_(line), column_(column) {}
    // copy constructor is implicit defaulted
    Token(const Token& tok);
    // destructor is implicit defaulted
    ~Token() {}
    // assignment operator is implicit defaulted
    Token& operator=(const Token& tok);

    static bool is_cmp_op(Token t) {
        return t.type_ == TokenType::T_EQ || t.type_ == TokenType::T_NEQ
               || t.type_ == TokenType::T_LE || t.type_ == TokenType::T_LEQ
               || t.type_ == TokenType::T_GE || t.type_ == TokenType::T_GEQ;
    }

    static string get_type_string(TokenType type);
};

#endif //BBC_TOKEN_H