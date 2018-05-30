#include <stdio.h>
/*
以每行一个单词的形式打印输入
*/
#define OUT 0
#define IN 1
int main(){
    int c,state;
    state=OUT;
    while((c=getchar())!=EOF){
        if(c==' '||c=='\t'||c=='\n'){
            if(state==IN){
                printf("\n");
                state=OUT;
            }
        }//注：注意多个连续空格的情况
        else if(state==OUT){
            state=IN;
            putchar(c);
        }
        else
            putchar(c);
    }
    return 0;
}
