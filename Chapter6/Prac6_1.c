#include <stdio.h>
#include <ctype.h>

/*
书上getword函数不能正确处理下划线、字符串常量、注释及预处理器控制指令
请编写一个更完善的getword函数
*/

int getch();
void ungetch(int c);
int comment();

int getword(char *word,int lim){
    int c,d;
    char *w = word;
    while(isspace(c = getch()));
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c) || c == '_' || c == '#'){
        for(;--lim > 0;w++)
            if(!isalnum(*w = getch()) && *w != '_'){
                ungetch(*w);
                break;
            }
    }
    else if(c == '\'' || c == '"'){
        for(;--lim > 0;w++)
            if((*w = getch()) == '\\')
                *++w = getch();
            else if(*w == c){
                w++;
                break;
            }
            else if(*w == EOF)
                break;
    }
    else if(c == '/')
        if((d = getch()) == '*')
            c = comment();
        else
            ungetch(d);
    *w = '\0';
    return c;
}

int buf[100];//输入读取缓冲区
int bufp = 0;
int getch(){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if(bufp >= 100)
        printf("ungetch:too many characters\n");
    else
        buf[bufp++] = c;//将字符存回输入缓冲区
}

int comment(){
    int c;
    while((c = getch()) != EOF)
        if(c == '*')
            if((c = getch()) == '/')
                break;//判断注释结束
            else
                ungetch(c);
    return c;
}
