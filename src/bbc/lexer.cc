#include "lexer.h"

#include <iostream>

#include "token.h"

//TODO 优化错误line/column
KeywordMap keywordMap{
    {"DIM", TokenType::T_DIM},
    {"IF", TokenType::T_IF},
    {"THEN", TokenType::T_THEN},
    {"ELSE", TokenType::T_ELSE},
    {"GOTO", TokenType::T_GOTO},
    {"END", TokenType::T_END},
    {"RETURN", TokenType::T_RETURN},
    {"WHILE", TokenType::T_WHILE},
    {"WEND", TokenType::T_WEND},
    {"PRINT", TokenType::T_PRINT},
    {"DATA", TokenType::T_DATA},
    {"READ", TokenType::T_READ},
    {"RESTORE", TokenType::T_RESTORE},
    {"DECLARE", TokenType::T_DECLARE},
    {"FUNCTION", TokenType::T_FUNCTION},
    {"SUB", TokenType::T_SUB},
    {"OPEN", TokenType::T_OPEN},
    {"FOR", TokenType::T_FOR},
    {"BINARY", TokenType::T_BINARY},
    {"AS", TokenType::T_AS},
    {"GET", TokenType::T_GET},
    {"PUT", TokenType::T_PUT},
    {"CLOSE", TokenType::T_CLOSE},
};

inline bool is_identifier_part(int ch) { return isalnum(ch) || ch == '_'; }

char Lexer::getc() {
    column_++;
    return fin_->get();
}

Token Lexer::Lex() {
    char c, c1;
    //TODO 这里c=fin_.get()必须加上括号
    while ((c = getc()) && fin_->good()) {
        //sikp spaces
        if (c == ' ' || c == '\t') {
            while((c = getc()) && (c == ' ' || c == '\t'));
        }
        // check and skip comment
        // TODO put back
        if (c == '\'') {
            c = getc();
            while (c && !fin_->eof()) {
                c = getc();
                if (c == '\n') {
                    break;
                }
            }
            if (c == ' ' || c == '\t') {
            while((c = getc()) && (c == ' ' || c == '\t'));
            }
        }
        switch (c) {
            case '\n': {
                 // lexeme
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_EOL, t_lexme, line_, column_);
                line_++;
                column_ = 0;
                return t;
            }
            case '+': {
                // lexeme
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_PLUS, t_lexme, line_, column_);
                return t;
            }
            case '-': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_MINUS, t_lexme, line_, column_);
                return t;
            }
            case '*': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_MULTIPLY, t_lexme, line_, column_);
                return t;
            }
            case '/': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_DIVIDE, t_lexme, line_, column_);
                return t;
            }
            case ',': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_COMMA, t_lexme, line_, column_);
                return t;
            }
            case '(': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_LPAREN, t_lexme, line_, column_);
                return t;
            }
            case ')': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_RPAREN, t_lexme, line_, column_);
                return t;
            }
            case '[': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_LBRACKET, t_lexme, line_, column_);
                return t;
            }
            case ']': {
                std::string t_lexme;
                t_lexme.push_back(c);
                // token
                Token t(TokenType::T_RBRACKET, t_lexme, line_, column_);
                return t;
            }
            case '<':{
				// lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                c1 = getc();

				if (c1 == '=') {
					t_lexme.push_back(c1);
					// token
					Token t(TokenType::T_LEQ, t_lexme, line_, column_);
					return t;
				}
				else {
					fin_->putback(c1);
                    column_--;
					// token
					Token t(TokenType::T_LE, t_lexme, line_, column_);
					return t;
				}
			}
			case '>':{
				// lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                c1 = getc();
				if (c1 == '=') {
					t_lexme.push_back(c1);
					// token
					Token t(TokenType::T_GEQ, t_lexme, line_, column_);
					return t;
				}
				else {
					fin_->putback(c1);
                    column_--;
					// token
					Token t(TokenType::T_GE, t_lexme, line_, column_);
					return t;
				}

			}
            case '=': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_EQ, t_lexme, line_, column_);
                return t;
            }
            case '%': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_INTTYPE, t_lexme, line_, column_);
                return t;
            }
            case '!': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_FLOATTYPE, t_lexme, line_, column_);
                return t;
            }
            case '$': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_STRINGTYPE, t_lexme, line_, column_);
                return t;
            }
            case ':': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_COLON, t_lexme, line_, column_);
                return t;
            }
            case ';': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_SEMICOLON, t_lexme, line_, column_);
                return t;
            }
            case '\"': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                while ((c1 =getc()) && c1 != '\"') {
                        t_lexme.push_back(c1);
                }
                t_lexme.push_back(c1);
                Token t(TokenType::T_STRING, t_lexme, line_, column_);
                return t;
            }
            case '#': {
                // lexeme
				std::string t_lexme;
				t_lexme.push_back(c);
                Token t(TokenType::T_SHARP, t_lexme, line_, column_);
                return t;
            }
            default: {
                if (isdigit(c)) { // a n constant or a x.y constant
				// lexeme
					std::string t_lexme;
					t_lexme.push_back(c);
					// numerical values are stored in these variables
					int iVal = 0;
					float xVal = 0.0;

                    int dot=0;
		            while ((c1 = getc()) && (isdigit(c1) || ( dot==0 && c1=='.'))) {
			            if (c1 =='.') dot=1;
                        t_lexme.push_back(c1);
		            }

                    fin_->putback(c1);
                    column_--;
		            if (!dot) {
			            sscanf(t_lexme.c_str(),"%d",&iVal);
                        Token t(TokenType::T_INTEGER, t_lexme, iVal, line_, column_);
                        return t;
		            }else{
                         sscanf(t_lexme.c_str(),"%f",&xVal);
                        Token t(TokenType::T_FLOAT, t_lexme, xVal, line_, column_);
                        return t;
                    }

				} else if (isalpha(c)) {
                    string t_lexme;
                    t_lexme.push_back(c);
                    while ((c1 = getc()) && is_identifier_part(c1)) {
                        t_lexme.push_back(c1);
                    }
                    fin_->putback(c1);
                    column_--;

                    if (keywordMap.find(t_lexme) != keywordMap.end()) {
                        // keyword detected
                        Token t(keywordMap[t_lexme], t_lexme, line_, column_);
                        return t;
                    } else {
                        Token t(TokenType::T_IDENTIFIER, t_lexme, line_, column_);
                        return t;
                    }
                }else {
                    string t_lexme;
                    t_lexme.push_back(c);
                    Token t(TokenType::T_ILLEGAL, t_lexme, line_, column_);
                    return t;
                }
            }
        }
    }
    return Token(TokenType::T_EOF, "", line_, column_);
}

Token Lexer::NextToken() {
    if(lookahead_.type_ != TokenType::T_EOF) {
        next_ = lookahead_;
        lookahead_.type_ = TokenType::T_EOF;
    }else{
        next_ = Lex();
    }
    return next_;
}

Token Lexer::LookAhead() {
    if(lookahead_.type_ == TokenType::T_EOF){
        lookahead_ = Lex();
    }
    return lookahead_;
}