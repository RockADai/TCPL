#include <stdio.h>
/*
编写函数rightrot(x,n)，返回将x循环右移（从最右端移出的位将从最左端移入）n位所得的值
*/
unsigned rightrot(unsigned x,int n){
    int i;
    unsigned v = (unsigned)~0;
    for(i = 1;(v = v >> 1) > 0;i++);//算出计算机使用的字长
    int rbit;//右移最大位数
    while(n-- > 0){
        rbit = (x&1) << (i-1);//每次将最右端的一位左移到最左端
        x = x >> 1;
        x = x|rbit;//x右移一位，与rbit相或得到循环右移一位的值
    }
    return x;
}