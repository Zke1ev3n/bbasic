#include "token.h"

//TODO 优化
// map used to write the type of a token
TokenTypeMap kTokenTypeMap{
        {TokenType::T_IDENTIFIER, "identfiier"},
        {TokenType::T_INTEGER, "integer"},
        {TokenType::T_FLOAT, "float"},
        {TokenType::T_STRING, "string"},
        {TokenType::T_INTTYPE, "INTTYPE"},
        {TokenType::T_FLOATTYPE, "FLOATTYPE"},
        {TokenType::T_STRINGTYPE, "STRINGTYPE"},
        {TokenType::T_SHARP, "SHARP"},
        {TokenType::T_EOF, "EOF"},
        {TokenType::T_EOL, "NEWLINE"},
        {TokenType::T_DIM, "DIM"},
        {TokenType::T_IF, "IF"},
        {TokenType::T_THEN, "THEN"},
        {TokenType::T_ELSE, "ELSE"},
        {TokenType::T_THEN, "THEN"},
        {TokenType::T_GOTO, "GOTO"},
        {TokenType::T_WHILE, "WHILE"},
        {TokenType::T_WEND, "WEND"},
        {TokenType::T_RETURN, "RETURN"},
        {TokenType::T_END, "END"},
        {TokenType::T_PRINT, "PRINT"},
        {TokenType::T_DATA, "DATA"},
        {TokenType::T_READ, "READ"},
        {TokenType::T_RESTORE, "RESTORE"},
        {TokenType::T_DECLARE, "DECLARE"},
        {TokenType::T_FUNCTION, "FUNCTION"},
        {TokenType::T_SUB, "SUB"},
        {TokenType::T_OPEN, "OPEN"},
        {TokenType::T_FOR, "FOR"},
        {TokenType::T_BINARY, "BINARY"},
        {TokenType::T_AS, "AS"},
        {TokenType::T_GET, "GET"},
        {TokenType::T_PUT, "PUT"},
        {TokenType::T_CLOSE, "CLOSE"},
        {TokenType::T_SUB, "SUB"},
        {TokenType::T_INPUT, "INPUT"},
        {TokenType::T_PLUS, "PLUS"},
        {TokenType::T_MINUS, "MINUS"},
        {TokenType::T_MULTIPLY, "MULTIPLY"},
        {TokenType::T_DIVIDE, "DIVIDE"},
        {TokenType::T_LPAREN, "LPAREN"},
        {TokenType::T_RPAREN, "RPAREN"},
        {TokenType::T_LBRACKET, "LBRACKET"},
        {TokenType::T_RBRACKET, "RBRACKET"},
        {TokenType::T_EQ, "EQ"},
        {TokenType::T_NEQ, "NEQ"},
        {TokenType::T_LE, "LE"},
        {TokenType::T_LEQ, "LEQ"},
        {TokenType::T_GE, "GE"},
        {TokenType::T_GEQ, "GEQ"},
        {TokenType::T_COMMA, "COMMA"},
        {TokenType::T_END, "END"},
        {TokenType::T_ILLEGAL, "ILLEGAL"},
};

Token::Token(const Token& t) {
	lexeme_ = t.lexeme_;
	// copy operations
	switch (t.type_) {
	case TokenType::T_INTEGER:
		inum_ = t.inum_;
		break;
    case TokenType::T_FLOAT:
        fnum_ = t.fnum_;
        break;
//	case TokenType::T_IDENTIFIER:
//		new (&id)(std::string)(tok.id);
//		break;
	default:
		break;
	}
	type_ = t.type_;
    line_ = t.line_;
    column_ = t.column_;
}

Token& Token :: operator =(const Token& t) {
	lexeme_ = t.lexeme_;
	if (type_ == TokenType::T_IDENTIFIER && t.type_ == TokenType::T_IDENTIFIER) {
		return *this;
	}
	// the current token type = id
	// if (type == TokenType::T_IDENTIFIER) {
	// 	id.~basic_string <char >(); // destroy explicitly
	// }
	switch (t.type_) {
	    case TokenType::T_INTEGER:
		    inum_ = t.inum_;
		    break;
        case TokenType::T_FLOAT:
            fnum_ = t.fnum_;
            break;
//	    case TokenType::T_IDENTIFIER:
//		    new (&id)(std::string)(tok.id);
//		    break;
	    default:
		    break;
	}
	type_ = t.type_;
	line_ = t.line_;
	column_ = t.column_;
	return *this;
}

string Token::get_type_string(TokenType type) {
    return kTokenTypeMap[type];
}