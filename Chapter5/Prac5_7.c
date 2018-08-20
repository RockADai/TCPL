#include <string.h>
#include <stdio.h>

/*
重写readlines，将输入的文本行存储到由main提供的一个数组中，而不是由alloc分配的空间中。
该函数运行速度比之前快多少？
*/

#define MAXLEN 1000
#define MAXSTOR 5000//最大存储空间

int getline(char *s,int lim);

int readlines(char *lineptr[],char *linestor,int maxlines){
    int len,nlines;//nlines为输入行数
    char line[MAXLEN];
    char *p = linestor;//设linestor为主函数提供的数组
    char *linestop = linestor+MAXSTOR;
    nlines = 0;
    while((len = getline(line,MAXLEN)) > 0)
        if(nlines >= maxlines || p+len > linestop)//若输入行数超限或存储空间超限则返回异常
            return -1;
        else{
            line[len-1] = '\0';
            strcpy(p,line);
            lineptr[nlines++] = p;
            p += len;
        }//否则读入输入行，并更新存储空间
    return nlines;
}//运行速度比使用alloc稍快

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