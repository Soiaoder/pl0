#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <vector>
#include <string>
#include <sstream>

#define REVERSED_WORD_NUMBER 9  // 关键字个数
#define CHAR_SYMBOL_NUMBER 11   // 算符界符个数
#define MAX_SYM_LENGTH 10       // 关键字最大长度
#define MAX_ID_LENGTH 10        // 标识符最大长度
#define MAX_NUMBER_LENGTH 14    // 整数最大长度

#define LEVEL 3        //最大层数
#define MAX_SYM_NUM 50 // 最多允许符号数
#define MAX_INS 8      // 目标指令数量
#define MAX_ADDR 65535 // 最大地址空间
#define CXMAX 500
#define TXMAX 500

#define STACK_SIZE 1024

std::ifstream fin; // 输入文件流
int line = 1;      // 行数

enum SYM_TYPE
{
    /*自定义变量*/
    NULL_SYM, // 空
    NUM_SYM,  // 整数
    ID_SYM,   // 标识符
    /*关键字*/
    PROGRAM_SYM, //program
    BEGIN_SYM, // begin
    END_SYM,   // end
    CONST_SYM,     // const 
    VAR_SYM,       // var 
    WHILE_SYM, // while
    DO_SYM,    // do
    IF_SYM,    // if
    THEN_SYM,  // then
    /*算符、界符*/
    PLUS_SYM,  // +
    MINUS_SYM, // -
    MUL_SYM,   // *
    DIV_SYM,   // /
    ASSIGNMENT_SYM, // :=
    EQUAL_SYM,      // =
    NOTEQ_SYM,      // <>
    BIG_SYM,        // >
    BIGEQ_SYM,      // >=
    LESS_SYM,       // <
    LESSEQ_SYM,     // <=
    LEFTP_SYM,     // (
    RIGHTP_SYM,    // )
    SEMICOLON_SYM, // ;
    COMMA_SYM,     // ,
};

enum  function {
    jmp,sto
};

enum object {
    constant,
    variable,
    temp,
};

const char* word[REVERSED_WORD_NUMBER + 1] = {
    "",
    "PROGRAM",
    "BEGIN",
    "END",
    "CONST",
    "VAR",
    "WHILE",
    "DO",
    "IF",
    "THEN"
};
int word_sym[REVERSED_WORD_NUMBER + 1] = {
    NULL_SYM,
    PROGRAM_SYM,
    BEGIN_SYM,
    END_SYM,
    CONST_SYM,
    VAR_SYM,
    WHILE_SYM,
    DO_SYM,
    IF_SYM,
    THEN_SYM
};

const char chars[CHAR_SYMBOL_NUMBER + 1] = {
    ' ',
    '+',
    '-',
    '*',
    '/',
    '=',
    '<',
    '>',
    '(',
    ')',
    ';',
    ','
};
int char_sym[CHAR_SYMBOL_NUMBER + 1] = {
    NULL_SYM,
    PLUS_SYM,
    MINUS_SYM,
    MUL_SYM,
    DIV_SYM,
    EQUAL_SYM,
    LESS_SYM,
    BIG_SYM,
    LEFTP_SYM,
    RIGHTP_SYM,
    SEMICOLON_SYM,
    COMMA_SYM
};

char lex_code[CXMAX]; // 存放代码
int code_pos = 0;     // 当前位置
char token[MAX_ID_LENGTH + 1];//读取的单位字符串

char ch;                    // 读到的字符
enum SYM_TYPE sym;          // 词法类型
char id[MAX_ID_LENGTH + 1]; // 标识符的值
int num;                    // 数字的值
int lev = 100;                    // 四地址层数
std::string cur;            //当前值

std::string Quaternion[1000][5];//存放四元式

struct tablestruct {
    std::string name;
    int kind;
    int val;
};

tablestruct table[1000];
int i_table = 0;
tablestruct T[1000];
int i_T = 0;

void getch();
void ungetch();
bool getsym();
void Analyzer();
void Error(int type = -1, const char* str = '\0');
void Prog();
void Block();
void Condecl();
void Const();
void Vardecl();
void Statement();
void Lexp();
void Exp();
void Term();
void Factor();
int Position(int type);
void Enter(enum object kind, std::string name, int val = -1);

