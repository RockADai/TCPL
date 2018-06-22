#include <stdio.h>
/*
ÖØĞ´ÎÂ¶È×ª»»
*/
float celsius_to_fahr(float fahr){
    return (5.0/9.0)*(fahr-32.0);
}
int main(){
    float fahr,celsius;
    int lower,upper,step;
    lower=0;
    upper=300;
    step=20;
    printf("Fahrenheit to Celsius:\n");
    fahr=lower;
    while(fahr<=upper){
        celsius=celsius_to_fahr(fahr);
        printf("%3.0f %6.1f\n",fahr,celsius);
        fahr=fahr+step;
    }
    return 0;
}
