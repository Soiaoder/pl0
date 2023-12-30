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

#define REVERSED_WORD_NUMBER 9  // �ؼ��ָ���
#define CHAR_SYMBOL_NUMBER 11   // ����������
#define MAX_SYM_LENGTH 10       // �ؼ�����󳤶�
#define MAX_ID_LENGTH 10        // ��ʶ����󳤶�
#define MAX_NUMBER_LENGTH 14    // ������󳤶�

#define LEVEL 3        //������
#define MAX_SYM_NUM 50 // ������������
#define MAX_INS 8      // Ŀ��ָ������
#define MAX_ADDR 65535 // ����ַ�ռ�
#define CXMAX 500
#define TXMAX 500

#define STACK_SIZE 1024

std::ifstream fin; // �����ļ���
int line = 1;      // ����

enum SYM_TYPE
{
    /*�Զ������*/
    NULL_SYM, // ��
    NUM_SYM,  // ����
    ID_SYM,   // ��ʶ��
    /*�ؼ���*/
    PROGRAM_SYM, //program
    BEGIN_SYM, // begin
    END_SYM,   // end
    CONST_SYM,     // const 
    VAR_SYM,       // var 
    WHILE_SYM, // while
    DO_SYM,    // do
    IF_SYM,    // if
    THEN_SYM,  // then
    /*��������*/
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

char lex_code[CXMAX]; // ��Ŵ���
int code_pos = 0;     // ��ǰλ��
char token[MAX_ID_LENGTH + 1];//��ȡ�ĵ�λ�ַ���

char ch;                    // �������ַ�
enum SYM_TYPE sym;          // �ʷ�����
char id[MAX_ID_LENGTH + 1]; // ��ʶ����ֵ
int num;                    // ���ֵ�ֵ
int lev = 100;                    // �ĵ�ַ����
std::string cur;            //��ǰֵ

std::string Quaternion[1000][5];//�����Ԫʽ

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

//////////////////////////�ʷ�������///////////////////////////////////////////
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

bool Get()//�����ʹ����SYM������Ǳ�ʶ�������id�У���������������num�У�����Ƿ��������ch�У����и��ַ���������������line��
{
    //Ԥ����
    for (int i = 0; i <= MAX_ID_LENGTH; i++) {//�����ʼ��Ϊ0
        token[i] = '\0';
    }
    do {
        getch();
    } while (ch == ' ' || ch == '\t' || ch == '\n');

    if (ch == EOF) // �ļ�����
    {
        sym = NULL_SYM;
        return false;
    }
    else if (isalpha(ch)) // ��ĸ��ͷ�ǹؼ��ֻ��߱�ʶ��
    {
        int k = 0;
        do
        {
            token[k++] = ch;
            getch();
        } while (isalpha(ch) || isdigit(ch));
        ungetch();//����һ���ַ�

        if (k > MAX_ID_LENGTH) Error(0);//������ʶ������

        // �ж��Ƿ��ǹؼ���
        strcpy_s(id, token);//תΪ�ַ���
        word[0] = id;
        int i = REVERSED_WORD_NUMBER;

        while (strcmp(id, word[i])) i--;
        if (i)
        {
            sym = static_cast<SYM_TYPE>(word_sym[i]); // �ǹؼ���
            std::cout << "�ؼ��� <line " << line << ", '" << word[i] << "'>\n";
        }
        else
        {
            sym = ID_SYM; // �Ǳ�ʶ��
            std::cout << "��ʶ�� <line " << line << ", '" << id << "'>\n";
        }
    }
    else if (isdigit(ch)) // ���ֿ�ͷ
    {
        num = 0;
        sym = NUM_SYM;
        int k = 0;
        do {
            num = num * 10 + ch - '0';
            k++;
            getch();
        } while (isdigit(ch));
        ungetch();//����һ���ַ�

        std::cout << "���� <line " << line << ", " << num << ">\n";

        if (k > MAX_NUMBER_LENGTH) Error(0);//������������
    }
    else if (ch == ':')
    {
        getch();
        if (ch == '=')
        {
            sym = ASSIGNMENT_SYM;
            std::cout << "����� <line " << line << ", ':='>\n";
        }
        else
        {
            Error(0);//�Ƿ���ֵ�����
            ungetch();
        }
    }
    else if (ch == '<')
    {
        getch();
        if (ch == '=')
        {
            sym = LESSEQ_SYM;
            std::cout << "����� <line " << line << ", '<='>\n";
        }
        else if (ch == '>')
        {
            sym = NOTEQ_SYM;
            std::cout << "����� <line " << line << ", '<>'>\n";
        }
        else
        {
            sym = LESS_SYM;
            std::cout << "����� <line " << line << ", '<'>\n";
            ungetch();
        }
    }
    else if (ch == '>')
    {
        getch();
        if (ch == '=')
        {
            sym = BIGEQ_SYM;
            std::cout << "����� <line " << line << ", '>='>\n";
        }
        else
        {
            sym = BIG_SYM;
            std::cout << "����� <line " << line << ", '>'>\n";
            ungetch();
        }
    }
    else if (ch == '=')
    {
        sym = EQUAL_SYM;
        std::cout << "����� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '+')
    {
        sym = PLUS_SYM;
        std::cout << "����� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '-')
    {
        sym = MINUS_SYM;
        std::cout << "����� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '*')
    {
        sym = MUL_SYM;
        std::cout << "����� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '/')
    {
        sym = DIV_SYM;
        std::cout << "����� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == '(')
    {
        sym = LEFTP_SYM;
        std::cout << "��� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ')')
    {
        sym = RIGHTP_SYM;
        std::cout << "��� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ',')
    {
        sym = COMMA_SYM;
        std::cout << "��� <line " << line << ", '" << ch << "'>\n";
    }
    else if (ch == ';')
    {
        sym = SEMICOLON_SYM;
        std::cout << "��� <line " << line << ", '" << ch << "'>\n";
    }

    return true;
}

//////////////////////////�ʷ�������///////////////////////////////////////////
///////////////////////////////�����������/////////////////////////////
void Error(int type, const char* str)
{
    if (type < 10)	//running error����� 
        std::cout << "��" << line << "��      ";
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
///////////////////////////////�����������/////////////////////////////
//////////////////////////�﷨�������м��������////////////////////////////////
//<prog> ��PROGRAM<id><block>
void Prog()
{
	//��PROGRAM
    Get();//��ȡ�ַ���
    if (sym != PROGRAM_SYM)
    {
        Error(2, "PROGRAM");
    }
    //��<id>
    Get();//��ȡ�ַ���
    if (sym != ID_SYM)
    {
        Error(2, "<id>");
    }
    //��<block>
    Block();

}

/*
lev :����
  */
//<block> �� [<condecl>][<vardecl>]<statement>
void Block()
{
    Get();
    //��[<condecl>]
    Condecl();
    //��[<condecl>]
    Vardecl();
    //��<Statement>
    Statement();
}

//<condecl> �� const <const>{,<const>};
void Condecl()
{
    if (sym == CONST_SYM)
    {
        //��<const>
        Get();
        Const();
        //��COMMA_SYM,�Ӷ��ж�{,<const>}
        Get();
        while (sym == COMMA_SYM)
        {
            Get();
            Const();
            Get();
        }
        //��SEMICOLON_SYM,�жϳ��������Ƿ����
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


//<const> �� <id>:=<integer>
void Const()
{
	//��<id>
    if (sym == ID_SYM)
    {
        Quaternion[lev][3] = id;
        Get();
        //��<integer>
        if (sym == ASSIGNMENT_SYM)
        {
            Quaternion[lev][0] = ":=";
            Get();
            if (sym != NUM_SYM)
            {
                Error(1);
                //tx--;//ռʱ��֪������
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


//<vardecl> �� VAR<id>{,<id>};
void Vardecl()
{
    //��VAR
    if (sym == VAR_SYM)	//var
    {
        //��<id>
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
<statement> �� <id> := <exp>
|IF <lexp> THEN <statement>
|WHILE <lexp> DO <statement>
|BEGIN <statement>{; <statement>} END
|��
*/
void Statement()
{
    std::string QT[5];//��ʱ�����Ԫʽ
    if (sym == ID_SYM) //����Ǹ�ֵ���
    {
        //��:=
        QT[3] = id;
        Get();
        if (sym == ASSIGNMENT_SYM)	//:=
        {
            QT[0] = ":=";
            QT[2] = "-";
            //��<exp>
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
    else if (sym == IF_SYM) //������������
    {
        //��<Lexp>
        Get();
        Lexp();
        //��then
        if (sym == THEN_SYM)	//then
            Get();
        else
            Error(2, "then");
        //��<statement>
        int current = lev;
        lev++;
        Statement();
        Quaternion[current][0] = "j";
        Quaternion[current][1] = "-";
        Quaternion[current][2] = "-";
        Quaternion[current][3] = std::to_string(lev);
    }
    else if (sym == WHILE_SYM)   //�����ѭ�����
    {
        int from = lev;
        //��<lexp>
        Get();
        Lexp();
        //��DO
        if (sym == DO_SYM)	//do
            Get();
        else
            Error(2, "do");
        //��statement
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
    else if (sym == BEGIN_SYM)     //<�������>��BEGIN <���>{; <���>} END
    {
        Get();
        Statement();
        //�����ֺ�
        while (sym == SEMICOLON_SYM)
        {
            Get();
            Statement();
        }
        //��END
        if (sym == END_SYM)
        {
            Get();
        }
        else
        {
            Error(2, "END");
        }
    }
    else //�����
    {
        //��Ϊ����
    }
}
//<lexp> �� <exp> <lop> <exp>
void Lexp()
{
    enum SYM_TYPE lop;
    std::string QT[5];//��ʱ�����Ԫʽ
	//��<exp>
    Exp();
    //������
    if (sym == EQUAL_SYM|| sym == NOTEQ_SYM || sym == BIG_SYM || sym == BIGEQ_SYM || sym == LESS_SYM || sym == LESSEQ_SYM)	//<lop>
    {
        lop = sym;
        Get();
    }
    else
        Error(2, "<lop>");
    //��<exp>
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

//<exp> �� [+|-]<term>{<aop><term>}
void Exp()
{
    enum SYM_TYPE aop = PLUS_SYM;
    //���ӷ������
    if (sym == PLUS_SYM || sym == MINUS_SYM)	// + | -
    {
        aop = sym;
        Get();
    }
    //��<term>
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
    //���ӷ������
    while (sym == PLUS_SYM || sym == MINUS_SYM) // + | -
    {
        std::string QT[5];//��ʱ�����Ԫʽ
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


//<term> �� <factor>{<mop><factor>}
void Term()
{
    enum SYM_TYPE mop;
    //��<facotr>
    Factor();
    //���˷������
    while (sym == MUL_SYM || sym == DIV_SYM)	// * | / 
    {
        std::string QT[5];//��ʱ�����Ԫʽ
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

//<factor>��<id>|<integer>|(<exp>)
void Factor()
{
    int i;
    //��<id>
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
        //��<exp>
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
        std:: cout<<i<<" "<< table[i_table].name <<"��������"<< std::endl;
        if (table[i_table].name == id)
        {
            return i;
        }
    }
    return i;
}
//////////////////////////�﷨�������м��������////////////////////////////////
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
    Prog();//�������϶��µķ�������Prog��ʼ�����ڳ����е��ôʷ���������ͬʱ�����м����
    Back(100);
    Out();
}
int main() {
    fin.open("pl0.txt", std::ios::in);//��ȡ�ļ�
    Analyzer();//��ʼ�������������м����
    return 0;
}