//////////////////////////词法分析器///////////////////////////////////////////
void getch()
{
    ch = fin.get();
    lex_code[++code_pos] = ch;

    if (ch == '\n') line++;
    if (ch == EOF) return;
}
void ungetch()
{
    if (ch == '\n') line--;
    code_pos--;
    fin.unget();
}

bool Get()//将类型存放在SYM，如果是标识符则放在id中，如果是整数则放在num中，如果是符号则放在ch中，其中该字符串所在行数放在line里
{
    //预处理
    for (int i = 0; i <= MAX_ID_LENGTH; i++) {//数组初始化为0
        token[i] = '\0';
    }
    do {
        getch();
    } while (ch == ' ' || ch == '\t' || ch == '\n');

    if (ch == EOF) // 文件结束
    {
        sym = NULL_SYM;
        return false;
    }
    else if (isalpha(ch)) // 字母开头是关键字或者标识符
    {
        int k = 0;
        do
        {
            token[k++] = ch;
            getch();
        } while (isalpha(ch) || isdigit(ch));
        ungetch();//回退一个字符

        if (k > MAX_ID_LENGTH) Error(0);//超过标识符长度

        // 判断是否是关键字
        strcpy_s(id, token);//转为字符串
        word[0] = id;
        int i = REVERSED_WORD_NUMBER;

        while (strcmp(id, word[i])) i--;
        if (i)
        {
            sym = static_cast<SYM_TYPE>(word_sym[i]); // 是关键字
            std::cout << "关键字 <line " << line << ", '" << word[i] << "'>\n";
        }
        else
        {
            sym = ID_SYM; // 是标识符
            std::cout << "标识符 <line " << line << ", '" << id << "'>\n";
        }
    }
    else if (isdigit(ch)) // 数字开头
    {
        num = 0;
        sym = NUM_SYM;
        int k = 0;
        do {
            num = num * 10 + ch - '0';
            k++;
            getch();
        } while (isdigit(ch));
        ungetch();//回退一个字符

        std::cout << "整数 <line " << line << ", " << num << ">\n";

        if (k > MAX_NUMBER_LENGTH) Error(0);//超过整数长度
    }
    else if (ch == ':')
    {
        getch();
        if (ch == '=')
        {
            sym = ASSIGNMENT_SYM;
            std::cout << "运算符 <line " << line << ", ':='>\n";
        }
        else
        {
            Error(0);//非法赋值运算符
            ungetch();
        }
    }
    else if (ch == '<')
    {
        getch();
        if (ch == '=')
        {
            sym = LESSEQ_SYM;
            std::cout << "运算符 <line " << line << ", '<='>\n";
        }
        else if (ch == '>')
        {
            sym = NOTEQ_SYM;
            std::cout << "运算符 <line " << line << ", '<>'>\n";
        }
        else
        {
            sym = LESS_SYM;
            std::cout << "运算符 <line " << line << ", '<'>\n";
            ungetch();
        }
    }
    else if (ch == '>')
    {
        getch();
        if (ch == '=')
        {
            sym = BIGEQ_SYM;
            std::cout << "运算符 <line " << line << ", '>='>\n";
        }
        else
        {
            sym = BIG_SYM;
            std::cout << "运算符 <line " << line << ", '>'>\n";
            ungetch();
        }
    }
    else if (ch == '=')
    {
        sym = EQUAL_SYM;
        std::cout << "运算符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '+')
    {
        sym = PLUS_SYM;
        std::cout << "运算符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '-')
    {
        sym = MINUS_SYM;
        std::cout << "运算符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '*')
    {
        sym = MUL_SYM;
        std::cout << "运算符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '/')
    {
        sym = DIV_SYM;
        std::cout << "运算符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '(')
    {
        sym = LEFTP_SYM;
        std::cout << "界符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ')')
    {
        sym = RIGHTP_SYM;
        std::cout << "界符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ',')
    {
        sym = COMMA_SYM;
        std::cout << "界符 <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ';')
    {
        sym = SEMICOLON_SYM;
        std::cout << "界符 <line " << line << ", '" << ch << "'>\n";
    }

    return true;
}

//////////////////////////词法分析器///////////////////////////////////////////
///////////////////////////////输出报错内容/////////////////////////////
void Error(int type, const char* str)
{
    if (type < 10)	//running error不输出 
        std::cout << "第" << line << "行      ";
    switch (type)
    {
    case 0:
        std::cout << "[Lexical Error] illegal character " << token << "" << std::endl;
        break;
    case 1:
        std::cout << "[Syntax  Error] expected initializer before " << token << std::endl;
        break;
    case 2:
        std::cout << "[Syntax  Error] expected " << str << " before " << token << std::endl;
        break;
    case 3:
        std::cout << "[Lexical  Error] missing " << str << " before " << token << std::endl;
        break;
    case 4:
        std::cout << "[Syntax Error] redundant" << std::endl;
        break;
    case 5:
        std::cout << "[Semantic Error] Undefined " << token << std::endl;
        break;
    case 6:
        std::cout << "[Semantic Error] Error type" << std::endl;
        break;
    case 7:
        std::cout << "[Semantic Error] redeclaration of " << token << std::endl;
        break;
    case 8:
        std::cout << "[Syntax Error] unknown error" << std::endl;
        break;
    case 9:
        std::cout << "[Semantic Error] parameter mismatch" << std::endl;
        break;
    case 10:
        std::cout << "[Running Error] stack overflows" << std::endl;
        break;
    case 11:
        std::cout << "[Running Error] division error" << std::endl;
        break;
    }
}
///////////////////////////////输出报错内容/////////////////////////////
//////////////////////////语法分析和中间代码生成////////////////////////////////
//<prog> →PROGRAM<id><block>
void Prog()
{
	//看PROGRAM
    Get();//获取字符串
    if (sym != PROGRAM_SYM)
    {
        Error(2, "PROGRAM");
    }
    //看<id>
    Get();//获取字符串
    if (sym != ID_SYM)
    {
        Error(2, "<id>");
    }
    //看<block>
    Block();

}

/*
lev :层数
  */
//<block> → [<condecl>][<vardecl>]<statement>
void Block()
{
    Get();
    //看[<condecl>]
    Condecl();
    //看[<condecl>]
    Vardecl();
    //看<Statement>
    Statement();
}

//<condecl> → const <const>{,<const>};
void Condecl()
{
    if (sym == CONST_SYM)
    {
        //看<const>
        Get();
        Const();
        //看COMMA_SYM,从而判断{,<const>}
        Get();
        while (sym == COMMA_SYM)
        {
            Get();
            Const();
            Get();
        }
        //看SEMICOLON_SYM,判断常量定义是否结束
        if (sym == SEMICOLON_SYM)
        {
            Get();
        }
        else
        {
            Error(2, ";");
        }
    }
}


//<const> → <id>:=<integer>
void Const()
{
	//看<id>
    if (sym == ID_SYM)
    {
        Quaternion[lev][3] = id;
        Get();
        //看<integer>
        if (sym == ASSIGNMENT_SYM)
        {
            Quaternion[lev][0] = ":=";
            Get();
            if (sym != NUM_SYM)
            {
                Error(1);
                //tx--;//占时不知道作用
            }
            else
            {
                Quaternion[lev][1] = num;
                Quaternion[lev][2] = "-";
                Enter(constant, id, num);
            }
        }
        lev++;
    }
    else
    {
        Error();
    }
}


//<vardecl> → VAR<id>{,<id>};
void Vardecl()
{
    //看VAR
    if (sym == VAR_SYM)	//var
    {
        //看<id>
        Get();
        if (sym == ID_SYM)
        {
            Enter(variable, id);
            Get();
            while (sym == COMMA_SYM)	//,
            {
                Get();
                if (sym != ID_SYM)	//<id>
                {
                    Error(1);
                    break;
                }
                else
                {
                    Enter(variable, id);
                }
                Get();
            }
            if (sym == SEMICOLON_SYM)	//;
            {
                Get();
            }
        }
        else
        {
            Error(1);
        }
    }
}


/*
<statement> → <id> := <exp>
|IF <lexp> THEN <statement>
|WHILE <lexp> DO <statement>
|BEGIN <statement>{; <statement>} END
|空
*/
void Statement()
{
    std::string QT[5];//临时存放四元式
    if (sym == ID_SYM) //如果是赋值语句
    {
        //看:=
        QT[3] = id;
        Get();
        if (sym == ASSIGNMENT_SYM)	//:=
        {
            QT[0] = ":=";
            QT[2] = "-";
            //看<exp>
            Get();
            Exp();
            QT[1] = cur;
            Quaternion[lev][1] = QT[1];
            Quaternion[lev][2] = QT[2];
            Quaternion[lev][3] = QT[3];
            Quaternion[lev][0] = QT[0];
            lev++;
        }
        else
        {
            Error(1);
        }
    }
    else if (sym == IF_SYM) //如果是条件语句
    {
        //看<Lexp>
        Get();
        Lexp();
        //看then
        if (sym == THEN_SYM)	//then
            Get();
        else
            Error(2, "then");
        //看<statement>
        int current = lev;
        lev++;
        Statement();
        Quaternion[current][0] = "j";
        Quaternion[current][1] = "-";
        Quaternion[current][2] = "-";
        Quaternion[current][3] = std::to_string(lev);
    }
    else if (sym == WHILE_SYM)   //如果是循环语句
    {
        int from = lev;
        //看<lexp>
        Get();
        Lexp();
        //看DO
        if (sym == DO_SYM)	//do
            Get();
        else
            Error(2, "do");
        //看statement
        int current = lev;
        Quaternion[current][0] = "j";
        Quaternion[current][1] = "-";
        Quaternion[current][2] = "-";
        lev++;
        Statement();
        Quaternion[lev][0] = "j";
        Quaternion[lev][1] = "-";
        Quaternion[lev][2] = "-";
        Quaternion[lev][3] = std::to_string(from);
        lev++;
        Quaternion[current][3] = std::to_string(lev);
    }
    else if (sym == BEGIN_SYM)     //<复合语句>→BEGIN <语句>{; <语句>} END
    {
        Get();
        Statement();
        //看；分号
        while (sym == SEMICOLON_SYM)
        {
            Get();
            Statement();
        }
        //看END
        if (sym == END_SYM)
        {
            Get();
        }
        else
        {
            Error(2, "END");
        }
    }
    else //空语句
    {
        //无为而治
    }
}
//<lexp> → <exp> <lop> <exp>
void Lexp()
{
    enum SYM_TYPE lop;
    std::string QT[5];//临时存放四元式
	//看<exp>
    Exp();
    //看符号
    if (sym == EQUAL_SYM|| sym == NOTEQ_SYM || sym == BIG_SYM || sym == BIGEQ_SYM || sym == LESS_SYM || sym == LESSEQ_SYM)	//<lop>
    {
        lop = sym;
        Get();
    }
    else
        Error(2, "<lop>");
    //看<exp>
    QT[1] = cur;
    Exp();
    QT[2] = cur;
    if (lop == EQUAL_SYM)
    {
        QT[0] = "j=";
    }
    else if (lop == NOTEQ_SYM)
    {
        QT[0] = "j<>";
    }
    else if (lop == BIG_SYM)
    {
        QT[0] = "j>";
    }
    else if (lop == BIGEQ_SYM)
    {
        QT[0] = "j>=";
    }
    else if (lop == LESS_SYM)
    {
        QT[0] = "j<";
    }
    else if (lop == LESSEQ_SYM)
    {
        QT[0] = "j<=";
    }

    Quaternion[lev][1] = QT[1];
    Quaternion[lev][2] = QT[2];
    Quaternion[lev][3] = std::to_string(lev+2);
    Quaternion[lev][0] = QT[0];
    lev++;
}

//<exp> → [+|-]<term>{<aop><term>}
void Exp()
{
    enum SYM_TYPE aop = PLUS_SYM;
    //看加法运算符
    if (sym == PLUS_SYM || sym == MINUS_SYM)	// + | -
    {
        aop = sym;
        Get();
    }
    //看<term>
    Term();
    if (aop == MINUS_SYM)
    {
        Quaternion[lev][0] = "uminus";
        Quaternion[lev][1] = cur;
        Quaternion[lev][2] = "-";
        std::string name = "T" + std::to_string(i_T + 1);
        Enter(temp, name);
        Quaternion[lev][3] = name;
        cur = name;
        lev++;
    }
    //看加法运算符
    while (sym == PLUS_SYM || sym == MINUS_SYM) // + | -
    {
        std::string QT[5];//临时存放四元式
        aop = sym;
        QT[1] = cur;
        Get();
        Term();
        if (aop == PLUS_SYM)
        {
            QT[0] = "+";
            QT[2] = cur;
            std::string name = "T" + std::to_string(i_T + 1);
            Enter(temp, name);
            QT[3] = name;
            cur = name;
            Quaternion[lev][1] = QT[1];
            Quaternion[lev][2] = QT[2];
            Quaternion[lev][3] = QT[3];
            Quaternion[lev][0] = QT[0];
            lev++;
        }
        else if (aop == MINUS_SYM)
        {
            QT[0] = "-";
            QT[2] = cur;
            std::string name = "T" + std::to_string(i_T + 1);
            Enter(temp, name);
            QT[3] = name;
            cur = name;
            Quaternion[lev][1] = QT[1];
            Quaternion[lev][2] = QT[2];
            Quaternion[lev][3] = QT[3];
            Quaternion[lev][0] = QT[0];
            lev++;
        }
    }
}


//<term> → <factor>{<mop><factor>}
void Term()
{
    enum SYM_TYPE mop;
    //看<facotr>
    Factor();
    //看乘法运算符
    while (sym == MUL_SYM || sym == DIV_SYM)	// * | / 
    {
        std::string QT[5];//临时存放四元式
        int current = lev;
        QT[1] = cur;
        mop = sym;
        Get();
        Factor();
        QT[2] = cur;
        if (mop == MUL_SYM)
        {
            QT[0] = "*";
        }
        else if (mop == DIV_SYM)
        {
            QT[0] = "/";
        }
        std::string name = "T" + std::to_string(i_T + 1);
        Enter(temp, name);
        QT[3] = name;
        Quaternion[lev][1] = QT[1];
        Quaternion[lev][2] = QT[2];
        Quaternion[lev][3] = QT[3];
        Quaternion[lev][0] = QT[0];
        cur = name;
        lev++;
    }
}

//<factor>→<id>|<integer>|(<exp>)
void Factor()
{
    int i;
    //看<id>
    if (sym == ID_SYM)	//<id>
    {
        /*
        i = Position(1);
        if (i == -1)
        Error(5);
        */
        cur = id;
        Get();
    }
    else if (sym == NUM_SYM)  // <integer>
    {
        cur = std::to_string(num);
        Get();
    }
    else if (sym == LEFTP_SYM)	//(
    {
        //看<exp>
        Get();
        Exp();
        Get();
        if (sym == RIGHTP_SYM)		//)
            Get();
        else
            Error(2, ")");
    }
    else
        Error(1);
}

void Enter(enum object kind, std::string name,int val)
{
    if (kind == constant)
    {
        table[i_table].kind = kind;
        table[i_table].name = name;
        table[i_table].val = val;
        i_table++;
    }
    if (kind == variable)
    {
        table[i_table].kind = kind;
        table[i_table].name = name;
        table[i_table].val = val;
        i_table++;
    }
    if (kind == temp)
    {
        T[i_T].kind = kind;
        T[i_T].name = name;
        T[i_T].val = val;
        i_T++;
    }
}

int Position(int type)
{
    int i;
    std::cout << i_table << std::endl;
    for (i = i_table - 1; i >= 0; i--)
    {
        std:: cout<<i<<" "<< table[i_table].name <<"我名字呢"<< std::endl;
        if (table[i_table].name == id)
        {
            return i;
        }
    }
    return i;
}
//////////////////////////语法分析和中间代码生成////////////////////////////////
std::string Trace(int i)
{
    std::istringstream ss(Quaternion[i][3]);
    ss >> num;
    if (Quaternion[num][0] == "j")
    {
        Quaternion[i][3] = Trace(num);
    }
    return Quaternion[i][3];
}
void Back(int i)
{
    for (; i <= lev - 1; i++)
    {
        if (Quaternion[i][0] == "j")
        {
            std::istringstream ss(Quaternion[i][3]);
            ss >> num;
            if (Quaternion[num][0] == "j")
            {
                Quaternion[i][3] = Trace(num);
            }
        }
    }
}
void Out()
{
    for (int i = 100; i <= lev-1; i++)
    {
        std::cout <<i<< "(" << Quaternion[i][0] << "," << Quaternion[i][1] << "," << Quaternion[i][2] << "," << Quaternion[i][3] << ")" << std::endl;
    }
}
void Analyzer()
{
    Prog();//采用自上而下的方法，从Prog开始，并在程序中调用词法分析器，同时生成中间代码
    Back(100);
    Out();
}
int main() {
    fin.open("pl0.txt", std::ios::in);//读取文件
    Analyzer();//开始分析程序并生成中间代码
    return 0;
}





