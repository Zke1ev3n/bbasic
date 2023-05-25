#include "ast_dumper.h"


void ASTDumper::VisitProgram(Program *node) {
    out_ << "program";
    begin_block();
    end_line();
    for(auto line: node->lines()){
        VisitLine(line);
        end_line();
    }
    end_block();
}

void ASTDumper::VisitLine(Line *node) {
    out_ << "line";
    begin_block();
    if(node->line_number() != 0) {
        end_line();
        out_ << "line_number = " << node->line_number();
    }
    if(node->label() != ""){
        end_line();
        out_ << "label = " << node->label();
    }
    end_line();
    visit(node->statement());
    end_block();
}

void ASTDumper::VisitVariableDeclaration(VariableDeclaration *node) {
    out_ << "variable declaration [ ";
    for (auto sym : node->variables())
        out_ << sym->name << ' ';
    out_.put(']');
}

void ASTDumper::VisitAssignVariable(AssignVariable *node) {
    // assign statement {
    out_ << "assign variable";
    begin_block();
    end_line();
    out_ << "target = ";
    VisitVariableProxy(node->target());
    // expression =
    end_line();
    visit(node->expr());
    end_block();
}

void ASTDumper::VisitVariableProxy(VariableProxy *node) {
    out_ << "varibale " << node->name();
}

void ASTDumper::VisitLiteral(Literal *node) {
    out_ << "literal " << node->value();
}

void ASTDumper::VisitLiteralString(LiteralString *node) {
    out_ << "literal_string " << node->value();
}

void ASTDumper::VisitExpression(Expression *node) {

}

void ASTDumper::VisitUnaryOperation(UnaryOperation *node) {
    out_ << "unary operation";
    begin_block();
    end_line();
    out_ << "operator = " << Token::get_type_string(node->op().type_);
    end_line();
    out_ << "expression = ";
    visit(node->expr());
    end_block();
}

void ASTDumper::VisitBinaryOperation(BinaryOperation *node) {
    // binary operation {
    out_ << "binary operation";
    begin_block();
    end_line();
    // operator =
    out_ << "operator = '" << Token::get_type_string(node->op().type_) << '\'';
    end_line();
    out_ << "left = ";
    visit(node->left());
    end_line();
    out_ << "right = ";
    visit(node->right());
    end_block();
}

void ASTDumper::VisitPrintStatement(PrintStatement *node) {
    out_ << "print";
    begin_block();
    end_line();
    for(int i = 0; i < node->expressions().size(); i++) {
        visit(node->expressions()[i]);
        end_line();
    }
    end_block();
}

void ASTDumper::VisitIFStatement(IFStatement *node) {
    out_ << "if";
    begin_block();
    end_line();
    out_ << "condition = ";
    visit(node->condition());
    end_line();
    out_ << "then = ";
    begin_block();
    end_line();
    for(auto line: node->then_lines()){
        VisitLine(line);
        end_line();
    }
    end_block();
    if (node->HasElseStatement()) {
        end_line();
        out_ << "else = ";
        begin_block();
        end_line();
        for(auto line: node->else_lines()){
            VisitLine(line);
            end_line();
        }
        end_block();
    }
    end_block();
}

void ASTDumper::VisitWhileStatement(WhileStatement *node) {
    out_ << "while";
    begin_block();
    end_line();
    out_ << "condition = ";
    visit(node->condition());
    end_line();
    out_ << "lines = ";

    begin_block();
    end_line();
    for(auto line : node->lines()){
        VisitLine(line);
        end_line();
    }
    end_block();

    end_block();
}

void ASTDumper::VisitGOTOStatement(GOTOStatement *node) {
    out_ << "goto" << node->label();
}


void ASTDumper::VisitEndStatement(EndStatement *node) {
    out_ << "end";
}

