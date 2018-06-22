#include <stdio.h>
/*
将输入复制到输出，连续多个空格用一个空格代替
*/
int main(){
    int c;
    char lastc='0';
    while((c=getchar())!=EOF){
        if(c!=' ')
            putchar(c);
        else if(lastc!=' ')
            putchar(c);
        lastc=c;
    }
    return 0;
}
