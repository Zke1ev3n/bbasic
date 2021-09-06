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
    end_line();
    visit(node->statement());
    end_block();
}

void ASTDumper::VisitVariableDeclaration(VariableDeclaration *node) {
    out_ << "variable declaration [ ";
    for (auto sym : node->variables())
        out_ << sym << ' ';
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
    string var = node->name();
//    if (sym->is_constant()) {
//        out_ << "constant ";
//    } else if (sym->is_variable()) {
//        out_ << "variable ";
//    } else if (sym->is_procedure()) {
//        out_ << "procedure ";
//    }
    out_ << var;
}

void ASTDumper::VisitLiteral(Literal *node) {
    out_ << "literal " << node->value();
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

void ASTDumper::VisitIFStatement(IFStatement *node) {
    out_ << "if";
    begin_block();
    end_line();
    out_ << "condition = ";
    visit(node->condition());
    end_line();
    out_ << "then = ";
    for(auto line: node->then_lines()){
        VisitLine(line);
        end_line();
    }
    if (node->HasElseStatement()) {
        end_line();
        out_ << "else = ";
        for(auto line: node->else_lines()){
            VisitLine(line);
            end_line();
        }
    }
    end_block();
}

void ASTDumper::VisitEndStatement(EndStatement *node) {
    out_ << "end";
}

