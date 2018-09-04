#include <stdio.h>
#include <ctype.h>

/*
编写一个程序，以合理的方式打印任何输入，能根据用户习惯以八进制或十六进制打印非显示字符并截断长文本行
*/

#define MAXLINE 100//输出行最大字符容量
#define OCTLEN 6//八进制值长度（可改为十六进制）
int inc(int pos,int n);//用于计算写入位置，并对长文本行进行换行处理

int main(){
    int c,pos;
    pos = 0;
    while((c = getchar()) != EOF)
        if(iscntrl(c) || c == ' '){//若输入非显示字符
            pos = inc(pos,OCTLEN);//pos移动相应长度
            printf("\\%03o",c);//以八进制输出非显示字符（可改为十六进制）
            if(c == '\n'){//若输入换行符
                pos = 0;//pos置0
                putchar('\n');
            }
        }
        else{//否则为显示字符
            pos = inc(pos,1);
            putchar(c);
        }
}

int inc(int pos,int n){
    if(pos+n < MAXLINE)
        return pos+n;
    else{//超出长度限制则自动换行，在第二行移动该字符相应长度
        putchar('\n');
        return n;
    }
}