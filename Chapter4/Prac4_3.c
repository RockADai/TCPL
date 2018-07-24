#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/*
编写一个计算器程序，使用逆波兰表示法（所有运算符都跟在操作数后面，如(1-2)*(4+5)输入为12-45+*）
目前的练习中不分割文件，所以代码较长
第四章习题3-11都写在此文件中
*/

/*
4.3：加入取模运算，在getop()中增添负数判断预处理
4.4：增加了几个命令，分别为：打印栈顶元素且不弹出（Ans操作）；复制栈顶元素；交换栈顶两个元素的值；清空栈；
4.5：增加了sin，cos，exp，pow四种数学运算，并为此修改getop()，加入对数学函数的识别预处理
*/

#define MAXVAL 100//栈val的最大深度
#define MAXOP 100//操作数或运算符最大长度
#define NUMBER '0'//标志找到一个数
#define BUFSIZE 100
#define NAME 'n'//标志找到一个小写字母组成的字符串

int getop(char s[]);//获取下一个运算符或操作数
void push(double f);//将f压入栈
double pop();//弹出并返回栈顶值
void clear();//清空
void mathfnc(char s[]);//数学计算

int main()
{
    int type;
    double op1,op2;//临时变量
    char s[MAXOP];
    while((type = getop(s)) != EOF){
        switch(type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop()+pop());
                break;
            case '-':
                op2 = pop();
                push(pop()-op2);//若用pop()-pop()会产生次序问题
                break;
            case '*':
                push(pop()*pop());
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop()/op2);
                else
                    printf("error:zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if(op2 != 0.0)
                    push(fmod(pop(),op2));
                else
                    printf("error:zero divisor\n");
                    break;
            case '\n':
                printf("\t%.8g\n",pop());
                break;
            case 'c':
                clear();
                break;
            case 'd':
                op2 = pop();
                push(op2);
                push(op2);
                break;//复制操作：先将元素弹出，再压入两次
            case 's':
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
                break;//交换
            case '?':
                op2 = pop();
                printf("\t%.8g\n",op2);
                push(op2);
                break;//若直接打印可能造成堆栈或指针变化
            case NAME:
                mathfnc(s);
                break;
            default:
                printf("error:unknown command %s\n",s);
                break;
        }
    }
    return 0;
}

int sp = 0;//下一个空闲栈位置
double val[MAXVAL];//值栈

void push(double f){
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:stack full,can't push %g\n",f);
}

double pop(){
    if(sp > 0)
        return val[--sp];
    else{
        printf("error:stack empty\n");
        return 0.0;
    }
}

int getch();
void ungetch(int c);

int getop(char s[]){
    int i,c;
    while((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    i = 0;
    if(islower(c)){
        while(islower(s[++i] = c = getch()));
        s[i] = '\0';
        if(c != EOF)
            ungetch(c);//读入几个字符，将多于要求的部分压回输入（下同）
        if(strlen(s) > 1)
            return NAME;//字符串长度大于1则可能为数学算法
        else
            return c;//否则可能为指令
    }
    if(!isdigit(c) && c != '.' && c != '-')
        return c;
    if(c == '-')
        if(isdigit(c = getch()) || c == '.')
            s[++i] = c;
        else{
            if(c != EOF)
                ungetch(c);
            return '-';
        }
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()));
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

char buf[BUFSIZE];//输入读取缓冲区
int bufp = 0;
int getch(){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        printf("ungetch:too many characters\n");
    else
        buf[bufp++] = c;//将字符存回输入缓冲区
}

void clear(){
    sp = 0;
}

void mathfnc(char s[]){
    double op2;
    if(strcmp(s,"sin") == 0)
        push(sin(pop()));
    else if(strcmp(s,"cos") == 0)
        push(cos(pop()));
    else if(strcmp(s,"exp") == 0)
        push(exp(pop()));
    else if(strcmp(s,"pow") == 0){
        op2 = pop();
        push(pow(pop(),op2));
    }
    else
        printf("error:%s not supported\n",s);
}

