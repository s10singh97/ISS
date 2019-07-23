// Program to demonstrate buffer overflow attack

#include<stdio.h>
// using namespace std;

int main()
{
    int a[5] = {1,1,1,1,1,1};
    for(int i = 0; i < 6; i++)
        printf("%d", a[i]);
    return 0;
}