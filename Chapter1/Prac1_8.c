#include <stdio.h>
/*
ͳ�ƿո��Ʊ�������з�����
*/
int main(){
    int c,numSpace,numTab,numLine;
    numSpace=0;
    numTab=0;
    numLine=0;
    while((c=getchar())!=EOF){
        if(c==' ')
            ++numSpace;
        if(c=='\t')
            ++numTab;
        if(c=='\n')
            ++numLine;
    }
    printf("%d %d %d\n",numSpace,numTab,numLine);
    return 0;
}
