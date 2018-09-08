#include "syscalls.h"

/*
编写函数bfree(p,n)，释放一个包含n个字符的任意块p，并放入由malloc和free维护的空闲块链表中
通过使用bfree，用户可以在任意时刻向空闲块链表中添加一个静态或外部数组
*/

unsigned bfree(char *p,unsigned n){
    Header *hp;
    if(n < sizeof(Header))
        return 0;
    hp = (Header *)p;
    hp->s.size = n/sizeof(Header);
    free((void *)(hp+1));
    return hp->s.size;
}