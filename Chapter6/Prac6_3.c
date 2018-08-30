#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
编写交叉引用程序，打印文档中所有单词的列表，且每个单词还有一个列表记录其出现的行号
对the、and等非实义单词不予考虑
*/

#define MAXWORD 100

struct linklist{
    int lnum;
    struct linklist *ptr;
};//单链表定义
struct tnode{
    char *word;
    struct linklist *lines;
    struct tnode *left;
    struct tnode *right;
};//二叉树定义
typedef struct linklist link;
typedef struct tnode wordnode;
wordnode *addtreex(wordnode *p,char *w,int linenum);//在二叉链表内的p节点或其子节点增加一个单词w
int getword(char *word,int lim);
void treexprint(wordnode *p);//按序打印树
int noiseword(char *w);
wordnode *talloc();
link *lalloc();
void addln(wordnode *p,int linenum);

int main(){
    wordnode *root;
    char word[MAXWORD];
    int linenum = 1;
    root = NULL;
    while(getword(word,MAXWORD) != EOF){
        if(isalpha(word[0]) && noiseword(word)  == -1)//第一个字符是字母且长度>=num，则填入变量名树
            root = addtreex(root,word,linenum);
        else if(word[0] == '\n')
            linenum++;
    }
    treexprint(root);
    return 0;
}

wordnode *addtreex(wordnode *p,char *w,int linenum){
    int cond;
    if(p == NULL){
        p = talloc();
        p->word = strdup(w);
        p->lines = lalloc();
        p->lines->lnum = linenum;
        p->lines->ptr = NULL;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w,p->word)) == 0)
        addln(p,linenum);
    else if(cond < 0)
        p->left = addtreex(p->left,w,linenum);
    else
        p->right = addtreex(p->right,w,linenum);
    return p;
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

void treexprint(wordnode *p){
    link *temp;
    if(p != NULL){
        treexprint(p->left);
        printf("%10s: ",p->word);
        for(temp = p->lines;temp != NULL;temp = temp->ptr)
            printf("%4d ",temp->lnum);
        printf("\n");
        treexprint(p->right);
    }
}

int noiseword(char *w){
    static char *nw[] = {"a","an","and","are","in","is","of","or","that","the","this","to"};
    int cond,mid;
    int low = 0;
    int high = sizeof(nw)/sizeof(char *)-1;
    while(low <= high){
        mid = (low+high)/2;
        if((cond = strcmp(w,nw[mid])) < 0)
            high = mid-1;
        else if(cond > 0)
            low = mid+1;
        else
            return mid;
    }
    return -1;
}

wordnode *talloc(){
    return (wordnode *)malloc(sizeof(wordnode));
}

link *lalloc(){
    return (link *)malloc(sizeof(link));
}

void addln(wordnode *p,int linenum){
    link *temp;
    temp = p->lines;
    while(temp->ptr != NULL && temp->lnum != linenum)
        temp = temp->ptr;
    if(temp->lnum != linenum){
        temp->ptr = lalloc();
        temp->ptr->lnum = linenum;
        temp->ptr->ptr = NULL;
    }
}
