#include "syscalls.h"

/*
通过调用或修改malloc函数实现calloc函数
*/

void *calloc(unsigned n,unsigned size){
    unsigned i,nb;
    char *p,*q;
    nb = n*size;
    if((p = q = malloc(nb)) != NULL)
        for(i = 0;i < nb;i++)
            *p++ = 0;
    return q;
}