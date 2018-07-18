#include <stdio.h>
/*
重写binsearch()函数，使得在循环内部只执行一次测试，比较两种版本的运行时间。
*/
int binsearch(int x,int v[],int n){
    int low,high,mid;
    low = 0;
    high = n-1;
    mid = (low+high)/2;
    while(low <= high){
        if(x < v[mid])
            high = mid-1;
        else
            low = mid+1;
        mid = (low+high)/2;
    }
    if(x == v[mid])
        return mid;
    else
        return -1;
}