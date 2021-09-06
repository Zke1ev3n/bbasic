#include "codegen.h"
#include "utils.h"


void CodeGen::VisitProgram(Program *node) {
    int label=LABEL_ID++;
    int failed=LABEL_ID++;
    int def=LABEL_ID++;
    int i,j;
    stream_ << Utils::FormatString("CALL LABEL%d ; For initialization\n",label);
    stream_ << "\n;================ MAIN PROG ==================\n";
//    stream_ << ";<Init data ptr>\n";
//    stream_ << "LD dword r2,CD_INITDATA\n";
//    stream_ << "IN r2,22\n";
//    stream_ << ";</Init data ptr>\n";
    for(auto line: node->lines()) {
        VisitLine(line);
    }
    stream_<<"EXIT\n";
    //TODO export func
    //TODO DATA
    stream_<<"\n;================ FUNCTIONS ==================\n";

    stream_<<"\n;================ Init Code ==================\n";
    stream_ << Utils::FormatString("LABEL%d:\n",label);
//    for (i=0;i<global.GetCount();i++) {
//        if (global.GetType(i)==ES_CSTRING) {
//            Output.VarArg("LD dword [%s],CS_%s\n",global.GetName(i),global.GetName(i));
//        }	else
//        if (global.GetType(i)==ES_VARSTRING) {
//            if (global.GetMode(i)==0) {
//                Output.VarArg("IN [%s],2\n",global.GetName(i));
//            }	else {
//                int k;
//                for (k=0;k<global.GetSize(i);k++) {
//                    Output.VarArg("LD int r0,%s\n",global.GetName(i));
//                    Output.VarArg("LD int r1,%d\n",k);
//                    Output<<"CAL int MUL r1,4\n";
//                    Output<<"CAL int ADD r0,r1\n";
//                    Output<<"IN [r0],2\n";
//                }
//            }
//        }
//    }
    stream_<<"RET\n";
    stream_ << Utils::FormatString("LABEL%d:\n",failed);
    stream_<<("EXIT\n");
    stream_<<"\n; Declaration:\n";
    stream_ << Utils::FormatString("LABEL%d:\n",def);
    for (i=0;i<global.GetCount();i++)
        switch (global.GetType(i))
        {
            case ES_VARINT:
            case ES_VARFLOAT:
            case ES_VARSTRING:
                if (global.GetMode(i)==0)
                    stream_<<Utils::FormatString("DATA %s dword 0\n",global.GetName(i).c_str());
                else{
                    stream_<<Utils::FormatString("DATA %s dword 0\n",global.GetName(i).c_str());
                    stream_<<Utils::FormatString(".BLOCK %d 0\n",global.GetSize(i)*4);
                }
                break;
//            case ES_CSTRING:
//                j=strings.Index(i);
//                Output.VarArg("DATA %s dword 0\n",global.GetName(i));
//                Output.VarArg("DATA CS_%s char \"%s\",0\n",global.GetName(i),strings.String(j));
//                break;
        }
//    stream_ << "DATA CD_INITDATA bin %%\n";
}

void CodeGen::VisitLine(Line *node) {
    //TODO make label
    visit(node->statement());
}

void CodeGen::VisitVariableDeclaration(VariableDeclaration* node) {

    for(int i = 0; i < node->variables().size(); i++){
        global.RegVar(global.VarName(node->variables()[i], ES_VARINT), ES_VARINT, NULL);
    }
}

void CodeGen::VisitIFStatement(IFStatement* node) {
    long LabelElse=LABEL_ID++;
    stream_<<"; If code\n";
    visit(node->condition());
    stream_<<"CMP int r3,0\n";
    stream_<<Utils::FormatString("JPC Z LABEL%ld\n", LabelElse);
}

void CodeGen::VisitAssignVariable(AssignVariable *node) {

    //右边的表达式
    visit(node->expr());
    //lvalue
    //visit(node->target());
    //表达式的结果放在r3
    stream_<<"POP r3\n";

    //getaddr
    //TODO 更新
    stream_<<Utils::FormatString("LD int r0,%s\n",global.VarName(node->target()->name(), ES_VARINT).c_str());
    stream_<<"LD int [r0],r3\n";
}

void CodeGen::VisitExpression(Expression *node) {

}

void CodeGen::VisitUnaryOperation(UnaryOperation* node) {

}

void CodeGen::VisitBinaryOperation(BinaryOperation *node) {
    string opr;
    visit(node->left());
    visit(node->right());
    stream_<<"POP r1\n";
    stream_<<"POP r0\n";
    switch(node->op().type_) {
        case TokenType::T_PLUS:
            opr = "ADD"; break;
        case TokenType::T_SUB:
            opr = "SUB"; break;
        case TokenType::T_MULTIPLY:
            opr = "MUL"; break;
        case TokenType::T_DIVIDE:
            opr = "DIV"; break;
    }
    //TODO 支持float和string类型
    stream_<<"CAL int " << opr << " r0, r1\n";
    stream_<<"PUSH r0\n";
}

void CodeGen::VisitLiteral(Literal *node) {
    //立即数
    stream_<<Utils::FormatString("PUSH %ld\n", node->value());
}

void CodeGen::VisitVariableProxy(VariableProxy *node) {
    stream_ << Utils::FormatString("PUSH [%s]\n", global.VarName(node->name(), ES_VARINT).c_str());
//    }else{
//        stream_<<"LD int r0,rb\n";
//        //TODO 相对栈底
//        stream_<<Utils::FormatString("CAL int ADD r0,%d\n", node->target()->get_index());
//        stream_<<"PUSH [r0]\n";
//    }
}

void CodeGen::VisitEndStatement(EndStatement* node) {

}

string CodeGen::GetStream() {
    return stream_.str();
}