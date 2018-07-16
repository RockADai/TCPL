#include <stdio.h>
/*
编写函数invert(x,p,n)，该函数返回对x执行下列操作后的结果值：
将x中第p位开始的n个二进制位求反，其余各位保持不变
*/
unsigned invert(unsigned x,int p,int n){
    return x^(~(~0 << n) << (p+1-n));
}