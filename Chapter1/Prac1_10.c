#include <stdio.h>
/*
�����븴�Ƶ�������Ʊ���滻Ϊ\t�����˷��滻Ϊ\b����б���滻Ϊ\\
*/
int main(){
    int c;
    while((c=getchar())!=EOF){
        if(c=='\t')
            printf("\\t");
        else if(c=='\b')
            printf("\\b");
        else if(c=='\\')
            printf("\\\\");
        else
            putchar(c);
    }
    return 0;
}
