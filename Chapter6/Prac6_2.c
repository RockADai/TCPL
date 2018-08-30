#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
编写程序读入C语言程序，按字母表顺序分组打印变量名，
要求每一组内各变量名的前6个字符相同，其余字符不同，字符串和注释中的单词不予考虑
将6作为一个可在命令行中设定的参数
*/

#define MAXWORD 100
#define YES 1
#define NO 0

struct tnode{
    char *word;
    int match;
    struct tnode *left;
    struct tnode *right;
};//二叉树定义
typedef struct tnode wordnode;
wordnode *addtreex(wordnode *p,char *w,int num,int *found);//在二叉链表内的p节点或其子节点增加一个单词w
void treexprint(wordnode *p);//按序打印树
int getword(char *word,int lim);
wordnode *talloc();
int compare(char *s,wordnode *p,int num,int *found);

int main(int argc,char *argv[]){
    wordnode *root;//变量名树
    char word[MAXWORD];
    int found = NO;//若识别出变量名树中有相同单词则置YES
    int num;
    num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0]+1) : 6;//若未使用参数指定num值则默认为6
    root = NULL;
    while(getword(word,MAXWORD) != EOF){
        if(isalpha(word[0]) && strlen(word) >= num)//第一个字符是字母且长度>=num，则填入变量名树
            root = addtreex(root,word,num,&found);
        found = NO;
    }
    treexprint(root);
    return 0;
}

wordnode *addtreex(wordnode *p,char *w,int num,int *found){
    int cond;
    if(p == NULL){
        p = talloc();
        p->word = strdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    }
    else if((cond = compare(w,p,num,found)) < 0)
        p->left = addtreex(p->left,w,num,found);
    else if(cond > 0)
        p->right = addtreex(p->right,w,num,found);
    return p;
}

void treexprint(wordnode *p){
    if(p != NULL){
        treexprint(p->left);
        if(p->match)
            printf("%s\n",p->word);
        treexprint(p->right);
    }
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

int getword(char *word,int lim){
    int c;
    char *w = word;
    while(isspace(c = getch()));
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }
    for(;--lim > 0;w++)
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

wordnode *talloc(){
    return (wordnode *)malloc(sizeof(wordnode));
}

int compare(char *s,wordnode *p,int num,int *found){
    int i;
    char *t = p->word;
    for(i = 0;*s == *t;i++,s++,t++)
        if(*s == '\0')
            return 0;
    if(i >= num){
        *found = YES;
        p->match = YES;
    }
    return *s-*t;
}
