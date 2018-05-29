#include <stdio.h>
/*
统计空格、制表符、换行符个数
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
