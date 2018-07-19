#include <stdio.h>
/*
修改itoa使其可以接受三个参数，第三个参数为最小字段宽度
为了保证转换后结果至少具有参数指定的最小宽度，必要时应在所得结果左边填充一定的空格
*/

#define abs(x) ((x) < 0 ? -(x) : (x))//计算绝对值

void itoa(int n,char s[],int w){
    int i,sign;
    void reverseStr(char s[]);
    sign = n;
    i = 0;
    do{
        s[i++] = abs(n%10)+'0';
    }while((n /= 10) != 0);
    if(sign < 0)
        s[i++] = '-';
    while(i < w)
        s[i++] = ' ';//若字长小于指定字段宽度，则填充空格，转置后空格将出现在左侧
    s[i] = '\0';
    reverseStr(s);
}