#include <stdio.h>
#include <stdlib.h>

/*
编写程序打印一个文件集合，每个文件从新的一页开始打印，并且打印每个文件相应的标题和页数
*/

#define MAXBOT 3
#define MAXHDR 5
#define MAXLINE 100
#define MAXPAGE 66
void fileprint(FILE *fp,char *fname);
int heading(char *fname,int pageno);

int main(int argc, char const *argv[])
{
    FILE *fp;
    if(argc == 1)
        fileprint(stdin," ");
    else
        while(--argc > 0)
            if((fp = fopen(*++argv,"r")) == NULL){
                fprintf(stderr,"print:can't open %s\n",*argv);
                exit(1);
            }
            else{
                fileprint(fp,*argv);
                fclose(fp);
            }
    return 0;
}

void fileprint(FILE *fp,char *fname){
    int lineno,pageno = 1;
    char line[MAXLINE];
    lineno = heading(fname,pageno++);
    while(fgets(line,MAXLINE,fp) != NULL){
        if(lineno == 1){
            fprintf(stdout,"\f");
            lineno = heading(fname,pageno++);
        }
        fputs(line,stdout);
        if(++lineno > MAXPAGE-MAXBOT)
            lineno = 1;
    }
    fprintf(stdout,"\f");
}

int heading(char *fname,int pageno){
    int ln = 3;
    fprintf(stdout,"\n\n");
    fprintf(stdout,"%s page %d\n",fname,pageno);
    while(ln++ < MAXHDR)
        fprintf(stdout,"\n");
    return ln;
}