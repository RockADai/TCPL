#include <stdio.h>
#include <stdlib.h>

/*
修改程序entab和detab使他们接收一组作为参数的制表符停止位，
若启动程序时不带参数，则使用默认的制表符停止位设置
第五章习题11、12都写在此文件中
*/

/*
5.12:对entab和detab做一些扩充，以接受命令entab -m +n
表示制表符从第m列开始，每隔n列停止
*/

#define TABSPACE 6//制表位大小
#define MAXLINE 100
#define YES 1
#define NO 0

void settab(int argc,char *argv[],char *tab);
void entab(char *tab);
void detab(char *tab);
int tabpos(int pos,char *tab);

int main(int argc, char const *argv[])
{
    char tab[MAXLINE+1];
    settab(argc,argv,tab);
    entab(tab);
    //detab(tab);
    return 0;
}

void entab(char *tab){
    int c,pos;
    int nb = 0;
    int nt = 0;
    for(pos = 1;(c = getchar()) != EOF;pos++)
        if(c == ' '){
            if(tabpos(pos,tab) == NO)
                ++nb;
            else{
                nb = 0;
                ++nt;
            }
        }
        else{
            for(;nt > 0;nt--)
                putchar('\t');
            if(c == '\t')
                nb = 0;
            else
                for(;nb > 0;nb--)
                    putchar(' ');
            putchar(c);
            if(c == '\n')
                pos = 0;
            else if(c == '\t')
                while(tabpos(pos,tab) != YES)
                    ++pos;
        }
}

void settab(int argc,char *argv[],char *tab){
    int i,inc,pos;
    if(argc <= 1)
        for(i = 1;i <= MAXLINE;i++)
            if(i%TABSPACE == 0)
                tab[i] = YES;
            else
                tab[i] = NO;
    else if(argc == 3 && *argv[1] == '-' && argv[2] == '+'){
        pos = atoi(&(*++argv)[1]);//将pos设置为第一个制表符停止位的位置
        inc = atoi(&(*++argv)[1]);//inc设置为制表符停止位递增值
        for(i = 1;i <= MAXLINE;i++)
            if(i != pos)
                tab[i] = NO;
            else{
                tab[i] = YES;
                pos += inc;
            }
    }
    else{
        for(i = 1;i <= MAXLINE;i++)
            tab[i] = NO;
        while(--argc > 0)
            pos = atoi(*++argv);
            if(pos > 0 && pos <= MAXLINE)
                tab[pos] = YES;
    }
}

int tabpos(int pos,char *tab){
    if(pos > MAXLINE)
        return YES;
    else
        return tab[pos];
}

void detab(char *tab){
    int c,pos = 1;
    while((c = getchar()) != EOF)
        if(c == '\t'){
            do
                putchar(' ');
            while(tabpos(pos++,tab) != YES);
        }
        else if(c == '\n'){
            putchar(c);
            pos = 1;
        }
        else{
            putchar(c);
            ++pos;
        }
}
