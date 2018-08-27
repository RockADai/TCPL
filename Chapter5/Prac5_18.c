#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
第五章习题18-20都写在此文件中
*/

/*
5.18：修改dcl，使其能处理输入中的错误
5.19：修改undcl，使它在把文字描述转换为声明的过程中不会生成多余的圆括号
5.10：扩展dcl，使其能处理包含其他成分的声明，如带有函数参数类型的声明、带有const的声明等
*/

#define MAXTOKEN 100
enum{NAME,PARENS,BRACKETS};
enum{NO,YES};
int tokentype;
int prevtoken = NO;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl();
void dirdcl();
void errmsg(char *s);
int gettoken();
int nexttoken();
void parmdcl();
void dclspec();

int main(){
    int type;
    char temp[MAXTOKEN];
    while(gettoken() !=EOF){
        strcpy(out,token);
        while((type = gettoken()) != '\n')
            if(type == PARENS || type == BRACKETS)
                strcat(out,token);
            else if(type == '*'){
                if((type = nexttoken()) == PARENS || type == BRACKETS)
                    sprintf(temp,"(*%s)",out);
                else
                    sprintf(temp,"*%s",out);
                strcpy(out,temp);
            }
            else if(type == NAME){
                sprintf(temp,"%s %s",token,out);
                strcpy(out,temp);
            }
            else
                printf("invalid input at %s\n",token);
        printf("%s\n",out);
    }
}

void dcl(){
    int ns;
    for(ns = 0;gettoken() == '*';)
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out,"pointer to");
}

void dirdcl(){
    int type;
    if(tokentype == '('){
        dcl();
        if(tokentype != ')')
            errmsg("error:missing )\n");
    }
    else if(tokentype == NAME)
        if(name[0] == '\0')
            strcpy(name,token);
    else
        prevtoken = YES;
    while((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if(type == PARENS)
            strcat(out,"function returning");
        else if(type == '('){
            strcat(out,"function expecting");
            parmdcl();
            strcat(out,"and returning");
        }
        else{
            strcat(out,"array");
            strcat(out,token);
            strcat(out,"of");
        }
}

int getch();
void ungetch(int c);

int gettoken(){
    int c;
    char *p = token;
    if(prevtoken == YES){
        prevtoken = NO;
        return tokentype;
    }
    while((c = getch()) == ' ' || c == '\t');
    if(c == '(')
        if((c = getch()) == ')'){
            strcpy(token,"()");
            return tokentype = PARENS;
        }
        else{
            ungetch(c);
            return tokentype = '(';
        }
    else if(c == '['){
        for(*p++ = c;(*p++ = getch()) != ']';);
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if(isalpha(c)){
        for(*p++ = c;isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

void errmsg(char *s){
    printf("%s",s);
    prevtoken = YES;
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

int nexttoken(){
    int type;
    type = gettoken();
    prevtoken = YES;
    return type;
}

void parmdcl(){
    do{
        dclspec();
    }while(tokentype == ',');
    if(tokentype != ')')
        errmsg("missing ) in parameter declaration\n");
}

int typespec();
int typequal();
int compare(char **s,char **t);

void dclspec(){
    char temp[MAXTOKEN];
    temp[0] = '\0';
    gettoken();
    do{
        if(tokentype != NAME){
            prevtoken = YES;
            dcl();
        }
        else if(typespec() == YES){
            strcat(temp, " ");
            strcat(temp,token);
            gettoken();
        }
        else if(typequal() == YES){
            strcat(temp," ");
            strcat(temp,token);
            gettoken();
        }
        else
            errmsg("unknown type in parameter list\n");
    }while(tokentype != ',' && tokentype != ')');
    strcat(out,temp);
    if(tokentype == ',')
        strcat(out,",");
}

int typespec(){
    static char *types[] = {"char","int","void"};
    char *pt = token;
    if(bsearch(&pt,types,sizeof(types)/sizeof(char *),sizeof(char *),compare) == NULL)
        return NO;
    else
        return YES;
}

int typequal(){
    static char *typeq[] = {"const","volatile"};
    char *pt = token;
    if(bsearch(&pt,typeq,sizeof(typeq)/sizeof(char *),sizeof(char *),compare) == NULL)
        return NO;
    else
        return YES;
}

int compare(char **s,char **t){
    return strcmp(*s,*t);
}
