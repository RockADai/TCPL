#include <stdio.h>
/*
打印长度大于80个字符的所有输入行
*/
#define MAXLINE 1000
int getline(char line[],int lim);//将一行读入到s中并返回其长度
//void copy(char to[],char from[]);//将from[]复制到to[]
int main(){
    int len;
    //int max;
    char line[MAXLINE];
    //max=0;
    while((len=getline(line,MAXLINE))>0){
        if(len>80){
            printf("%s",line);
        }
    }
    return 0;
}
int getline(char line[],int lim){
    int c,i;
    for(i=0;(c=getchar())!=EOF&&c!='\n';++i)
        line[i]=c;
    if(c=='\n'){
        line[i]=c;
        ++i;
    }
    line[i]='\0';
    return i;
}
/*void copy(char to[],char from[]){
    int i=0;
    while((to[i]=from[i])!='\0')
        ++i;
}*/
