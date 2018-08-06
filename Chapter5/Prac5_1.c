#include <ctype.h>
#include <stdio.h>

/*
在getint中，若符号+或-后紧跟的不是数字，函数将把符号视为数字0的有效表达方式
修改函数，将+或-重新写回输入流中
*/

#define BUFSIZE 100

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

int getint(int *pn){
    int c,d,sign;
    while(isspace(c = getch()));
    if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-'){
        d = c;//将符号保存到d中
        if(!isdigit(c = getch())){
            if(c != EOF)
                ungetch(c);
            ungetch(d);
            return d;
        }//若下一个字符既不是数也不是EOF，则把该字符放入缓冲区，再把符号放入缓冲区并输出
    }
    for(*pn = 0;isdigit(c);c = getch())
        *pn = 10*(*pn)+(c-'0');
    *pn *= sign;
    if(c != EOF)
        ungetch(c);
    return c;
}