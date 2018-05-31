#include <stdio.h>
/*
打印输入中单词长度的直方图
*/
#define MAXLEN 12//单词限定长度
#define MAXHIST 15//直方条最大长度
#define IN 1
#define OUT 0
int main(){
    int c,i,state,overflow,numc,maxvalue,barLen;
    int wordLen[MAXLEN];//存放各长度单词数
    for(i=0;i<MAXLEN;i++){
        wordLen[i]=0;
    }
    state=OUT;
    overflow=0;//超过限长的单词数
    numc=0;//单词长度
    while((c=getchar())!=EOF){
        if(c==' '||c=='\t'||c=='\n'){
            state=OUT;
            if(numc>0){
                if(numc<MAXLEN)
                    ++wordLen[numc];
                else
                    ++overflow;
            }
            numc=0;
        }
        else if(state==OUT){
            state=IN;
            ++numc;
        }
        else
            ++numc;
    }//输入处理及长度存放处理
    maxvalue=0;//同长度最大单词数初始化
    for(i=1;i<MAXLEN;i++){
        if(wordLen[i]>maxvalue)
            maxvalue=wordLen[i];
    }//求出maxvalue
    /*for(i=1;i<MAXLEN;i++){
        printf("%d %d",i,wordLen[i]);//各长度单词数值统计
        barLen=wordLen[i]*MAXHIST/maxvalue;//求直方条长度
        if(wordLen[i]>0){
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
    }//输出水平直方图
    printf("overflows:%d\n",overflow);*/
    //以下为输出垂直直方图实现部分
    for(i=MAXHIST;i>0;i--){
        for(int j=1;j<MAXLEN;j++){
            barLen=wordLen[j]*MAXHIST/maxvalue;
            if(barLen>=i)
                printf(" * ");
            else
                printf("   ");
        }//从最长直方条顶端向底端平铺输出
        printf("\n");
    }
    for(i=1;i<MAXLEN;i++)
        printf("%4d",i);
    printf("\n");
    for(i=1;i<MAXLEN;i++)
        printf("%4d",wordLen[i]);
    printf("\n");
    printf("overflows:%d\n",overflow);//数值统计输出
}
