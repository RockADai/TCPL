#include <stdio.h>
/*
编写程序删除C语言中所有注释，要正确处理带引号的字符串与字符常量。（C语言不允许嵌套注释）
*/

void rcomment(int c);
void in_comment();
void echo_quote(int c);

int main(){
    int c;
    while((c = getchar()) != EOF)
        rcomment(c);
    return 0;
}

void rcomment(int c){
    int d;
    if(c == '/')
        if((d = getchar()) == '*')
            in_comment();//输入注释开始判定符时，调用in_comment()处理合法注释
        else if(d == '/'){
            putchar(c);
            rcomment(d);//若输入的是单行注释，通过递归进行字符处理（实测不删除单行注释？）
        }
        else{
            putchar(c);
            putchar(d);
        }//否则正常输出
    else if(c == '\'' || c == '"')
        echo_quote(c);//当输入单引号或双引号时调用echo_quote()处理
    else
        putchar(c);//其他情况正常输出
}//该函数处理每个输入字符，寻找注释并删除

void in_comment(){
    int c,d;
    c = getchar();
    d = getchar();
    while(c != '*' || d != '/'){
        c = d;
        d = getchar();
    }//找到注释结束符"*/"之前，每次循环用下一个输入字符覆盖当前输入，从而去掉注释
}//该函数负责注释的内部处理

void echo_quote(int c){
    int d;
    putchar(c);
    while((d = getchar()) != c){
        putchar(d);
        if(d = '\\')
            putchar(getchar());
    }//确保引号中内容按原样输出
    putchar(d);
}//处理输入了单引号或双引号的情形
