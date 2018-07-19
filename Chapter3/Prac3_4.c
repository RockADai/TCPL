#include <stdio.h>
/*
书中的itoa函数不能处理最大的负数，即n等于-(2^(字长-1))的情况
修改该函数使其在任何机器上都能正确运行
*/

#define abs(x) ((x) < 0 ? -(x) : (x))//计算绝对值

void itoa(int n,char s[]){
    int i,sign;
    void reverseStr(char s[]);
    sign = n;
    i = 0;
    do{
        s[i++] = abs(n%10)+'0';
    }while((n /= 10) != 0);
    if(sign < 0)
        s[i++] = '-';//倒序赋值该负数再转置
    s[i] = '\0';
    reverseStr(s);
}
//-(2^(字长-1))不能通过n = -n;转换为一个正数
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