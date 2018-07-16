#include <stdio.h>
/*
编写函数setbits(x,p,n,y)，该函数返回对x执行下列操作后的结果值：
将x中第p位开始的n个二进制位设置为y中最右边n位的值，其余各位保持不变
*/
unsigned setbits(unsigned x,int p,int n,unsigned y){
    return x&~(~(~0 << n) << (p+1-n)) | (y&~(~0 << n)) << (p+1+n);
}