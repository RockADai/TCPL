/*
考虑isupper节省空间或时间的实现方式
*/

int isupper(char c){
    if(c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}//省空间

#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0
//省时间

/*
int isupper(char c){
    return ((c) >= 'A' && (c) <= 'Z') ? 1 : 0
}
*/