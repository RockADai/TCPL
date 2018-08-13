#include <stdio.h>
/*
用指针实现函数strcat，将t指向的字符串复制到s指向的字符串的尾部
*/
void strcat(char *s,char *t){
    int i;
    while(*s)
        s++;//指针后移直至指向字符串末尾
    while(*s++ = *t++);//循环操作t中每一个字符存入s，t指向的位置等于s的末尾
}