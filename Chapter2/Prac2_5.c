#include <stdio.h>
/*
编写函数any(s1,s2)将字符串s2中任一字符在s1中第一次出现的位置作为结果返回
若s1中不包含s2的字符则返回-1
*/
int any(char s1[],char s2[]){
    int i;
    for(i = 0;s1[i] != '\0';i++){
        for(j = 0;s2[j] != '\0';j++)
            if(s1[i] == s2[j])
                return i;
    }
    return -1;
}