#include <stdio.h>
/*
将输入复制到输出，连续多个空格用一个空格代替
*/
int main(){
    int c;
    while((c=getchar())!=EOF){
        putchar(c);
    }
    return 0;
}
