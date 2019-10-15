#include<bits/stdc++.h>
#include<random>
using namespace std;

int main()
{
    int n;
    string file;
    cout<<"Enter input file name : ";
    cin>>file;
    cout<<"Enter number of nodes : ";
    cin>>n;
    int k[n][n] = {0};
    ifstream in(file.c_str());
    char a, b;
    vector<char> v;
    while(in)
    {
        if(n == 0)
            break;
        in>>a;
        v.push_back(a);
        n--;
    }
    // for(int i = 0; i < v.size(); i++)
    //     cout<<v[i]<<" ";
    while(in)
    {
        in>>a>>b;
        k[int(a-'A')][int(b-'A')] = 1;
        k[int(b-'A')][int(a-'A')] = 1;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<k[i][j]<<"\t";
        }
        cout<<"\n";
    }

    // cout<<"\n";
    // vector<string> edge;
    // while(in)
    // {
    //     getline(in, a);
    //     for(int i = 0; i < a.length(); i += 2)
    //     {
    //         if(a[i] == ' ')
    //             continue;
    //         else
    //         {
    //             edge.push_back(""+a[i]+a[i+1]);
    //         }
    //     }
    // }
    // for(int i = 0; i < edge.size(); i++)
    //     cout<<edge[i]<<" ";


    // char ch, a, b;
    // int n;
    // vector<pair<int, int> >v;
    // cout<<"Enter number of nodes : ";
    // cin>>n;
    // cout<<"Enter nodes : ";
    // vector<char> in(n);
    // for(int i = 0; i < n; i++)
    // {
    //     cin>>in[i];
    //     cout<<in[i];
    // }
    // do
    // {
    //     cout<<"Enter graph in as(node node): ";
    //     cin>>a>>b;
    //     v.push_back(make_pair(a, b));
    //     cout<<"do you want to enter more ? [Y/N]";
    //     cin>>ch;
    // }while(ch == 'Y' || ch == 'y');
    
    return 0;
}