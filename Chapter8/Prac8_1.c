#include <stdio.h>
#include <fcntl.h>
#include "syscalls.h"

/*
用read、write、open和close系统调用代替标准库中等价的函数
重写第7章的cat程序，比较两个版本的相对执行速度
*/

void filecopy(int ifd,int ofd);

int main(int argc, char const *argv[])
{
    int fd;
    if(argc == 1)
        filecopy(0,1);
    else
        while(--argc > 0)
            if((fd = open(*++argv,O_RDONLY)) == -1)
                error("cat:can't open %s",*argv);
            else{
                filecopy(fd,1);
                close(fd);
            }
    return 0;
}

void filecopy(int ifd,int ofd){
    int n;
    char buf[BUFSIZ];
    while((n = read(ifd,buf,BUFSIZ)) > 0)
        if(write(ofd,buf,n) != n)
            error("cat:write error");
}
//使用系统调用速度较快