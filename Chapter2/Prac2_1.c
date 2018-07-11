#include <stdio.h>
#include <limits.h>
/*
编写程序确定分别由signed及unsigned限定的char、short、int与long类型变量的取值范围。
采用打印标准头文件相应值以及直接计算两种方式实现。
*/
int main(){
    printf("signed char min = %d\n",SCHAR_MIN);//此值在头文件中具有宏定义，下同
    printf("signed char max = %d\n",SCHAR_MAX);
    printf("signed short min = %d\n",SHRT_MIN);
    printf("signed short max = %d\n",SHRT_MAX);
    printf("signed int min = %d\n",INT_MIN);
    printf("signed int max = %d\n",INT_MAX);
    printf("signed long min = %d\n",LONG_MIN);
    printf("signed long max = %d\n",LONG_MAX);

    printf("unsigned char max = %u\n",UCHAR_MAX);
    printf("unsigned short max = %u\n",USHRT_MAX);
    printf("unsigned int max = %u\n",UINT_MAX);
    printf("unsigned long max = %u\n",ULONG_MAX);
    
    //以下为计算方式实现
    /*
    printf("signed char min = %d\n",-(char)((unsigned char)~0 >> 1));//右移一位清除符号位
    printf("signed char max = %d\n",(char)((unsigned char)~0 >> 1));
    printf("signed short min = %d\n",-(short)((unsigned short)~0 >> 1));
    printf("signed short max = %d\n",(short)((unsigned short)~0 >> 1));
    printf("signed int min = %d\n",-(int)((unsigned int)~0 >> 1));
    printf("signed int max = %d\n",(int)((unsigned int)~0 >> 1));
    printf("signed long min = %d\n",-(long)((unsigned long)~0 >> 1));
    printf("signed long max = %d\n",(long)((unsigned long)~0 >> 1));

    printf("unsigned char max = %u\n",(unsigned char)~0);
    printf("unsigned short max = %u\n",(unsigned short)~0);
    printf("unsigned int max = %u\n",(unsigned int)~0);
    printf("unsigned long max = %u\n",(unsigned long)~0);
    */
}