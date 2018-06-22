#include <stdio.h>
/*
编写程序entab，将空格串替换为最少数量的制表符和空格，但要保持单词之间的间隔不变。
假设制表符终止位的位置与detab相同，当使用一个制表符或一个空格都可以到达下一个制表符终止位时，选用哪种替换字符较好？
*/

#define TABSPACE 6//制表位大小
int main(){
    int c,nblank,ntab,pos;
    nblank = 0;//需要的空格数
    ntab = 0;//需要的tab数
    for(pos = 1;(c=getchar()) != EOF;++pos){
        if(c == ' '){
            if(pos%TABSPACE != 0)
                ++nblank;//当前位置对制表位取余，若不为0则所需空格数数+1
            else{
                nblank = 0;//若取余为0则重置所需空格数，所需tab数+1
                ++ntab;
            }
        }//输入为空格时的处理
        else{
            for(;ntab > 0;--ntab)
                putchar('\t');
            if(c == '\t')
                nblank = 0;//若输入了tab则重置所需空格数
            else
                for(;nblank > 0;--nblank)
                    putchar(' ');
            putchar(c);
            if(c == '\n')
                pos = 0;//若输入了换行符则充值pos，表示开始新行
            else if(c == '\t')
                pos = pos+(TABSPACE-(pos-1)%TABSPACE)-1;//若输入了tab则位置置于下一个制表位
        }
    }
}
