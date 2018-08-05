#include <stdio.h>
#include <math.h>
/*
运用printd函数的设计思想编写一个递归版本的itoa函数，即通过递归调用把整数转换为字符串。
*/
void itoa(int n,char s[]){
    static int i;//i作为字符数组的索引，最好声明为静态变量
    if(n/10)
        itoa(n/10,s);//递归调用，每次处理将原数除以10
    else{//n/10结果为0时获得最高位
        i = 0;
        if(n < 0)
            s[i++] = '-';//负数下一位增加-号
    }
    s[i++] = abs(n)%10+'0';
    s[i] = '\0';
}