#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
编写一个计算器程序，使用逆波兰表示法（所有运算符都跟在操作数后面，如(1-2)*(4+5)输入为12-45+*）
目前的练习中不分割文件，所以代码较长
第四章习题3-11都写在此文件中
*/

#define MAXVAL 100//栈val的最大深度
#define MAXOP 100//操作数或运算符最大长度
#define NUMBER '0'//标志找到一个数
#define BUFSIZE 100

int getop(char s[]);//获取下一个运算符或操作数
void push(double f);//将f压入栈
double pop();//弹出并返回栈顶值

int main()
{
    int type;
    double op2;//临时变量
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

char buf[BUFSIZE];
int bufp = 0;
int getch(){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        printf("ungetch:too many characters\n");
    else
        buf[bufp++] = c;
}