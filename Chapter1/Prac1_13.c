#include <stdio.h>
/*
��ӡ�����е��ʳ��ȵ�ֱ��ͼ
*/
#define MAXLEN 12//�����޶�����
#define MAXHIST 15//ֱ������󳤶�
#define IN 1
#define OUT 0
int main(){
    int c,i,state,overflow,numc,maxvalue,barLen;
    int wordLen[MAXLEN];//��Ÿ����ȵ�����
    for(i=0;i<MAXLEN;i++){
        wordLen[i]=0;
    }
    state=OUT;
    overflow=0;//�����޳��ĵ�����
    numc=0;//���ʳ���
    while((c=getchar())!=EOF){
        if(c==' '||c=='\t'||c=='\n'){
            state=OUT;
            if(numc>0){
                if(numc<MAXLEN)
                    ++wordLen[numc];
                else
                    ++overflow;
            }
            numc=0;
        }
        else if(state==OUT){
            state=IN;
            ++numc;
        }
        else
            ++numc;
    }//���봦�����ȴ�Ŵ���
    maxvalue=0;//ͬ������󵥴�����ʼ��
    for(i=1;i<MAXLEN;i++){
        if(wordLen[i]>maxvalue)
            maxvalue=wordLen[i];
    }//���maxvalue
    /*for(i=1;i<MAXLEN;i++){
        printf("%d %d",i,wordLen[i]);//�����ȵ�����ֵͳ��
        barLen=wordLen[i]*MAXHIST/maxvalue;//��ֱ��������
        if(wordLen[i]>0){
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
    }//���ˮƽֱ��ͼ
    printf("overflows:%d\n",overflow);*/
    //����Ϊ�����ֱֱ��ͼʵ�ֲ���
    for(i=MAXHIST;i>0;i--){
        for(int j=1;j<MAXLEN;j++){
            barLen=wordLen[j]*MAXHIST/maxvalue;
            if(barLen>=i)
                printf(" * ");
            else
                printf("   ");
        }//���ֱ����������׶�ƽ�����
        printf("\n");
    }
    for(i=1;i<MAXLEN;i++)
        printf("%4d",i);
    printf("\n");
    for(i=1;i<MAXLEN;i++)
        printf("%4d",wordLen[i]);
    printf("\n");
    printf("overflows:%d\n",overflow);//��ֵͳ�����
}
