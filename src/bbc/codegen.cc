#include "codegen.h"
#include "utils.h"


void CodeGen::VisitProgram(Program *node) {
    int label=LABEL_ID++;
    int failed=LABEL_ID++;
    int def=LABEL_ID++;
    int i,j;
    stream_ << Utils::FormatString("CALL LABEL%d ; For initialization\n",label);
    stream_ << "\n;================ MAIN PROG ==================\n";
    for(auto line: node->lines()) {
        VisitLine(line);
    }

    //TODO 这里调用waitkey()等待结束
    stream_ << "CALL FINT_WAITKEY\n";
    stream_ << "CAL int ADD rs,0\n";

    stream_<<"EXIT\n";
    //TODO export func
    //TODO DATA
    stream_<<"\n;================ FUNCTIONS ==================\n";

    //TODO 这里手动添加waitkey()
    stream_ << ";(FINT_WAITKEY) Function\n";
    stream_ << ";parcount=0\n";
    stream_ << "FINT_WAITKEY:\n";
    stream_ << "PUSH rb\n";
    stream_ << "LD int rb,rs\n";
    stream_ << "CAL int ADD rs,-4\n";
    stream_ << "; This is a comment line\n";
    stream_ << "OUT 39,0\n";
    stream_ << "LD int [rb],r3\n";
    stream_ << "FINT_WAITKEY_EXIT:\n";
    stream_ << "LD int r3,[rb]\n";
    stream_ << "LD int rs,rb\n";
    stream_ << "POP rb\n";
    stream_ << "RET\n";
    stream_ << "; END FUN FINT_WAITKEY\n";

    stream_<<"\n;================ Init Code ==================\n";
    stream_ << Utils::FormatString("LABEL%d:\n",label);
    for (i=0;i<global.GetCount();i++) {
        if (global.GetType(i)==ES_CSTRING) {
            stream_ << Utils::FormatString("LD dword [%s],CS_%s\n",global.GetName(i).c_str(),global.GetName(i).c_str());
        }	else
        if (global.GetType(i)==ES_VARSTRING) {
            if (global.GetMode(i)==0) {
                stream_ << Utils::FormatString("IN [%s],2\n",global.GetName(i).c_str());
            }	else {
                int k;
                for (k=0;k<global.GetSize(i);k++) {
                    stream_ << Utils::FormatString("LD int r0,%s\n",global.GetName(i).c_str());
                    stream_ << Utils::FormatString("LD int r1,%d\n",k);
                    stream_<<"CAL int MUL r1,4\n";
                    stream_<<"CAL int ADD r0,r1\n";
                    stream_<<"IN [r0],2\n";
                }
            }
        }
    }
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
            case ES_CSTRING:
                j=strings.Index(i);
                stream_<<Utils::FormatString("DATA %s dword 0\n",global.GetName(i).c_str());
                stream_<<Utils::FormatString("DATA CS_%s char \"%s\",0\n",global.GetName(i).c_str(),strings.String(j));
                break;
        }
}

void CodeGen::VisitLine(Line *node) {
    //TODO make label
    string s = node->label();
    if(s != ""){
        //TODO 检测是否定义过
        if (labels.Id((char*)s.c_str())>=0) {
            //iserr<<"Label had already been defined";
        }
        //labels.Add(label.c_str(), node->)
//        if (FunPoint==NULL) label.VarArg("LABEL_%s",s);
//        else label.VarArg("LABEL_%s_%s",FunPoint->name.GetString(),s);
//        Output<<label.GetString()<<":\n";
        string label = Utils::FormatString("LABEL_%s", s.c_str());
        stream_ << label << ":\n";
    }
    visit(node->statement());
}

void CodeGen::VisitVariableDeclaration(VariableDeclaration* node) {

    for(int i = 0; i < node->variables().size(); i++){
        global.RegVar(global.VarName(node->variables()[i]->name, node->variables()[i]->type), node->variables()[i]->type, NULL);
    }
}

