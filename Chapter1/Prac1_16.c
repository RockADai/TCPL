#include <stdio.h>
/*
修改P21程序，使其可以打印任意长度的输入行的长度，并尽可能多的打印文本
*/
#define MAXLINE 1000
int getline(char line[],int lim);//将一行读入到s中并返回其长度
void copy(char to[],char from[]);//将from[]复制到to[]
int main(){
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    max=0;
    while((len=getline(line,MAXLINE))>0){
        printf("%d %s",len,line);
        if(len>max){
            max=len;
            copy(longest,line);
        }
    }
    if(max>0)
        printf("%s",longest);
    return 0;
}
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
void copy(char to[],char from[]){
    int i=0;
    while((to[i]=from[i])!='\0')
        ++i;
}
