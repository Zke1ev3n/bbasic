#ifndef BBC_AST_H
#define BBC_AST_H

#include <vector>
#include "token.h"
#include "symbol.h"

#define AST_NODE_LIST(V) \
    V(Program)           \
    V(Line)              \
    V(VariableDeclaration) \
    V(VariableProxy)     \
    V(AssignVariable)    \
    V(Expression)       \
    V(UnaryOperation)    \
    V(BinaryOperation)  \
    V(Literal)           \
    V(LiteralString)     \
    V(WhileStatement)    \
    V(GOTOStatement)     \
    V(IFStatement)       \
    V(PrintStatement)    \
    V(EndStatement)     \


#define DEF_ENUM_AST_NODE_TYPE(type) type,
enum class ASTNodeType {
    AST_NODE_LIST(DEF_ENUM_AST_NODE_TYPE)
};
#undef DEF_ENUM_AST_NODE_TYP

#define PROPERTY_GETTER(field) decltype(field##_) field() const { return field##_; }

#define PROPERTY_CONST_REF_GETTER(field) const decltype(field##_) &field() const { return field##_; }

class ASTNode {
    ASTNodeType type_;
public:
    explicit ASTNode(ASTNodeType type) : type_(type) { }

    ASTNodeType type() const {
        return type_;
    }

    virtual ~ASTNode() = default;
};

//语句
class Statement : public ASTNode {
public:
    explicit Statement(ASTNodeType type) : ASTNode(type) { }

    ~Statement() override = default;

};

class Line : public ASTNode {
private:
    Statement* statement_;
    int line_number_;
    string label_;

public:
    explicit Line(Statement* statement, int line_number, string label) : ASTNode(ASTNodeType::Line), statement_(statement), line_number_(line_number), label_(label) {}
    explicit Line(Statement* statement, string label) : ASTNode(ASTNodeType::Line), statement_(statement), label_(label) {}
    explicit Line(Statement* statement, int line_number) : ASTNode(ASTNodeType::Line), statement_(statement), line_number_(line_number) {}
    explicit Line(Statement* statement) : ASTNode(ASTNodeType::Line), statement_(statement){}

    PROPERTY_GETTER(statement)
    PROPERTY_GETTER(line_number)
    PROPERTY_GETTER(label)
};

class Lines : public ASTNode {
private:
    vector<Line*> lines;

};


class Program : public ASTNode {
private:
    //TODO 这里其实
    //Scope *belonging_scope_;
    vector<Line*> lines_;

public:
    explicit Program(vector<Line*> lines): ASTNode(ASTNodeType::Program), lines_(std::move(lines)) {}

    //PROPERTY_GETTER(belonging_scope)

    PROPERTY_GETTER(lines)
};

class Expression : public ASTNode {
    int expr_type_;
public:
    explicit Expression(ASTNodeType type) : ASTNode(type) { }

    ~Expression() override = default;

    void SetType(int expr_type) {expr_type_ = expr_type;}

    PROPERTY_GETTER(expr_type)

};

class UnaryOperation : public Expression {
    Token op_;
    Expression *expr_;
public:
    UnaryOperation(Token op, Expression *expr) : Expression(ASTNodeType::UnaryOperation), op_(op), expr_(expr) { }

    ~UnaryOperation() final {
        delete expr_;
    }

    PROPERTY_GETTER(op)

    PROPERTY_GETTER(expr)
};

class BinaryOperation : public Expression {
    Token op_;
    Expression* left_;
    Expression* right_;

public:
    explicit BinaryOperation(Token op, Expression* left, Expression* right) : Expression(ASTNodeType::BinaryOperation),
                            op_(op), left_(left), right_(right) {}

    ~BinaryOperation() final {
        delete left_;
        delete right_;
    }

    PROPERTY_GETTER(op)

    PROPERTY_GETTER(left)

    PROPERTY_GETTER(right)
};


class Literal : public Expression {
    int value_;
public:
    explicit Literal(int value)
            : Expression(ASTNodeType::Literal), value_(value) { }

    ~Literal() final = default;

    PROPERTY_GETTER(value)
};

class LiteralString : public Expression {
    string value_;
public:
    explicit LiteralString(string value)
            : Expression(ASTNodeType::LiteralString), value_(value) { }

    ~LiteralString() final = default;

