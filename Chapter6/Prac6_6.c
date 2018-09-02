#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*以6.6节中的函数为基础，编写一个适合C语言程序使用的#define处理器的简单版本（即无参数情况）*/

#define MAXWORD 101
#define HASHSIZE 101
struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};//链表存放名字和替换文本

void error(int c,char *s);
int getch();
void ungetch();
int getword(char *word,int lim);
struct nlist *install(char *name,char *defn);
struct nlist *lookup(char *s);
unsigned hash(char *s);
void getdef();
void ungets(char *s);
void skipblanks();
void undef(char *s);
static struct nlist *hashtab[HASHSIZE];//指针表

int main(){
    char w[MAXWORD];
    struct nlist *p;
    while(getword(w,MAXWORD) != EOF)
        if(strcmp(w,"#") == 0)
            getdef();
        else if(!isalpha(w[0]))
            printf("%s",w);
        else if((p = lookup(w)) == NULL)
            printf("%s",w);
        else
            ungets(p->defn);
    return 0;
}

void getdef(){
    int c,i;
    char def[MAXWORD],dir[MAXWORD],name[MAXWORD];
    skipblanks();
    if(!isalpha(getword(dir,MAXWORD)))
        error(dir[0],"getdef:expecting a directive after #");
    else if(strcmp(dir,"define") == 0){
        skipblanks();
        if(!isalpha(getword(name,MAXWORD)))
            error(name[0],"getdef:non-alpha-name expected");
        else{
            skipblanks();
            for(i = 0;i < MAXWORD-1;i++)
                if((def[i] = getch()) == EOF || def[i] == '\n')
                    break;
            def[i] = "\0";
            if(i <= 0)
                error('\n',"getdef:incomplete define");
            else
                install(name,def);
        }
    }
    else if(strcmp(dir,"undef") == 0){
        skipblanks();
        if(!isalpha(getword(name,MAXWORD)))
            error(name[0],"getdef:non-alpha in undef");
        else
            undef(name);
    }
    else
        error(dir[0],"getdef:expecting a directive after #");
}

void skipblanks(){
    int c;
    while((c = getch()) == ' ' || c == '\t');
    ungetch(c);
}

void error(int c,char *s){
    printf("error:%s\n",s);
    while(c != EOF && c != '\n')
        c = getch();
}

void undef(char *s){
    int h;
    struct nlist *prev,*np;
    prev = NULL;
    h = hash(s);
    for(np = hashtab[h];np != NULL;np = np->next){
        if(strcmp(s,np->name) == 0)
            break;
        prev = np;//保存刚遍历到的节点
    }//查找字符串s，若找到则跳出循环，否则遍历完成后终止
    if(np != NULL){//np不为NULL则所指hash表存在需清除定义
        if(prev == NULL)
            hashtab[h] = np->next;
        else
            prev->next = np->next;//删除节点
        free((void *)np->name);
        free((void *)np->defn);
        free((void *)np);//要将成员和存储结构本身都释放
    }
}

struct nlist *install(char *name,char *defn){
    struct nlist *np;
    unsigned hashval;
    if((np = lookup(name)) == NULL){
        np = (struct nlist *)malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *)np->defn);
    if((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

struct nlist *lookup(char *s){
    struct nlist *np;
    for(np = hashtab[hash(s)];np != NULL;np = np->next)
        if(strcmp(s,np->name) == 0)
            return np;
    return NULL;
}

unsigned hash(char *s){
    unsigned hashval;
    for(hashval = 0;*s != 0;s++)
        hashval = *s+31*hashval;
    return hashval%HASHSIZE;
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

void ungets(char s[]){
    int len = strlen(s);
    while(len > 0)//执行ungetch操作，次数为字符串s的字符个数
        ungetch(s[--len]);//先减1去掉\0
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
