#include <stdio.h>
/*
��д����detab���������е��Ʊ���滻���ʵ���Ŀ�Ŀո�ʹ�ո��������һ���Ʊ����ֹλ�ĵط���
�����Ʊ����ֹλ��λ���ǹ̶��ģ�����ÿ��n�оͻ����һ���Ʊ����ֹλ��nӦ����Ϊ�������Ƿ��ų����أ�
*/
#define TABSPACE 6//�Ʊ�λ��С
int main(){
    int c,nblank,pos;
    nblank=0;//��Ҫ�Ŀո���
    pos=1;//�еĵ�ǰλ��
    while((c=getchar())!=EOF){
        if(c=='\t'){
            nblank=TABSPACE-(pos-1)%TABSPACE;
            /*ÿTABSPACE��λ��Ϊһ���Ʊ�λ�����������ַ�λ����TABSPACEȡ�಻Ϊ0������TABSPACE��ȥ������
            �������Ʊ�λ����ʣ��ո��������ÿո��滻*/
            while(nblank>0){
                putchar(' ');
                ++pos;
                --nblank;
            }
        }//�������Ʊ�����滻Ϊ�ո�
        else if(c=='\n'){
            putchar(c);
            pos=1;
        }//�����뻻�з���pos��1����ʾ��ʼ����
        else{
            putchar(c);
            ++pos;
        }//��ͨ�ַ�ֱ�����
    }
}
//nӦ����Ϊ���������������е�TABSPACE
