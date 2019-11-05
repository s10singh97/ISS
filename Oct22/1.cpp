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

bool check_irp(int *a)
{
    for(int i = 8; i < 16; i++)
        if(a[i] == 1)
            return true;
    return false;
}

int* multiply(int *a, int *b)
{
    int *c = new int[16];
    memset(c, 0, 16*sizeof(int));
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            c[i+j] += a[i]*b[j];
        }
    }
    for(int i = 0; i < 16; i++)
        c[i] %= 2;

    return c;
}

void divide(int *c, int *b)
{
    int q[8] = {0};
    int r[8] = {0};
    while(check_irp(c))
    {
        for(int i = 15; i >= 0; i--)
        {
            if(c[i] == 1)
            {
                if(i >= 8)
                {
                    q[i-8] = 1;
                    int *qq = new int[8];
                    memset(qq, 0, 8*sizeof(int));
                    qq[i-8] = 1;
                    int *temp = multiply(c, qq);
                }
            }
        }
    }
}

void print8(int *a)
{
    for(int i = 0; i < 8; i++)
        cout<<a[i]<<"\t";
    cout<<"\n";
}

void print16(int *a)
{
    for(int i = 0; i < 16; i++)
        cout<<a[i]<<"\t";
    cout<<"\n";
}

int main()
{
    int *a = represent2p();
    print8(a);
    int *b = represent2p();
    print8(b);
    int *c = add(a, b);
    print8(c);
    int *d = multiply(a, b);
    print16(d);
    int irp[16] = {1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    divide(d, irp);
    return 0;
}