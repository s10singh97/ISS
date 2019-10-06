// Frequency attack on additive (caesar) cipher

#include<bits/stdc++.h>
using namespace std;

void print(vector<string> a)
{
    for(int i = 0; i < a.size(); i++)
        cout<<a[i]<<"\n";
}

void split(vector<string> &token, vector<string> a)
{
    for(int i = 0; i < a.size(); i++)
    {
        string word = ""; 
        for (auto x : a[i]) 
        { 
            if (x == ' ') 
            { 
                token.push_back(word); 
                word = ""; 
            } 
            else
                word = word + x;
        }  
        token.push_back(word);
    } 
}

bool comp(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

void caesar_to_k(string file, string ofile)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str(), ios_base::app);

    vector<string> a;
    while(!ip.eof())
    {
        string in;
        getline(ip, in);
        a.push_back(in);
    }
    vector<string> token;
    split(token, a);

    // Frequency chart in descending order
    char dict[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'R',
                   'H', 'D', 'L', 'U', 'C', 'M', 'F', 'Y', 
                   'W', 'G', 'P', 'B', 'V', 'K', 'X', 'Q', 
                   'J', 'Z'};
    map<int, int>m;
    for(int i = 0; i < token.size(); i++)
        for(int j = 0; j < token[i].size(); j++)
            m[toupper(token[i][j])-'A']++;
    
    vector<pair<int, int> > mapcopy(m.begin(), m.end());
    sort(mapcopy.begin(), mapcopy.end(), comp);

    ip.seekg(ios::beg);
    string l;
    while(ip)
    {
        getline(ip, l);
        for(int i = 0; i < l.size(); i++)
        {
            if(isalpha(l[i]))
            {
                for(int j = 0; j < 26; j++)
                {
                    if(l[i] == char(mapcopy[j].first + 'A'))
                    {
                        l[i] = tolower(dict[j]);
                        of<<l[i];
                    }
                }
            }
            else
                of<<l[i];
        }
    }
}

int main()
{
    cout<<"Choose the following: \n1. Decrypt a file\n2. Exit\n";
    int ch;
    cin>>ch;
    int k;
    string ofile, file;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    remove(ofile.c_str());       
                    caesar_to_k(file, ofile);
                    break;

            case 2: cout<<"\nThank You...Exiting...\n";
                    exit(0);

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(ch == 'y');
    return 0;
}