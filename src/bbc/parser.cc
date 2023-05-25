#include "parser.h"

Token Parser::NextToken() {
    current_token_ = lexer_->NextToken();
    return current_token_;
}

Token Parser::LookAhead() {
    return lexer_->LookAhead();
}

Program* Parser::ParseProgram() {
    vector<Line*> lines = ParseLines();
    if(current_token_.type_ != TokenType::T_EOF) {
        throw CompileException("expect EOF", current_token_);
    }
    return new Program(lines);
}

//TODO 前看符号
vector<Line*> Parser::ParseLines() {
    vector<Line*> lines;

    //前看，避免回溯
    //TODO 优化
    while(LookAhead().type_ != TokenType::T_EOF && LookAhead().type_ != TokenType::T_ELSE &&
            !(current_token_.type_ == TokenType::T_END && LookAhead().type_ == TokenType::T_IF) && current_token_.type_ != TokenType::T_WEND) {
        Line* line = ParseLine();
        if(line) {
            lines.push_back(line);
        }
    }
    return lines;
}

Line* Parser::ParseLine() {
    int line_number;
    Line* line = nullptr;

    NextToken();

    //TODO Statements
    if(current_token_.type_ == TokenType::T_EOL) {
        return nullptr;
    }
    else if(current_token_.type_ == TokenType::T_INTEGER){
        line_number = current_token_.inum_;
        NextToken();
        Statement* statement = ParseStatement();
        if(statement){
            line = new Line(statement, line_number);
        }
    }else if(current_token_.type_ == TokenType::T_IDENTIFIER && LookAhead().type_ == TokenType::T_COLON){
        string label = current_token_.lexeme_;
        NextToken();
        NextToken();
        //跳过换行
        if(current_token_.type_ == TokenType::T_EOL) NextToken();
        Statement* statement = ParseStatement();
        if(statement){
            line = new Line(statement, label);
        }
    }else{
        Statement* statement = ParseStatement();
        if(statement){
            line = new Line(statement);
        }
    }

    //TODO 优化
    if(current_token_.type_ != TokenType::T_EOL && current_token_.type_ != TokenType::T_EOF
    && current_token_.type_ != TokenType::T_END && current_token_.type_ != TokenType::T_WEND) {
        throw CompileException("except EOL", current_token_);
    }

    return line;
}

Statement* Parser::ParseStatement() {
    Statement* statement = nullptr;
    switch(current_token_.type_) {
        case TokenType::T_WHILE:
            statement = ParseWhileStatement();
            break;
        case TokenType::T_IF:
            statement = ParseIFStatement();
            break;
        case TokenType::T_ELSE:
            break;
        case TokenType::T_GOTO:
            statement = ParseGOTOStatement(0);
            break;
        case TokenType::T_DIM:
            statement = ParseVariableDeclare();
            break;
        case TokenType::T_IDENTIFIER:
            statement = ParseAssignVariable();
            break;
        case TokenType::T_PRINT:
            statement = ParsePrintStatement();
            break;
        case TokenType::T_WEND:
            break;
        case TokenType::T_END:
            if(LookAhead().type_ == TokenType::T_IF) {
                //skip if
                break;
            }
            statement = new EndStatement();
            break;
        default:
            break;
    }
    return statement;
}

int Parser::GetVariableType() {
	int type=ES_VARINT;
	if (current_token_.type_ == TokenType::T_INTTYPE) {
		type=ES_VARINT;
		NextToken();
	}else if(current_token_.type_ == TokenType::T_FLOATTYPE) {
        type=ES_VARFLOAT;
        NextToken();
    }else if(current_token_.type_ == TokenType::T_STRINGTYPE) {
        type=ES_VARSTRING;
        NextToken();
    }
	return type;
}

VariableDeclaration* Parser::ParseVariableDeclare() {
    VariableDeclaration::list_type vars;

    NextToken();
    while(true) {

        if(current_token_.type_ != TokenType::T_IDENTIFIER){
            throw CompileException("expect identifier", current_token_);
        }

        string name = current_token_.lexeme_;
        NextToken();
        int type = GetVariableType();
        //TODO 目前不支持数组
        VariableSymbol* var = new VariableSymbol();
        var->name = name;
        var->type = type;
        vars.push_back(var);

        if (current_token_.type_ == TokenType::T_COMMA) {
			NextToken();
		}	else break;

    }

    return new VariableDeclaration(std::move(vars));
}


/*
a = 1
a = 'aaa'
a(1,2) = 1
a(1,2) = 'aaa'
func(1,2)
*/
AssignVariable* Parser::ParseAssignVariable() {
    VariableProxy* var;

    //if(current_token_.type_ == )

    var = LocalVariable();
    NextToken();

    return new AssignVariable(var, ParseExpression());
}

PrintStatement* Parser::ParsePrintStatement() {
    vector<Expression*> expressions;

    NextToken();
    while(true) {
        if(current_token_.type_ == TokenType::T_EOL || current_token_.type_ == TokenType::T_EOF) {
            //0是换行，1是制表
            expressions.push_back(new Literal(0));
            break;
        }
        //:
        if(current_token_.type_ == TokenType::T_COLON) {
            //expressions.push_back(new LiteralString("\n"));
            expressions.push_back(new Literal(0));
            break;
        }
        //;
        if(current_token_.type_ == TokenType::T_SEMICOLON) {
            NextToken();
            if(current_token_.type_ == TokenType::T_EOL || current_token_.type_ == TokenType::T_EOF) {
                break;
            }
        }
        //,
        else if(current_token_.type_ == TokenType::T_COMMA) {
            NextToken();
            //expressions.push_back(new LiteralString("\t"));
            expressions.push_back(new Literal(1));
            if(current_token_.type_ == TokenType::T_EOL || current_token_.type_ == TokenType::T_EOF) {
                break;
            }
        }

        if(current_token_.type_ == TokenType::T_EOL || current_token_.type_ == TokenType::T_EOF) {
            //expressions.push_back(new LiteralString("\n"));
            expressions.push_back(new Literal(0));
            break;
        }

        Expression* r = ParseExpression();
        expressions.push_back(r);
    }

    return new PrintStatement(expressions);
}

