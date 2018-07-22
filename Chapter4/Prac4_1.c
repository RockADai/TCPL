#include <stdio.h>
#include <string.h>
/*
编写函数strrindex(s,t)，它返回字符串t在s中最右边出现的位置
若s中不包含t则返回-1
*/
int strrindex(char s[],char t[]){
    int i,j,k;
    for(i = strlen(s)-strlen(t);i >= 0;i--){
        for(j = i,k = 0;t[k] != '\0' && s[j] == t[k];j++,k++);
        if(k > 0 && t[k] == '\0')
            return i;
    }//若未从s尾部向串首推进t的长度个字符处开始寻找，可能导致不完整目标字符串被检索
    return -1;
}