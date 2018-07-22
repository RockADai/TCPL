#include <stdio.h>
#include <stdlib.h>

/*
编写一个计算器程序，使用逆波兰表示法（所有运算符都跟在操作数后面，如(1-2)*(4+5)输入为12-45+*）
目前的练习中不分割文件，所以代码较长
第四章习题3-11都写在此文件中
*/

#define MAXVAL 100//栈val的最大深度
#define MAXOP //操作数或运算符最大长度
#define NUMBER '0'//标志找到一个数

int getop(char s[]);//获取下一个运算符或操作数
void push(double f);//将f压入栈
double pop();//弹出并返回栈顶值