IFStatement* Parser::ParseIFStatement() {

    int has_endif = 1;
    NextToken();
    auto expr = ParseExpression();

    NextToken();

    vector<Line*> then_lines;
    vector<Line*> else_lines;

    //TODO 优化 Lines和Statement
    //多行
    if(current_token_.type_ == TokenType::T_EOL) {
        then_lines = ParseLines();
    }else{
        Line* single_line = ParseLine();
        then_lines.push_back(single_line);
    }

    //TODO 优化逻辑
    if(current_token_.type_ != TokenType::T_END) NextToken();

    if(current_token_.type_ == TokenType::T_ELSE) {
        NextToken();
        if(current_token_.type_ == TokenType::T_EOL) {
            else_lines = ParseLines();
        }else{
            Line* single_line = ParseLine();
            else_lines.push_back(single_line);
        }
    }

    //TODO 校验END IF
    if(has_endif == 1) {
        if(current_token_.type_ != TokenType::T_END){
            throw CompileException("expect IF", current_token_);
        }
        NextToken();
        NextToken();
    }

    return new IFStatement(expr, then_lines, else_lines);
}

WhileStatement* Parser::ParseWhileStatement() {

    int mode =0;

    vector<Line*> lines;

    NextToken();
    auto expr = ParseExpression();

    /*
     * WHILE expr : statement
     */
    if(current_token_.type_ == TokenType::T_COLON){
        mode = 1;
    } else if(current_token_.type_ == TokenType::T_EOL) {
    }else{
        throw CompileException("expect EOL", current_token_);
    }

    if(mode ==0){
        lines = ParseLines();
    }else{
        Line* single = ParseLine();
        lines.push_back(single);
        NextToken();
    }

    if(current_token_.type_ != TokenType::T_WEND){
        throw CompileException("expect WEND", current_token_);
    }

    NextToken();

    return new WhileStatement(expr, lines);
}

GOTOStatement* Parser::ParseGOTOStatement(int callf) {
    NextToken();
    if(current_token_.type_ != TokenType::T_IDENTIFIER) {
        throw CompileException("expect identifier", current_token_);
    }

    string label = current_token_.lexeme_;

    //LABEL
    NextToken();

    return new GOTOStatement(label, callf);
}

/*
 *
 */
Expression* Parser::ParseExpression() {
    Expression* left = ParseAddSubExpression();
    while(current_token_.type_ == TokenType::T_EQ|| current_token_.type_ == TokenType::T_NEQ
        || current_token_.type_ == TokenType::T_GE || current_token_.type_ == TokenType::T_GEQ
        || current_token_.type_ == TokenType::T_LE || current_token_.type_ == TokenType::T_LEQ) {
        Token op = current_token_;
        NextToken();
        left = new BinaryOperation(op, left, ParseAddSubExpression());
    }

    return left;
}

//关系表达式
Expression* Parser::ParseAddSubExpression() {
    Expression* left;

    if(current_token_.type_ == TokenType::T_PLUS || current_token_.type_ == TokenType::T_MINUS) {
        Token op = current_token_;
        NextToken();
        left = new UnaryOperation(op, ParseTerm());
    }else{
        left = ParseTerm();
    }

    while(current_token_.type_ == TokenType::T_PLUS || current_token_.type_ == TokenType::T_MINUS) {
        Token op = current_token_;
        NextToken();
        Expression* right = ParseTerm();
        left = new BinaryOperation(op, left, right);
    }
    return left;
}

Expression* Parser::ParseTerm() {
    Expression* left = ParseFactor();
    while(current_token_.type_ == TokenType::T_MULTIPLY || current_token_.type_ == TokenType::T_DIVIDE) {
        Token op = current_token_;
        NextToken();
        left = new BinaryOperation(op, left, ParseFactor());
    }

    return left;
}

Expression* Parser::ParseFactor() {
    switch(current_token_.type_) {
        case TokenType::T_IDENTIFIER: {
            std::string id = current_token_.lexeme_;
            NextToken();
            return new VariableProxy(id);
        }
        case TokenType::T_INTEGER: {
            int num = current_token_.inum_;
            NextToken();
            return new Literal(num);
        }
        case TokenType::T_LPAREN: {
            NextToken();
            Expression *expr = ParseExpression();
            if (current_token_.type_ != TokenType::T_RPAREN) {
                throw CompileException("expect )", current_token_);
            }
            NextToken();
            return expr;
        }
        case TokenType::T_STRING: {
            string str = current_token_.lexeme_;
            NextToken();
            return new LiteralString(str);
        }
        default: {
            throw CompileException("unexpected token", current_token_);
        }
    }
}

// expressions
VariableProxy * Parser::LocalVariable() {
    std::string id = current_token_.lexeme_;
    NextToken();
    return new VariableProxy(id);
}