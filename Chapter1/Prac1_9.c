#include <stdio.h>
/*
�����븴�Ƶ��������������ո���һ���ո����
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
