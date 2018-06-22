#include <stdio.h>
/*
本例程用于练习程序测试
*/
#define IN 1
#define OUT 0
/*
统计输入的行数、单词数、字符数
*/
int main(){
    int c,nl,nw.nc,state;
    state=OUT;
    nl=nw=nc=0;
    while((c=getchar())!=EOF){
        ++nc;
        if(c=='\n')
            ++nl;
        if(c==' '||c=='\n'||c=='\t')
            state=OUT;
        else if(state==OUT){
            state=IN;
            ++nw;
        }
    }
    printf("%d %d %d\n",nl,nw,nc);
    return 0;
}
