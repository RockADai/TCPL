/*
用指针方式代替数组下标方式改写day_of_month和month_day
*/

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year,int month,int day){
    int leap;
    char *p;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    while(--month)
        day = *++p;
    return day;
}

void month_day(int year,int yearday,int *pmonth,int *pday){
    int leap;
    char *p;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    while(yearday > *++p)
        yearday -= *p;
    *pmonth = p-*(daytab+leap);//将当前月份值赋给pmonth所指对象，若该年为闰年则月份-1
    *pday = yearday;
}