// Store no. bigger then INT size

#include<stdio.h>
#include<limits.h>
int main()
{
    int a = 8465312084651324587452145785421457865432135689654321454845;
    printf("%d\n%d", a, INT_MAX);
    return 0;
}