#include <fstream>
#include <iostream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "symbol.h"
#include "ast_dumper.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout<<"bbc filename"<<endl;
        return -1;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail()) {
        cerr << "failed to open file" << endl;;
        return -1;
    }

    Lexer lex(&fin);

//     while(1) {
//         Token t = lex.NextToken();
//         if(t.type_ == TokenType::T_EOF) break;
//         cout << Token::get_type_string(t.type_) << "( " << t.line_ << ", " << t.column_ << "): " << t.lexeme_ << endl;
//     }

    Parser parser(&lex);
    Program* program;
    try {
        program = parser.ParseProgram();
    } catch (CompileException &exception) {
        std::cout << exception.message() << endl;
        return EXIT_FAILURE;
    }

    ASTDumper ast_dumper(std::cout);
    ast_dumper.VisitProgram(program);

    fin.close();

    return 0;
}