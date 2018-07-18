#include <stdio.h>
/*
编写函数escape(s,t)，将字符串t复制到字符串s中，并将不可见字符转换为可见的转义字符序列，要求使用switch
再编写一个具有相反功能的函数，将转义字符序列转换为实际字符
*/
void escape(char s[],char t[]){
    int i,j;
    for(i = j = 0;t[i] != '\0';i++){
        switch(t[i]){
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[],char t[]){
    int i,j;
    for(i = j = 0;t[i] != '\0';i++){
        if(t[i] != '\\')
            s[j++] = t[i];
        else{
            switch(t[++i]){
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
        }
    }
    s[j] = '\0';
}