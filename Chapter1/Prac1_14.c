#include <stdio.h>
#include <ctype.h>
/*
��ӡ�����и����ַ�����Ƶ��
*/
#define MAXHIST 15//ֱ������󳤶�
#define MAXCHAR 128//����ַ�����
int main(){
    int c,i,maxvalue,barLen;
    int numChar[MAXCHAR];
    for(i=0;i<MAXCHAR;i++){
        numChar[i]=0;
    }
    while((c=getchar())!=EOF){
        if(c<MAXCHAR)
            ++numChar[c];
    }//���봦������ASCII��ֵ
    maxvalue=0;
    for(i=1;i<MAXCHAR;i++){
        if(numChar[i]>maxvalue)
            maxvalue=numChar[i];
    }//���maxvalue
    for(i=1;i<MAXCHAR;i++){
        if(isprint(i))//isprint()�ж�һ���ַ�����ASCII��ֵ��Ӧ���ַ����Ƿ�Ϊ����ʾ�ַ�
            printf("%3d %c %3d",i,i,numChar[i]);//��char�Ϳ����ASCII��ֵ��Ӧ���ַ�
        else
            printf("%3d   %3d",i,numChar[i]);
        barLen=numChar[i]*MAXHIST/maxvalue;//��ֱ��������
        if(numChar[i]>0){
            if(barLen<=0)
                barLen=1;
        }
        else
            barLen=0;
        while(barLen>0){
            putchar('*');
            barLen--;
        }//���ֱ����
        printf("\n");
    }
}
