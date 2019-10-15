#include<bits/stdc++.h>
#include<random>
using namespace std;

#define N 10
int k[N][N];
vector<char> v;

void func(char ch, char p, vector<char> &bb, int l)
{
    for(int i = 0; i < l; i++)
    {
        if(k[ch-'A'][i] == 1 && v[i] != p)
        {
            bb.push_back(v[i]);
            func(v[i], ch, bb, l);
        }
        if(k[ch-'A'][i] == 1 && v[i] == p)
        {
            bb.push_back('|');
        }
    }
}

void print(vector<char> bb)
{
    for(int i = 0; i < bb.size(); i++)
        cout<<bb[i]<<" ";
}

int main()
{
    int n;
    string file;
    cout<<"Enter input file name : ";
    cin>>file;
    cout<<"Enter number of nodes : ";
    cin>>n;
    // int k[n][n];
    int l = n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            k[i][j] = 0;
    ifstream in(file.c_str());
    char a, b;
    while(in)
    {
        if(n == 0)
            break;
        in>>a;
        v.push_back(a);
        n--;
    }
    vector<pair<char, char> >vv;
    while(in)
    {
        in>>a>>b;
        vv.push_back(make_pair(a, b));
    }

    for(int i = 0; i < v.size(); i++)
    {
        k[vv[i].first-'A'][vv[i].second-'A'] = 1;
        k[vv[i].second-'A'][vv[i].first-'A'] = 1;
    }
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < l; j++)
        {
            cout<<k[i][j]<<"\t";
        }
        cout<<"\n";
    }

    for(int i = 0; i < l; i++)
    {
        vector<char> bb;
        func(v[i], ' ', bb, l);
        cout<<v[i]<<" -> ";
        print(bb);
        cout<<"\n";
    }


    return 0;
}