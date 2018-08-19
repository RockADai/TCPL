#include <stdio.h>
/*
实现库函数strncpy、strncat、strncmp，它们最多对参数字符串中的前n个字符进行操作
*/
int strlen(char *s){
    int i = 0;
    while(*s++)
        i++;
    return i;
}
void strncpy(char *s,char *t,int n){
    while(*t && n-- > 0)//t非空且n>0
        *s++ = *t++;//将t中前n个字符复制到s
    while(n-- > 0)
        *s++ = '\0';//若t长度小于n则在s末尾填充'\0'
}

void strncat(char *s,char *t,int n){
    strncpy(s+strlen(s),t,n);//调用strncpy将t的前n个字符添加到s末尾
}

int strncmp(char *s,char *t,int n){
    for(;*s == *t;s++,t++)
        if(*s == '\0' || --n <= 0)
            return 0;//s到达末尾或成功比较n个字符后终止
    return *s-*t;//否则返回差别点
}