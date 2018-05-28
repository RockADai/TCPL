#include <stdio.h>
/*
摄氏温度转化为华氏温度
*/
int main(){
    float fahr,celsius;
    int lower,upper,step;
    lower=0;
    upper=300;
    step=20;
    printf("Celsius to Fahrenheit:\n");
    celsius=lower;
    while(celsius<=upper){
        fahr=celsius*(9.0/5.0)+32.0;
        printf("%3.0f %6.1f\n",celsius,fahr);
        celsius=celsius+step;
    }
    return 0;
}
