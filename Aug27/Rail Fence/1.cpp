// Rail Fence

#include<bits/stdc++.h>
using namespace std;
#define N 10

bool isValid(string key)
{
    sort(key.begin(), key.end());
    for(int i = 0; i < key.length(); i++)
    {
        if(key[i] != '0'+i)
            return false;
    }
    return true;
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
    
    string res;

    for(int i = 0, j = 0; i < a.length(); i++)
    {
        
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
    string kk;
    
    string res;
    for(int i = 0, j = 0; i < a.length(); i++)
    {
        
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