#include <stdio.h>
/*
编写函数strend(s,t)，若字符串t出现在字符串s的尾部则返回1，否则返回0
*/
int strend(char *s,char *t){
    char *bs = *s;
    char *bt = *t;//起始地址
    for(;*s;s++);
    for(;*t;t++);
    for(;*s == *t;s--,t--)//将s最后一个字符与t比较，再前移
        if(*t == *bt || *s == *bs)//若退回到t的开始或s的开始（s = t），则退出循环
            break;
    if(*s == *t && t == bt && *s != '\0')//s，t字符匹配且指针t退回到起始且s，t不为空
        return 1;
    else
        return 0;
}