#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
编写函数undef，它将从由lookup和install维护的表中删除一个变量名及其定义
*/

#define HASHSIZE 101
struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};//链表存放名字和替换文本
static struct nlist *hashtab[HASHSIZE];//指针表
unsigned hash(char *s);

void undef(char *s){
    int h;
    struct nlist *prev,*np;
    prev = NULL;
    h = hash(s);
    for(np = hashtab[h];np != NULL;np = np->next){
        if(strcmp(s,np->name) == 0)
            break;
        prev = np;//保存刚遍历到的节点
    }//查找字符串s，若找到则跳出循环，否则遍历完成后终止
    if(np != NULL){//np不为NULL则所指hash表存在需清除定义
        if(prev == NULL)
            hashtab[h] = np->next;
        else
            prev->next = np->next;//删除节点
        free((void *)np->name);
        free((void *)np->defn);
        free((void *)np);//要将成员和存储结构本身都释放
    }
}

unsigned hash(char *s){
    unsigned hashval;
    for(hashval = 0;*s != 0;s++)
        hashval = *s+31*hashval;
    return hashval%HASHSIZE;
}


