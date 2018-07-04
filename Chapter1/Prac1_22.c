#include <stdio.h>
/*
编写一个程序，把较长的输入行折成短一些的两行或多行，折行的位置在输入行的第n列之前的
最后一个非空格之后。要保证程序能够智能地处理输入行很长以及在指定的列前没有空格或制表符时的情况
*/

#define TABSPACE 6//制表位大小
#define MAXCOL 20//最长折行

char line[MAXCOL]//输入行
int exptab(int pos);
int findblank(int pos);
int newpos(int pos);
void printl(int pos);

