#include <stdio.h>
/*
�޸�P21����ʹ����Դ�ӡ���ⳤ�ȵ������еĳ��ȣ��������ܶ�Ĵ�ӡ�ı�
*/
#define MAXLINE 1000
int getline(char line[],int lim);//��һ�ж��뵽s�в������䳤��
void copy(char to[],char from[]);//��from[]���Ƶ�to[]
int main(){
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    max=0;
    while((len=getline(line,MAXLINE))>0){
        printf("%d %s",len,line);
        if(len>max){
            max=len;
            copy(longest,line);
        }
    }
    if(max>0)
        printf("%s",longest);
    return 0;
}
int getline(char line[],int lim){
    int c,i,j=0;
    for(i=0;(c=getchar())!=EOF&&c!='\n';++i)
        if(i<lim-2){
            line[j]=c;
            ++j;
        }//�ַ���δ����
    if(c=='\n'){
        line[j]=c;
        ++i;
        ++j;
    }
    line[j]='\0';
    return i;
}
void copy(char to[],char from[]){
    int i=0;
    while((to[i]=from[i])!='\0')
        ++i;
}
