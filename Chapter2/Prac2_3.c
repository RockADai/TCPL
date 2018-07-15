#include <stdio.h>
/*
编写函数htoi(s)，把由十六进制数字组成的字符串（包含前缀）转换为与之等价的整型值
*/

#define YES 1
#define NO 0//判断是否输入了十六进制数字符串

int htoi(char s[]){
    int hex,ishex = NO;
    int n = 0;
    int i = 0;
    if(s[i] == '0'){
        i++;
        if(s[i] == 'x' || s[i] == 'X'){
            i++;
            ishex = YES;
        }
    }//检测到0x或0X进入十六进制数
    while(ishex == YES){
        if(s[i] >= '0' && s[i] <= '9')
            hex = s[i]-'0';
        else if(s[i] >= 'a' && s[i] <= 'z')
            hex = s[i]-'a'+10;
        else if(s[i] >= 'A' && s[i] <= 'Z')
            hex = s[i]-'A'+10;
        else
            ishex = NO;
        if(ishex == YES)
            n = hex+16*n;//获取十六进制数赋值给n
        i++;
    }
    return n;
}