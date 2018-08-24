#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
编写程序tail，将输入中的最后n行打印出来，可通过-n改变n的值
*/

#define DEFLINES 10//默认打印行数
#define LINES 100//最大行数
#define MAXLEN 100//输入行最大长度

void error(char *s);
int getline(char *s,int lim);

int main(int argc, char const *argv[])
{
    char *p,*buf,*bufend;
    char line[MAXLEN];
    char *lineptr[LINES];
    int first,i,last,len,n,nlines;
    if(argc == 1)
        n = DEFLINES;
    else if(argc == 2 && (*++argv)[0] == '-')
        n = atoi(argv[0]+1);
    else
        error("usage:tail [-n]");
    if(n < 1 || n > LINES)
        n = LINES;
    for(i = 0;i < LINES;i++)
        lineptr[i] = NULL;
    if((p = buf = malloc(LINES*MAXLEN)) == NULL)
        error("tail:cannot allocate buf");
    bufend = buf+LINES*MAXLEN;
    last = 0;
    nlines = 0;
    while((len = getline(line,MAXLEN)) > 0){
        if(p+len+1 >= bufend)
            p = buf;
        lineptr[last] = p;
        strcpy(lineptr[last],line);
        if(++last >= LINES)
            last = 0;
        p += len+1;
        nlines++;
    }
    if(n > nlines)
        n = nlines;
    first = last-n;
    if(first < 0)
        first += LINES;
    for(i = first;n-- > 0;i=(i+1)%LINES)
        printf("%s",lineptr[i]);
    return 0;
}

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

void error(char *s){
    printf("%s\n",s);
    exit(1);
}
