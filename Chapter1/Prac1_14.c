#include <stdio.h>
#include <ctype.h>
/*
打印输入中各个字符出现频度
*/
#define MAXHIST 15//直方条最大长度
#define MAXCHAR 128//最大字符种类
int main(){
    int c,i,maxvalue,barLen;
    int numChar[MAXCHAR];
    for(i=0;i<MAXCHAR;i++){
        numChar[i]=0;
    }
    while((c=getchar())!=EOF){
        if(c<MAXCHAR)
            ++numChar[c];
    }//输入处理，根据ASCII码值
    maxvalue=0;
    for(i=1;i<MAXCHAR;i++){
        if(numChar[i]>maxvalue)
            maxvalue=numChar[i];
    }//求出maxvalue
    for(i=1;i<MAXCHAR;i++){
        if(isprint(i))//isprint()判断一个字符（或ASCII码值对应的字符）是否为可显示字符
            printf("%3d %c %3d",i,i,numChar[i]);//用char型可输出ASCII码值对应的字符
        else
            printf("%3d   %3d",i,numChar[i]);
        barLen=numChar[i]*MAXHIST/maxvalue;//求直方条长度
        if(numChar[i]>0){
            if(barLen<=0)
                barLen=1;
        }
        else
            barLen=0;
        while(barLen>0){
            putchar('*');
            barLen--;
        }//输出直方条
        printf("\n");
    }
}
