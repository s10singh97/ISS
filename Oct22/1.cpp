// Construct S-BOX of AES

#include<bits/stdc++.h>
using namespace std;

int *represent2p()
{
    int *a = new int[8];
    for(int i = 0; i < 8; i++)
    {
        int b;
        cout<<"Enter coefficient of x^"<<i<<" : ";
        cin>>b;
        a[i] = b % 2;
    }
    return a;
}

int* add(int *a, int *b)
{
    int *c = new int[8];
    for(int i = 0; i < 8; i++)
        c[i] = a[i] ^ b[i];
    return c;
}

int* multiply(int *a, int *b)
{
    int *c = new int[14];
    memset(c, 0, sizeof(c));
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            c[i+j] += a[i]*b[j];
        }
    }
    for(int i = 0; i < 14; i++)
        c[i] %= 2;
    
}

int main()
{

    return 0;
}