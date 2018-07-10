#include <stdio.h>
/*
编写程序查找C语言程序中的基本语法错误，如各种括号不配对等。
要正确处理引号、转义字符序列与注释
*/

int brace,brack,paren;//花括号，方括号，圆括号

void in_quote(int c);
void in_comment();
void search(int c);

int main(){
    int c;
    while((c = getchar()) != EOF){
        if(c == '/'){
            if((c = getchar()) == '*')
                in_comment();
            else
                search(c);
        }
        else if(c == '\'' || c =='"')
            in_quote(c);
        else
            search(c);

        if(brace < 0){
            printf("Unbalanced braces.\n");
            brace = 0;
        }
        else if(brack < 0){
            printf("Unbalanced bracks.\n");
            brack = 0;
        }
        else if(paren < 0){
            printf("Unbalanced parens.\n");
            paren = 0;
        }
    }
    if(brace > 0){
        printf("Unbalanced braces.\n");
        brace = 0;
    }
    if(brack > 0){
        printf("Unbalanced bracks.\n");
        brack = 0;
    }
    if(paren > 0){
        printf("Unbalanced parens.\n");
        paren = 0;
    }
}

void search(int c){
    if(c == '{')
        ++brace;
    else if(c == '}')
        --brace;
    else if(c == '[')
        ++brack;
    else if(c == ']')
        --brack;
    else if(c == '(')
        ++paren;
    else if(c == ')')
        --paren;
}//该函数检查括号配对情况

void in_comment(){
    int c,d;
    c = getchar();
    d = getchar();
    while(c != '*' || d != '/'){
        c = d;
        d = getchar();
    }//找到注释结束符"*/"之前，每次循环用下一个输入字符覆盖当前输入，从而去掉注释
}//该函数负责注释的内部处理

void in_quote(int c){
    int d;
    while((d = getchar()) != c)
        if(d == '\\')
            getchar();
}//该函数负责处理引号内容
