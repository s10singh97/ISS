// Deffie_Hellman

#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool isprime(int a)
{
    if (a == 2)
        return true;
    for(int i = 2; i <= sqrt(a); i++)
    {
        if(a % i == 0)
            return false;        
    }
    return true;
}

vector<int> generate_prime()
{
    vector<int> v;
    int i = 2;
    while(v.size() != 100)
    {
        if(isprime(i))
            v.push_back(i);
        i++;
    }
    return v;
}

long long poww(long long t, int e, int n)
{
    if(e == 1)
        return t;
    return (t*poww(t, e-1, n))%n;
}

bool check(vector<int> v, int q)
{
    for(int i = 0; i < q-1; i++)
        if(v[i] != i+1)
            return false;
    return true;    
}

int primeRoot(int q)
{
    for(int i = 1; i < q; i++)
    {
        vector<int> v;
        for(int j = 1; j < q; j++)
        {
            v.push_back(poww(i, j, q) % q);
        }
        sort(v.begin(), v.end());
        if(check(v, q))
            return i;
    }
}

void key_gen()
{
    vector<int> v = generate_prime();
    int ind = rand() % 100;
    int q = v[ind];
    int alpha = primeRoot(q);
    int xa = 2 + (rand() % (q-1));
    int xb = 2 + (rand() % (q-1));
    int ya = poww(alpha, xa, q) % q;
    int yb = poww(alpha, xb, q) % q;
    int ka = poww(yb, xa, q) % q;
    int kb = poww(ya, xb, q) % q;
    cout<<"q : "<<q<<"\nalpha : "<<alpha<<"\nxa : "<<xa<<"\nxb : "<<xb<<"\nya : "<<ya<<"\nyb : "<<yb<<"\nka : "<<ka<<"\nkb : "<<kb<<"\n";
}

int main()
{
    srand(time(NULL));
    char c = 'y';
    do
    {
        cout<<"Choose the following: \n1. Key Generation\n2. Exit\n";
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1: key_gen();
                    break;
            
            case 2: cout<<"\nExitting..";
                    exit(0);

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(c == 'y');
    return 0;
}