void CodeGen::VisitPrintStatement(PrintStatement *node) {
    for(int i = 0; i < node->expressions().size(); i++){
        if(node->expressions()[i]->type() == ASTNodeType::Literal){

        }else{
            visit(node->expressions()[i]);
            stream_<<"POP r3\n";
            //TODO 输出单个字符
            if(node->expressions()[i]->expr_type() == ES_IMMINT) {
                stream_ << "OUT 3,r3\n";
            }
            else if(node->expressions()[i]->expr_type() == ES_IMMFLOAT){
                stream_ << "OUT 5,r3\n";
            }
            else if(node->expressions()[i]->expr_type() == ES_VARSTRING) {
                stream_ << "OUT 2,r3\n";
                stream_ << "IN r3,8\n";
            }
        }
    }
}

void CodeGen::VisitIFStatement(IFStatement* node) {
    long LabelElse=LABEL_ID++;
    long LabelEndif=LABEL_ID++;
    stream_<<"; If code\n";
    visit(node->condition());
    stream_<<"POP r3\n";
    stream_<<"CMP int r3,0\n";
    stream_<<Utils::FormatString("JPC Z LABEL%ld\n", LabelElse);
    for(int i = 0; i < node->then_lines().size(); i++) {
        visit(node->then_lines()[i]);
    }
    stream_<<Utils::FormatString("JMP LABEL%ld\n",LabelEndif);
    stream_<<Utils::FormatString("LABEL%ld:\t; Else\n",LabelElse);
    for(int i = 0; i < node->else_lines().size(); i++) {
        visit(node->else_lines()[i]);
    }

    stream_<<Utils::FormatString("LABEL%ld:\t; End of If\n",LabelEndif);
}

void CodeGen::VisitWhileStatement(WhileStatement *node) {
    long WStart=LABEL_ID++;
    long WEnd=LABEL_ID++;
    stream_<<Utils::FormatString("LABEL%d:\t; While code\n",WStart);
    visit(node->condition());
    stream_<<"POP r3\n";
    stream_<<"CMP int r3,0\n";
    stream_<<Utils::FormatString("JPC Z LABEL%ld\n",WEnd);
    for(int i = 0; i < node->lines().size(); i++) {
        visit(node->lines()[i]);
    }
    stream_<<Utils::FormatString("JMP LABEL%d\n",WStart);
    stream_<<Utils::FormatString("LABEL%d:\t; End of While\n",WEnd);
}

void CodeGen::VisitGOTOStatement(GOTOStatement *node) {
    string s = node->label();
    //TODO 检测是否定义过
    //if(reference.Id((char*)s.c_str()) < 0) reference.Add((char*)s.c_str(), 0);
    string label;
    label = Utils::FormatString("LABEL_%s", s.c_str());
    if(node->callf() == 1){
        stream_ << "CALL " << label << "\n";
    }else{
        stream_ << "JMP " << label << "\n";
    }
}

void CodeGen::VisitAssignVariable(AssignVariable *node) {

    //右边的表达式
    visit(node->expr());
    //lvalue
    //visit(node->target());
    //表达式的结果放在r3
    stream_<<"POP r3\n";
    //getaddr
    //TODO 赋值自动类型转换
    stream_<<Utils::FormatString("LD int r0,%s\n",global.VarName(node->target()->name(), ES_VARINT).c_str());
    stream_<<"LD int [r0],r3\n";
}

//最好的实现是自动执行父类的visit
void CodeGen::VisitExpression(Expression *node) {
    stream_ << ";Expression\n";
}

void CodeGen::VisitUnaryOperation(UnaryOperation* node) {

}

