#include <string.h>
/*
编写一个递归版本的reverse(s)函数将字符串倒置。
*/
void reverse(char s[],int i,int len){
    int c,j;
    j = len-(i+1);
    if(i < j){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverse(s,++i,len);
    }
}
//为保持相同的用户接口，原函数应仍声明为void reverse(char s[])，重新声明一个reverser(char s[],int i,int len)






//4.14：定义宏swap(t,x,y)，以交换t类型的两个参数
#define swap(t,x,y) {t _z;\
                    _z = y;\
                    y = x;\
                    x = _z;}