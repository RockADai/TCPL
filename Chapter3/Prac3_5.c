#include <stdio.h>
/*
编写函数itob(n,s,b)，将整数n转换为以b为底的数，并将转换结果以字符的形式保存到字符串s中
*/
void itob(int n,char s[],int b){
    int i,j,sign;
    void reverseStr(char s[]);
    if((sign = n) < 0)
        n = -n;
    i = 0;
    do{
        j = n%b;
        s[i++] = (j <= 9) ? j+'0' : j+'a'-10;
    }while((n /= b) > 0);//逆序生成b进制位的各位数字
    if(sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverseStr(s);
}
void reverseStr(char s[]){
    int i=0;
    char temp;
    while(s[i]!='\n')
        ++i;
    --i;
    for(int j=0;j<=i;++j,--i){
        temp=s[j];
        s[j]=s[i];
        s[i]=temp;
    }
}