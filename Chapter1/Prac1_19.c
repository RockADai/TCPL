#include <stdio.h>
/*
编写函数reverseStr(s)，将字符串s倒置；
使用该函数编写一个程序，每次颠倒一个输入行中的字符顺序
*/
#define MAXLINE 1000
int getline(char line[],int lim);
void reverseStr(char s[]){
    int i=0;
    char temp;
    while(s[i]!='\n')
        ++i;
    --i;
    for(int j=0;j<=i;++j,--i){
        temp=s[j];
        s[j]=s[i];
        s[i]=temp;
    }
}
int main(){
    char line[MAXLINE];
    while(getline(line,MAXLINE)>0){
        reverseStr(line);
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
