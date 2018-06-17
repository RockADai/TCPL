#include <stdio.h>
/*
编写程序detab，将输入中的制表符替换成适当数目的空格，使空格充满到下一个制表符终止位的地方；
假设制表符终止位的位置是固定的，比如每隔n列就会出现一个制表符终止位，n应该作为变量还是符号常量呢？
*/
#define TABSPACE 6//制表位大小
int main(){
    int c,nblank,pos;
    nblank=0;//需要的空格数
    pos=1;//行的当前位置
    while((c=getchar())!=EOF){
        if(c=='\t'){
            nblank=TABSPACE-(pos-1)%TABSPACE;
            /*每TABSPACE个位置为一个制表位，若已输入字符位数对TABSPACE取余不为0，则令TABSPACE减去余数，
            获得填充制表位所需剩余空格数，并用空格替换*/
            while(nblank>0){
                putchar(' ');
                ++pos;
                --nblank;
            }
        }//若输入制表符则替换为空格
        else if(c=='\n'){
            putchar(c);
            pos=1;
        }//若输入换行符，pos置1，表示开始新行
        else{
            putchar(c);
            ++pos;
        }//普通字符直接输出
    }
}
//n应该作为常量，即本程序中的TABSPACE
