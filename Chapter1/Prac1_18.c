#include <stdio.h>
/*
ɾ��ÿ��������ĩβ�Ŀո��Ʊ������ɾ����ȫ�ǿո����
*/
#define MAXLINE 1000
int getline(char line[],int lim);
int removeBlank(char line[]);
int main(){
    char line[MAXLINE];
    while(getline(line,MAXLINE)>0){
        removeBlank(line);
        printf("%s",line);
    }
}
int getline(char line[],int lim){
    int c,i;
    for(i=0;i<lim-1&&(c=getchar())!=EOF&&c!='\n';++i)
        line[i]=c;
    if(c=='\n'){
        line[i]=c;
        ++i;
    }
    line[i]='\0';
    return i;
}
int removeBlank(char line[]){
    int i=0;
    while(line[i]!='\n')
        ++i;
    --i;//��ָʾ����λ���������һ���ַ�
    while(i>=0&&(line[i]==' '||line[i]=='\t'))
        --i;//ָʾ��ǰ��ֱ����ǰ�ַ����ǿո���Ʊ��
    if(i>=0){
        ++i;
        line[i]='\n';
        ++i;
        line[i]='\0';
    }//�ж��Ƿ�Ϊȫ�ո��У����������У�ע��ȫ�ո��кͿ��ַ���������
    return i;
}
