#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
编写一个程序，根据其自身被调用时存放在argv[0]中的名字，实现将大写字母转换为小写字母
或将小写字母转换为大写字母的功能
*/

int main(int argc, char const *argv[])
{
    int c;
    if(strcmp(argv[0],"lower") == 0)
        while((c = getchar()) != EOF)
            putchar(tolower(c));
    else if(strcmp(argv[0],"upper") == 0)
        while((c = getchar()) != EOF)
            putchar(toupper(c));
    return 0;
}
