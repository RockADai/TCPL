#include <stdio.h>
#include <ctype.h>
#include <math.h>

/*
编写程序expr，以计算从命令行输入的逆波兰表达式的值，每个运算符或操作数用一个单独的参数表示
*/

#define MAXOP 100//操作数或运算符最大长度
#define NUMBER '0'//标志找到一个数

int getop(char s[]);
void ungets(char s[]);
void push(double f);
double pop();

int main(int argc, char const *argv[])
{
    char s[MAXOP];
    double op2;
    while(--argc > 0){//判断是否还有参数
        ungets(" ");//将一个空格（标记参数结束）压入输入缓冲区
        ungets(*++argv);//压入一个参数
        switch(getop(s)){
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
            default:
                printf("error:unknown command %s\n",s);
                argc = 1;//若参数错误则argc置1
                break;
        }
    }
    printf("\t%.8g\n",pop());
    return 0;
}


int getch();
void ungetch(int c);

int getop(char s[]){
    int i,c;
    while((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if(!isdigit(c) && c != '.')
        return c;
    i = 0;
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()));
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

int buf[100];//输入读取缓冲区
int bufp = 0;
int getch(){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= 100)
        printf("ungetch:too many characters\n");
    else
        buf[bufp++] = c;//将字符存回输入缓冲区
}

void ungets(char s[]){
    int len = strlen(s);
    while(len > 0)//执行ungetch操作，次数为字符串s的字符个数
        ungetch(s[--len]);//先减1去掉\0
}

int sp = 0;//下一个空闲栈位置
double val[100];//值栈

void push(double f){
    if(sp < 100)
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
