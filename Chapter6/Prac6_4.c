#include <stdio.h>
#include <ctype.h>

/*
编写一个程序，根据单词出现频率按降序打印输入的各个不同单词，并在每个单词前标上其出现次数
*/

#define MAXWORD 100
#define NDISTINCT 1000

struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};//二叉树定义
typedef struct tnode wordnode;
wordnode *list[NDISTINCT];
int ntn = 0;
wordnode *addtree(wordnode *p,char *w);//在二叉链表内的p节点或其子节点增加一个单词w
int getword(char *word,int lim);
wordnode *talloc();
void sortlist();
void treestore(wordnode *p);

int main(){
    wordnode *root;
    char word[MAXWORD];
    int i;
    root = NULL;
    while(getword(word,MAXWORD) != EOF)
        if(isalpha(word[0]))
            root = addtree(root,word);
    treestore(root);
    sortlist();
    for(i = 0;i < ntn;i++)
        printf("%2d:%20s\n",list[i]->count,list[i]->word);
    return 0;
}

void treestore(wordnode *p){
    if(p != NULL){
        treestore(p->left);
        if(ntn < NDISTINCT)
            list[ntn++] = p;
        treestore(p->right);
    }
}

void sortlist(){
    int gap,i,j;
    wordnode *temp;
    for(gap = ntn/2;gap > 0;gap /= 2)
        for(i = gap;i < ntn;i++)
            for(j = i-gap;j >= 0;j -= gap){
                if((list[j]->count) >= (list[j+gap]->count))
                    break;
                temp = list[j];
                list[j] = list[j+gap];
                list[j+gap] = temp;
            }
}

wordnode *addtree(wordnode *p,char *w){
    int cond;
    if(p == NULL){
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w,p->word)) == 0)
        p->count++;
    else if(cond < 0)
        p->left = addtreex(p->left,w);
    else
        p->right = addtreex(p->right,w);
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

wordnode *talloc(){
    return (wordnode *)malloc(sizeof(wordnode));
}
