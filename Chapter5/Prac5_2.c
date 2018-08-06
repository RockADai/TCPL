#include <ctype.h>
#include <stdio.h>

/*
模仿getint编写getfloat。getfloat的返回值应该是什么类型？
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

int getfloat(float *pn){
    int c,sign,power;
    while(isspace(c = getch()));
    if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-')
        c = getch();
    for(*pn = 0.0;isdigit(c);c = getch())
        *pn = 10.0*(*pn)+(c-'0');
    if(c == '.')
        c = getch();
    for(*pn = 0.0;isdigit(c);c = getch()){
        *pn = 10.0*(*pn)+(c-'0');
        power *= 10;
    }//小数点后每出现一位则lg(*pn)+1
    *pn *= sign/power*1.0;//先将小数点后的位数从右侧填入*pn，再除以指数得到结果
    if(c != EOF)
        ungetch(c);
    return c; 
}