#include <stdio.h>
/*
重新编写函数squeeze(s1,s2),将字符串s1中任何与字符串s2中字符匹配的字符都删除
*/
void squeeze(char s1[],char s2[]){
    int i,j,k;
    for(i = k = 0;s1[i] != '\0';i++){
        for(j = 0;s2[j] != '\0' && s2[j] != s1[i];j++);//遍历s2
        if(s2[j] == '\0')
            s1[k++] = s1[i];//若遍历到s2结束仍未发现匹配字符，才拷贝下一个字符
    }
    s1[k] = '\0';
}