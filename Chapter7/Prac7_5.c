#include<stdio.h>
#include<ctype.h>

/*
改写第4章中的后缀计算器，用scanf和（或）sscanf实现输入以及数的转换
*/

#define NUMBER '0'

int getop(char s[]){
    int c,rc;
    float f;
    while((rc = scanf("%c",&c)) != EOF)
        if((s[0] = c) != ' ' && c != '\t')
            break;
    s[1] = '\0';
    if(rc == EOF)
        return EOF;
    else if(!isdigit(c) && c != '.')
        return c;
    ungetc(c,stdin);
    scanf("%f",&f);
    sprintf(s,"%f",f);
    return NUMBER;
}