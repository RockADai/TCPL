#include <stdio.h>
/*
��ÿ��һ�����ʵ���ʽ��ӡ����
*/
#define OUT 0
#define IN 1
int main(){
    int c,state;
    state=OUT;
    while((c=getchar())!=EOF){
        if(c==' '||c=='\t'||c=='\n'){
            if(state==IN){
                printf("\n");
                state=OUT;
            }
        }//ע��ע���������ո�����
        else if(state==OUT){
            state=IN;
            putchar(c);
        }
        else
            putchar(c);
    }
    return 0;
}
