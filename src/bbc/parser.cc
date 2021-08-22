#include "parser.h"

Token Parser::NextToken() {
    current_token_ = lexer_->NextToken();
    return current_token_;
}

Token Parser::LookAhead() {
    return lexer_->LookAhead();
}


void Parser::EnterScope() {
    top_ = new Scope(top_);
}

void Parser::LeaveScope() {
    Scope *inner = top_;
    top_ = top_->get_enclosing_scope();
}

Program* Parser::ParseProgram() {
    EnterScope();
    vector<Line*> lines = ParseLines();
    if(current_token_.type_ != TokenType::T_EOF) {
        throw CompileException("expect EOF", current_token_);
    }
    LeaveScope();
    return new Program(lines);
}

//TODO 前看符号
vector<Line*> Parser::ParseLines() {
//    vector<Line*> lines;
//    Line* line = ParseLine();
//    lines.push_back(line);
//    if(tok.GetType() != TokenType::T_EOF) {
//        vector<Line*> lines2 = ParseLines();
//        lines.insert(lines.end(), lines2.begin(), lines2.end());
//    }
//
//    return lines;

    vector<Line*> lines;

    //前看，避免回溯
    while(LookAhead().type_ != TokenType::T_EOF && LookAhead().type_ != TokenType::T_ELSE) {
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
    }else {
        Statement* statement = ParseStatement();
        if(statement){
            line = new Line(statement);
        }
    }

    if(current_token_.type_ != TokenType::T_EOL && current_token_.type_ != TokenType::T_EOF) {
        throw CompileException("except EOL", current_token_);
    }

    return line;
}

Statement* Parser::ParseStatement() {
    Statement* statement = nullptr;
    switch(current_token_.type_) {
        case TokenType::T_IF:
            statement = ParseIFStatement();
            break;
        case TokenType::T_DIM:
            statement = ParseVariableDeclare();
            break;
        case TokenType::T_IDENTIFIER:
            statement = ParseAssignVariable();
            break;
        case TokenType::T_END:
            if(NextToken().type_ == TokenType::T_IF) {
                //skip if
                NextToken();
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
        //数组
        if (current_token_.type_ == TokenType::T_LPAREN) {
            NextToken();

            while(current_token_.type_ != TokenType::T_RPAREN){
                if(current_token_.type_ != TokenType::T_INTEGER) {
                    //error
                    //TODO
                    throw CompileException("expect integer", current_token_);
                }
            }
            //这里还不支持数组，暂时都这样吧
            auto sym = new Variable(name, top_->get_level(), top_->get_variable_count(), true);
            vars.push_back(sym);
            top_->define(sym);
        }else{
            auto sym = new Variable(name, top_->get_level(), top_->get_variable_count(), true);
            vars.push_back(sym);
            top_->define(sym);
        }

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
    VariableProxy* var_proxy;
    //当前仅支持int
    //int type = GetVariableType();

    var_proxy = LocalVariable();
    NextToken();

    return new AssignVariable(var_proxy, ParseExpression());
}

IFStatement* Parser::ParseIFStatement() {
    Expression* condition;

    auto left = ParseExpression();
    Token cmp_op = current_token_;
    //NextToken();
    if (!Token::is_cmp_op(current_token_)) {
        throw CompileException("expect compare operand", current_token_);
    }
    condition = new BinaryOperation(cmp_op, left, ParseExpression());
    if(current_token_.type_ != TokenType::T_THEN) {
        throw CompileException("expect THEN", current_token_);
    }

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

    NextToken();

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
//    if(has_endif == 1) {
//        if(current_token_.type_ != TokenType::T_IF){
//            throw CompileException("expect IF", current_token_);
//        }
//    }

    return new IFStatement(condition, then_lines, else_lines);
}

Expression* Parser::ParseExpression() {
    Expression* left;

    NextToken();
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
            Symbol *sym = top_->resolve(id);
            if (sym == nullptr)
                throw CompileException("undeclared identifier", current_token_);
            return new VariableProxy{sym};
        }
        case TokenType::T_INTEGER: {
            int num = current_token_.inum_;
            NextToken();
            return new Literal(num);
        }
        case TokenType::T_LPAREN: {
            Expression *expr = ParseExpression();
            if (current_token_.type_ != TokenType::T_RPAREN) {
                throw CompileException("expect )", current_token_);
            }
            return expr;
        }
        default: {
            throw CompileException("unexpected token", current_token_);
        }
    }
}

// expressions
VariableProxy * Parser::LocalVariable() {
    std::string id = current_token_.lexeme_;
    Symbol *sym = top_->resolve(id);
    if (sym == nullptr) {
        //throw general_error("undeclared identifier \"", id, '"');
        throw CompileException("undeclared identifier", current_token_);
    } else if (sym->is_variable()) {
        return new VariableProxy(dynamic_cast<Variable*>(sym));
    } else {
        throw CompileException("cannot assign value to a non-variable", current_token_);
    }
}