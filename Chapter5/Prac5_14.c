#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
修改排序程序，第五章习题14-17都写在此文件中
*/

/*
5.14：使程序能处理-r标记，表示以逆序（递减）方式排序，要保证-r和-n能够组合使用
5.15：增加选项-f，使程序不考虑字母大小写之间的区别
5.16：增加选项-d，该选项表明，只对字母、数字和空格进行比较，要保证-d和-f可以组合使用
5.17：增加字段处理功能，使排序程序可根据行内不同字段进行排序，每个字段按一个单独的选项集合进行排序
*/

#define MAXLINES 5000
#define NUMERIC 1
#define DECR 2
#define FOLD 4
#define DIR 8
#define LINES 100
char *lineptr[MAXLINES];
static char option = 0;
int pos1 = 0;
int pos2 = 0;

int readlines(char *lineptr[],int nlines);
void writelines(char *lineptr[],int nlines);
void qsort(void *lineptr[],int left,int right,int (*comp)(void *,void *));
int numcmp(char *,char *);
int charcmp(char *,char *);
void swap(void *v[],int i,int j);
void error(char *s);
void readargs(int argc,char *argv[]);

int main(int argc, char const *argv[])
{
    char *lineptr[LINES];
    int nlines;
    int rc = 0;
    readargs(argc,argv);
    if((nlines = readlines(lineptr,LINES)) > 0){
        if(option&NUMERIC)
            qsort((void **)lineptr,0,nlines-1,(int (*)(void *,void *))numcmp);
        else
            qsort((void **)lineptr,0,nlines-1,(int (*)(void *,void *))charcmp);
        writelines(lineptr,nlines,option&DECR);
    }
    else{
        printf("input too big to sort\n");
        rc = -1;
    }
    return rc;
}

void qsort(void *lineptr[],int left,int right,int (*comp)(void *,void *)){
    int i,last;
    if(left >= right)
        return;
    swap(lineptr,left,(left+right)/2);
    last = left;
    for(i = left+1;i <= right;i++)
        if((*comp)(lineptr[i],lineptr[left]) < 0)
            swap(lineptr,++last,i);
    swap(lineptr,left,last);
    qsort(lineptr,left,last-1,comp);
    qsort(lineptr,last+1,right,comp);
}

int numcmp(char *s1,char *s2){
    double v1,v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2)
        return -1;
    else if(v1 > v2)
        return 1;
    else
        return 0;
}

int charcmp(char *s,char *t){
    char a,b;
    int fold = (option&FOLD) ? 1 : 0;
    int dir = (option&DIR) ? 1 : 0;
    do{
        if(dir){
            while(!isalnum(*s) && *s != ' ' && *s != '\0')
                s++;
            while(!isalnum(*t) && *t != ' ' && *t != '\0')
                t++;
        }
        a = fold ? tolower(*s) : *s;
        s++;
        b = fold ? tolower(*t) : *t;
        t++;
        if(a == b && a == '\0')
            return 0;
    }while(a == b);
    return a-b;
}

void swap(void *v[],int i,int j){
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000
#define MAXSTOR 5000//最大存储空间
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int getline(char *s,int lim);
char *alloc(int n);

int readlines(char *lineptr[],int maxlines){
    int len,nlines;//nlines为输入行数
    char line[MAXLEN],*p;
    nlines = 0;
    while((len = getline(line,MAXLEN)) > 0)
        if(nlines >= maxlines || (p = alloc(len)) == NULL)//若输入行数超限或存储空间超限则返回异常
            return -1;
        else{
            line[len-1] = '\0';
            strcpy(p,line);
            lineptr[nlines++] = p;
        }//否则读入输入行，并更新存储空间
    return nlines;
}

void writelines(char *lineptr[],int nlines,int decr){
    int i;
    if(decr)
        for(i = nlines-1;i >= 0;i--)
            printf("%s\n",lineptr[i]);
    else
        for(i = 0;i < nlines;i++)
            printf("%s\n",lineptr[i]);
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

char *alloc(int n){
    if(allocbuf+ALLOCSIZE-allocp >= n){
        allocp += n;
        return allocp-n;
    }
    else
        return 0;
}

void error(char *s){
    printf("%s\n",s);
    exit(1);
}

int atoi(char *s);

void readargs(int argc,char *argv[]){
    int c;
    while(--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+'){
        if(c == '-' && !isdigit(*(argv[0]+1)))
            while(c = *++argv[0])
                switch(c){
                    case 'd':
                        option |= DIR;
                        break;
                    case 'f':
                        option |= FOLD;
                        break;
                    case 'n':
                        option |= NUMERIC;
                        break;
                    case 'r':
                        option |= DECR;
                        break;
                    default:
                        printf("sort:illegal option %c\n",c);
                        error("usage:sort -dfnr [+pos1] [-pos2]");
                        break;
                }
        else if(c == '-')
            pos2 = atoi(argv[0]+1);
        else if((pos1 = atoi(argv[0]+1)) < 0)
            error("usage:sort -dfnr [+pos1] [-pos2]");
    }
    if(argc || pos1>pos2)
        error("usage:sort -dfnr [+pos1] [-pos2]");
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
