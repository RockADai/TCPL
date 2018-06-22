#include <stdio.h>
/*
删除每个输入行末尾的空格及制表符，并删除完全是空格的行
*/
#define MAXLINE 1000
int getline(char line[],int lim);
int removeBlank(char line[]);
int main(){
    char line[MAXLINE];
    while(getline(line,MAXLINE)>0){
        removeBlank(line);
        printf("%s",line);
    }
}
int getline(char line[],int lim){
    int c,i;
    for(i=0;i<lim-1&&(c=getchar())!=EOF&&c!='\n';++i)
        line[i]=c;
    if(c=='\n'){
        line[i]=c;
        ++i;
    }
    line[i]='\0';
    return i;
}
int removeBlank(char line[]){
    int i=0;
    while(line[i]!='\n')
        ++i;
    --i;//将指示器定位至该行最后一个字符
    while(i>=0&&(line[i]==' '||line[i]=='\t'))
        --i;//指示器前移直到当前字符不是空格或制表符
    if(i>=0){
        ++i;
        line[i]='\n';
        ++i;
        line[i]='\0';
    }//判断是否为全空格行，并结束该行；注意全空格行和空字符串的区别
    return i;
}
