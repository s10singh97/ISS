// Rail Fence

#include<bits/stdc++.h>
using namespace std;
#define N 10

bool isValid(string key)
{
    sort(key.begin(), key.end());
    for(int i = 0; i < key.length(); i++)
    {
        if(key[i] != '1'+i)
            return false;
    }
    return true;
}

void print(char **mat, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            cout<<mat[i][j]<<"\t";
        cout<<"\n";
    }
}

string removespace(string a)
{
    string b;
    for(int i = 0; i < a.length(); i++)
        if(isalpha(a[i]))
            b.push_back(a[i]);
    return b;
}

void p_to_c(string file, string ofile, string key)
{
    if(!isValid(key))
    {
        cout<<"Invalid Key !\nExitting";
        exit(1);
    }
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    
    string a_mod = removespace(a);
    char **mat = new char *[key.length()];
    int i = 0, k = 0;
    int a_l = ceil((float)a_mod.length()/key.length());
    while(i < a_l)    
    {
        mat[i] = new char [key.length()];
        for(int j = 0; j < key.length(); j++)
        {
            if(k < a_mod.length())
                mat[i][j] = a_mod[k++];
            else
                mat[i][j] = char('a'+ (k++ % 26));
        }
        i++;
    }
    // print(mat, i, key.length());

    string res;
    k = 0;
    while(k != key.length())
    {
        int temp = 0;
        while(k != key[temp]-'0'-1)
            temp++;
        for(i = 0; i < a_l; i++)
        {
            res.push_back(toupper(mat[i][temp]));
        }
        k++;
    }
    of<<res;
}

void c_to_p(string file, string ofile, string key)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    
    char **mat = new char *[key.length()];
    int i = 0, k = 0;
    int a_l = ceil((float)a.length()/key.length());
    while(i < key.length())    
    {
        mat[i] = new char [a_l];
        for(int j = 0; j < a_l; j++)
        {
            if(k < a.length())
                mat[i][j] = tolower(a[k++]);
            else
                mat[i][j] = char('a'+ (k++ % 26));
        }
        i++;
    }
    // print(mat, i, a_l);

    string res;
    k = 0, i = 0; int j = 0;
    while(j != a_l)
    {
        for(i = 0; i < key.length(); i++)
            res.push_back(mat[key[i]-'0'-1][j]);
        j++;
    }
    of<<res;
}

int main()
{
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n";
    int ch;
    cin>>ch;
    string ofile, file;
    string key;
    cout<<"Enter key: ";
    cin>>key;
    string key_dup = key;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: cout<<"name the file to encrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    p_to_c(file, ofile, key);
                    break;

            case 2: cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    c_to_p(file, ofile, key_dup);
                    break;

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(ch == 'y');
    return 0;
}