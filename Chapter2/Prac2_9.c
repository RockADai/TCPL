#include <stdio.h>
/*
重写bitcount函数，加快执行速度
*/
int bitcount(unsigned x){
    int b;
    for(b = 0;x != 0;x &= (x-1))
        b++;
    return b;
}
/*
x&(x-1)将清除x最右端值为1的位
在上述函数中，每执行一次循环，则从右向左清除x中的一位1，并获得操作次数
即操作次数 = x中1的个数
*/