    PROPERTY_GETTER(value)
};

class VariableProxy : public Expression {
    string name_;

public:
    explicit VariableProxy(string name)
            : Expression(ASTNodeType::VariableProxy), name_(name) { }

    ~VariableProxy() final = default; // TODO add a proper destructor here

    PROPERTY_GETTER(name)
};

class VariableDeclaration : public Statement {
public:
    typedef std::vector<VariableSymbol*> list_type;

private:
    const list_type variables_;

public:
    explicit VariableDeclaration(list_type variables)
            : Statement(ASTNodeType::VariableDeclaration), variables_(std::move(variables)) { }

    ~VariableDeclaration() override = default;

    PROPERTY_CONST_REF_GETTER(variables)
};

class AssignVariable : public Statement {
private:
    VariableProxy* target_;
    //vector<Expression*> indexes_;
    Expression* expr_;

public:

    explicit AssignVariable(VariableProxy* target, Expression* expr)
            : Statement(ASTNodeType::AssignVariable), target_(target), expr_(expr) { }

    ~AssignVariable() override = default;

    PROPERTY_GETTER(target)

    PROPERTY_GETTER(expr)
};

class IFStatement : public Statement {
    Expression *condition_;
    vector<Line*> then_lines_;
    vector<Line*> else_lines_;
public:
    IFStatement(Expression *condition, vector<Line*> then_lines, vector<Line*> else_lines)
            : Statement(ASTNodeType::IFStatement),
              condition_(condition),
              then_lines_(std::move(then_lines)),
              else_lines_(std::move(else_lines)) { }

    ~IFStatement() final {
        delete condition_;
        for (auto line : then_lines_)
            delete line;
        for (auto line : else_lines_)
            delete line;
    }

    bool HasElseStatement() const {
        return !else_lines_.empty();
    }

    PROPERTY_GETTER(condition)

    PROPERTY_GETTER(then_lines)

    PROPERTY_GETTER(else_lines)
};

class WhileStatement : public Statement {
    Expression *condition_;
    vector<Line*> lines_;

public:
    WhileStatement(Expression *condition, vector<Line*> lines) : Statement(ASTNodeType::WhileStatement),
    condition_(std::move(condition)), lines_(std::move(lines)){}

    ~WhileStatement() final{
        delete condition_;
        for(auto line : lines_) {
            delete line;
        }
    }

    PROPERTY_GETTER(condition)

    PROPERTY_GETTER(lines)

};

class GOTOStatement : public Statement {
    int callf_;
    string label_;
public:
    GOTOStatement(string label, int callf) : Statement(ASTNodeType::GOTOStatement), label_(label), callf_(callf) {}

    ~GOTOStatement() final {
    }

    PROPERTY_GETTER(callf)
    PROPERTY_GETTER(label)

};

class PrintStatement : public Statement {
    vector<Expression*> expressions_;

public:
    PrintStatement(vector<Expression*> expressions) : Statement(ASTNodeType::PrintStatement),
    expressions_(std::move(expressions)) {}

    ~PrintStatement() final {
        for(auto expression : expressions_)  delete expression;
    }

    PROPERTY_GETTER(expressions);

};

class EndStatement: public Statement {
public:
    EndStatement(): Statement(ASTNodeType::EndStatement) {}
    ~EndStatement() {}
};

template <class Visitor>
class ASTVisitor {
protected:
    Visitor *impl() {
        return static_cast<Visitor*>(this);
    }
public:
    void visit(ASTNode* node) {
        impl()->visit(node);
    }
};

#define DECLARE_VISIT(type) \
    void Visit##type(type *node);

#define DECLARE_VISIT_METHODS \
    AST_NODE_LIST(DECLARE_VISIT)


#define GENERATE_VISIT_CASE(type) \
    case ASTNodeType::type: \
        return this->impl()->Visit##type(dynamic_cast<type*>(node));

#define GENERATE_AST_VISITOR_SWITCH() \
    switch(node->type()) { \
        AST_NODE_LIST(GENERATE_VISIT_CASE) \
    }

#define DEFINE_AST_VISITOR_SUBCLASS_MEMBERS() \
    void visit(ASTNode *node) { \
        GENERATE_AST_VISITOR_SWITCH() \
    }

#endif //BBC_AST_H