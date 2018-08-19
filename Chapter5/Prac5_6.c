#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
采用指针而非数组索引方式改写某些程序，例如getline，atoi、itoa及其变体，reverse，strindex，getop等
*/
int getline(char *s,int lim){
    int c;
    char *t = s;//记录初始地址
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if(c == '\n')
        *s++ = c;
    *s = '\0';
    return s-t;
}

int atoi(char *s){
    int n,sign;
    for(;isspace(*s);s++);
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
        s++;
    for(n = 0;isdigit(*s);s++)
        n = 10*n+*s-'0';
    return sign*n;
}

void reverse(char *s){
    int c;
    char *t;
    for(t = s+(strlen(s)-1);s < t;s++,t--){
        c = *s;
        *s = *t;
        *t = c;
    }
}//s++与数组索引版本中i++等价，*s++与s[i++]等价

void itoa(char *s,int n){
    int sign;
    char *t = s;
    if((sign = n) < 0)
        n = -n;
    do{
        *s++ = n%10+'0';
    }while((n /= 10) > 0);
    if(sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(t);
}

double atof(char *s){
    double val,power;
    int sign;
    for(;isspace(*s);s++);
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
        s++;
    for(val = 0.0;isdigit(*s);s++)
        val = 10.0*val+(*s-'0');
    if(*s == '.')
        s++;
    for(power = 1.0;isdigit(*s);s++){
        val = 10.0*val+(*s-'0');
        power *= 10.0;
    }
    return sign*val/power;
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

int getop(char *s){
    int c;
    while((*s = c = getch()) == ' ' || c == '\t');
    *(++s) = '\0';
    if(!isdigit(c) && c != '.')
        return c;
    if(isdigit(c))
        while(isdigit(*++s = c = getch()));
    if(c == '.')
        while(isdigit(*++s = c = getch()));
    *s = '\0';
    if(c != EOF)
        ungetch(c);
    return '0';
}

int strindex(char *s,char *t){
    char *b = s;
    char *p,*r;
    for(;*s != '\0';s++){
        for(p = s,r = t;*r != '\0' && *p == *r;p++,r++);
        if(r > t && *r == '\0')
            return s-b;
    }
    return -1;
}