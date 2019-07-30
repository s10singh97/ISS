// Monoalphabetic cipher

#include<bits/stdc++.h>
using namespace std;

bool isValidKey(string key)
{
    ifstream ip2(key.c_str());
    char a[1000];
    ip2.getline(a, 1000);
    int count = 0, flag = 0, h[26] = {0};
    for(;a[count] != '\0'; count++);
    if(count != 26)
    {
        ip2.close();
        return false;
    }
    for(int i = 0; i < 26; i++)
    {
        if(a[i] < 'a' || a[i] > 'z')
        {
            ip2.close();
            return false;
        }
        else
            h[a[i]-'a']++;
    }
    for(int i = 0; i < 26; i++)
    {
        if(h[i] != 1)
        {
            ip2.close();
            return false;
        }
    }
    ip2.close();
    return true;
}

void p_to_c(string file, string ofile, string key)
{
    if(isValidKey(key) == false)
    {
        cout<<"Invalid Key\nExiting !!\n";
        exit(0);
    }
    ifstream ip(file.c_str());
    ifstream ip2(key.c_str());
    ofstream of(ofile.c_str());

    while(!ip.eof())
    {
        char b[26];
        ip2.getline(b, 26);
        char res[1000];
        char a[1000];
        ip.getline(a, 1000);
        int j = 0;
        for(int i = 0; i < 1000; i++)
        {
            if(a[i] >= 'a' || a[i] <= 'z')
                res[j++] = b[a[i]-'a'-1];
            else
                res[j++] = a[i];
        }
        of<<res;
        of<<endl;
    }
}

void c_to_p(string file, string ofile, string key)
{
    
}

int main()
{
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n";
    int ch;
    cin>>ch;
    string ofile, file, key;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: cout<<"Enter key file name: ";
                    cin>>key;
                    cout<<"name the file to encrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    p_to_c(file, ofile, key);
                    break;

            case 2: cout<<"Enter key file name: ";
                    cin>>key;
                    cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    c_to_p(file, ofile, key);
                    break;

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(ch == 'y');
    return 0;
}