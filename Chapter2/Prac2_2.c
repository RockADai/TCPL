#include <stdio.h>
/*
在不使用运算符&&或||的条件下编写与
for(i = 0;i < lim-1 && (c = getchar()) != '\n' && c != EOF;i++)语句等价的循环语句
*/
int main(){
    enum status{NO,YES};
    enum status stat = YES;
    int i = 0;
    int c,lim;
    char s[100];
    while(stat == YES){
        if(i >= lim-1)
            stat = NO;
        else if((c = getchar()) == '\n')
            stat = NO;
        else if(c == EOF)
            stat = NO;
        else{
            s[i] = c;
            i++;
        }
    }
}