void CodeGen::VisitBinaryOperation(BinaryOperation *node) {
    string opr;
    //TODO 符号校验
    //if(node->op().type_)
    visit(node->left());
    visit(node->right());
    stream_<<"POP r1\n";
    stream_<<"POP r0\n";
    //TODO 类型转换
    //TODO 模除/或/与
    switch(node->op().type_) {
        case TokenType::T_PLUS:
            opr = "ADD"; break;
        case TokenType::T_MINUS:
            opr = "SUB"; break;
        case TokenType::T_MULTIPLY:
            opr = "MUL"; break;
        case TokenType::T_DIVIDE:
            opr = "DIV"; break;
    }
    if(opr != "") {
        //TODO 类型设置
//        switch(type)
//        {
//            case ES_IMMINT:		mode="int"; break;
//            case ES_IMMFLOAT:	mode="float"; break;
        stream_<<"CAL int " << opr << " r0, r1\n";
        stream_<<"PUSH r0\n";
        return ;
    }
    switch(node->op().type_) {
        case TokenType::T_EQ:
            opr = "NZ"; break;
        case TokenType::T_LE:
            opr = "AE"; break;
        case TokenType::T_LEQ:
            opr = "A"; break;
        case TokenType::T_GE:
            opr = "BE"; break;
        case TokenType::T_GEQ:
            opr = "B"; break;
    }
    stream_<<Utils::FormatString("CMP %s r0,r1\n",(node->left()->expr_type()==ES_IMMINT)?"int":"float");
    stream_<<Utils::FormatString("JPC %s LABEL%ld\n",opr.c_str(),LABEL_ID);
    stream_<<Utils::FormatString("PUSH 1\n");
    stream_<<Utils::FormatString("JMP LABEL%ld\n",LABEL_ID+1);
    stream_<<Utils::FormatString("LABEL%ld:\n",LABEL_ID);
    stream_<<Utils::FormatString("PUSH 0\n");
    stream_<<Utils::FormatString("LABEL%ld:\n",LABEL_ID+1);
    LABEL_ID+=2;

    node->SetType(ES_IMMINT);
}

void CodeGen::VisitLiteral(Literal *node) {
    //立即数
    stream_<<Utils::FormatString("PUSH %ld\n", node->value());
    node->SetType(ES_IMMINT);
}

void CodeGen::VisitLiteralString(LiteralString* node){

    //node->SetType();
//    iString s; int sid;
//    iString statics;
//    s=Mident[p]->Text;
//    statics.VarArg("CSTRING_%d",LABEL_ID++);
//    global.regvar(statics.GetString(),ES_CSTRING,NULL);
//    sid=global.GetCount()-1;
//    strings.Add(s.GetString(),sid);				// 增加字串到列表


//    Estack[stacktop].type=ES_VARINT;
//    Estack[stacktop].mode=0;
//    Estack[stacktop].v=sid;
//    Estack[stacktop++].set=0;


//    Estack[stacktop].type=ES_OPERATOR;
//    Estack[stacktop++].v='C';
    int sid;
    string statics;
    statics = Utils::FormatString("CSTRING_%d", LABEL_ID++);
    global.RegVar(statics.c_str(), ES_CSTRING, NULL);
    sid = global.GetCount() - 1;
    strings.Add((char*)node->value().c_str(), sid);				// 增加字串到列表

    //pushv
    stream_ << Utils::FormatString("PUSH [%s]\n", statics.c_str());

//    Output<<"POP r2\n";
//    Output<<"IN r3,2\n";
//    Output<<"IN r2,5\n";
//    Output<<"PUSH r3\n";
//    Astack[ap++].type=ES_VARSTRING;

    stream_ << "POP r2\n";
    stream_ << "IN r3,2\n";
    stream_ << "IN r2,5\n";
    stream_ << "PUSH r3\n";

    node->SetType(ES_VARSTRING);

}

void CodeGen::VisitVariableProxy(VariableProxy *node) {
    //TODO 查找变量失败
    stream_ << Utils::FormatString("PUSH [%s]\n", global.VarName(node->name(), ES_VARINT).c_str());
//    }else{
//        stream_<<"LD int r0,rb\n";
//        //TODO 相对栈底
//        stream_<<Utils::FormatString("CAL int ADD r0,%d\n", node->target()->get_index());
//        stream_<<"PUSH [r0]\n";
//    }
    node->SetType(ES_IMMINT);
}

void CodeGen::VisitEndStatement(EndStatement* node) {
    stream_ << "EXIT\n";
}

string CodeGen::GetStream() {
    return stream_.str();
}