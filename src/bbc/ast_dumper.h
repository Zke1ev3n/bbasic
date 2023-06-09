#ifndef BBC_AST_DUMPER_H
#define BBC_AST_DUMPER_H

#include <ostream>
#include "ast.h"

class ASTDumper : public ASTVisitor<ASTDumper> {
    DEFINE_AST_VISITOR_SUBCLASS_MEMBERS()

    std::ostream &out_;
    const int indent_size_;
    int indent_level_;

    void increase_indent() {
        indent_level_ += indent_size_;
    }

    void write_indent() {
        for (int i = 0; i < indent_level_; i++)
            out_.put(' ');
    }

    void end_line() {
        out_.put('\n');
        write_indent();
    }

    void begin_block() {
        indent_level_ += indent_size_;
        out_ << " {";
    }

    void end_block() {
        indent_level_ -= indent_size_;
        end_line();
        out_ << "}";
    }

public:
    explicit ASTDumper(std::ostream &out, int indent_size = 2)
    : out_(out), indent_size_(indent_size), indent_level_(0) { }

    DECLARE_VISIT_METHODS
};

#endif //BBC_AST_DUMPER_H
