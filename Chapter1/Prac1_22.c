#include <stdio.h>
/*
编写一个程序，把较长的输入行折成短一些的两行或多行，折行的位置在输入行的第n列之前的
最后一个非空格之后。要保证程序能够智能地处理输入行很长以及在指定的列前没有空格或制表符时的情况
*/

#define TABSPACE 6//制表位大小
#define MAXCOL 20//最长折行阈值

char line[MAXCOL];//存取输入字符
int exptab(int pos);
int findblank(int pos);
int newpos(int pos);
void printl(int pos);

int main(){
    int c,pos;
    pos = 0;
    while((c = getchar()) != EOF){
        line[pos] = c;
        if(c == '\t')
            pos = exptab(pos);//若输入tab则调用exptab()处理之
        else if(c == '\n'){
            printl(pos);
            pos = 0;
        }//若主动换行则调用printl()输出，并将pos复位，开启新行
        else if(++pos >= MAXCOL){
            pos = findblank(pos);
            printl(pos);
            pos = newpos(pos);
        }//在普通输入情况下调用findblank()和newpos()智能地进行折行
    }
}

void printl(int pos){
    int i;
    for(i = 0;i < pos;++i)
        putchar(line[i]);
    if(pos > 0)
        putchar('\n');//输完一行，换行
}//输出指定长度的一行

int exptab(int pos){
    line[pos] = ' ';//tab至少为一个空格
    for(++pos;pos < MAXCOL && pos%TABSPACE != 0;++pos)
        line[pos] = ' ';//将tab转换为一定数量的空格，使转换后当前位置与制表位对齐
    if(pos < MAXCOL)
        return pos;//若当前位置未达到最大行长，则返回
    else{
        printl(pos);
        return 0;
    }//否则输出该行并返回0，表示提前结束，达到智能处理指定列前tab占位情况
}//将tab转换为一定数量的空格以处理特定情况

int findblank(int pos){
    while(pos > 0 && line[pos] != ' ')
        --pos;//从后往前直至找到第一个空格
    if(pos == 0)
        return MAXCOL;//若未找到空格则返回最大长度
    else
        return pos+1;//否则返回该空格后一个位置
}//智能处理长输入行，若有空格则在空格处换行，无空格才按最大行长度换行

int newpos(int pos){
    int i,j;
    if(pos <= 0 || pos >= MAXCOL)
        return 0;//无字符可用时结束
    else{
        i = 0;
        for(j = pos;j < MAXCOL;++j){
            line[i] = line[j];
            ++i;
        }//将当前位置开始的字符复制到下一行
        return i;//返回新行的输入当前位置
    }
}//该函数用于自动完成长输入时对上一行的折叠
