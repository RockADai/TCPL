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
4.6：增加处理变量的命令，增加一个变量存放最近打印的值
4.7：编写函数ungets(s)，将整个字符串s压回到输入中（它需要使用buf和bufp吗？它能否仅使用ungetch函数？）
4.8：若最多只压回一个字符，修改getch和ungetch
4.9：以上的getch和ungetch不能正确处理压回的EOF，应如何修正？
4.10：另一种方法是通过getline函数读入整个输入行，这种情况下可以不使用getch和ungetch函数，运用这一方法修改程序
4.11：修改getop函数，使其不必使用ungetch函数。（可以使用一个静态内部变量解决该问题）
*/

#define MAXVAL 100//栈val的最大深度
#define MAXOP 100//操作数或运算符最大长度
#define NUMBER '0'//标志找到一个数
#define BUFSIZE 100
#define NAME 'n'//标志找到一个小写字母组成的字符串

int getop(char s[]);//获取下一个运算符或操作数
void push(double f);//将f压入栈
double pop();//弹出并返回栈顶值
int getch();
void ungetch(int c);
void clear();//清空
void mathfnc(char s[]);//数学计算
void ungets(char s[]);//压回字符串，不直接操作buf和bufp，该操作和出错检查由ungetch()处理

int main()
{
    int i,type,var = 0;
    double op1,op2,v;//临时变量，v存放最近打印的值
    char s[MAXOP];
    double variable[26];
    for(i = 0;i < 26;i++)
        variable[i] = 0.0;
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
            case '=':
                pop();
                if(var >= 'A' && var <= 'Z')
                    variable[var-'A'] = pop();
                else
                    printf("error:no variable name\n");
                break;//赋值操作
            case NAME:
                mathfnc(s);
                break;
            default:
                if(type >= 'A' && type <= 'Z')
                    push(variable[type-'A']);
                else if(type == 'v')
                    push(v);
                else
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

int buf[BUFSIZE];//输入读取缓冲区
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

void ungets(char s[]){
    int len = strlen(s);
    while(len > 0)//执行ungetch操作，次数为字符串s的字符个数
        ungetch(s[--len]);//先减1去掉\0
}

/*
题4.8：
char buf = 0;
int getch(){
    int c;
    if(buf != 0)
        c = buf;
    else
        c = getchar();
    buf = 0;
    return c;
}
void ungetch(int c){
    if(buf != 0)
        printf("ungetch:too many characters\n");
    else
        buf = c;
}
*/

/*
题4.9：
int buf[BUFSIZE];//将缓冲区声明为int型
*/

/*
题4.10：
int getline(char line[],int lim){
    int c,i,j=0;
    for(i=0;(c=getchar())!=EOF&&c!='\n';++i)
        if(i<lim-2){
            line[j]=c;
            ++j;
        }//字符数未超限
    if(c=='\n'){
        line[j]=c;
        ++i;
        ++j;
    }
    line[j]='\0';
    return i;
}
#define MAXLINE 100
int li = 0;
char line[MAXLINE];
int getop(char s[]){
    int c,i;
    if(line[li] == '\0')
        if(getline(line,MAXLINE) == 0)
            return EOF;
        else
            li = 0;
    while((s[0] = c = line[li++]) == ' ' || c == '\t');
    s[1] = '\0';
    if(!isdigit(c) && c != '.')
        return c;
    i = 0;
    if(isdigit(c))
        while(isdigit(s[++i] = c = line[li++]));
    if(c == '.')
        while(isdigit(s[++i] = c = line[li++]));
    s[i] = '\0';
    li--;
    return NUMBER;
}
*/

/*
题4.11：
int getop(char s[]){
    int c,i;
    static int lastc = 0;
    if(lastc == 0)
        c = getch();
    else{
        c = lastc;
        lastc = 0;
    }
    while((s[0] = c) == ' ' || c == '\t')
        c = getch();
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
        lastc = c;
    return NUMBER;
}
*/
