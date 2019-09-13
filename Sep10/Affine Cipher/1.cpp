// Affine Cipher

#include<bits/stdc++.h>
using namespace std;

int a_inverse(int a)
{
    for(int i = 1; i < 26; i++)
        if((a*i) % 26 == 1)
            return i;
    return -1;
}

bool check_a(int a)
{
    if((a % 2) == 0 || a == 13)
        return false;
    return true;
}

void p_to_c(string file, string ofile, int a, int b)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());

    string ip_s;
    while(!ip.eof())
        getline(ip, ip_s);

    string res;
    for(int i = 0; i < ip_s.length(); i++)
    {
        if(isalpha(ip_s[i]))
        {
            res.push_back(toupper(((a*(ip_s[i]-'a') + b) % 26) + 'a'));
        }
        else
            res.push_back(ip_s[i]);
    }
    of<<res;
}

void c_to_p(string file, string ofile, int a, int b)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    string ip_s;
    while(!ip.eof())
        getline(ip, ip_s);

    string res;
    int a_inv = a_inverse(a);
    for(int i = 0; i < ip_s.length(); i++)
    {
        if(isalpha(ip_s[i]))
        {
            int m1 = (ip_s[i]-b-'A') % 26;
            if(m1 < 0)
                m1 += 26;
            res.push_back(tolower((a_inv*m1) % 26)+'a');
        }
        else
            res.push_back(ip_s[i]);
    }
    of<<res;
}

int main()
{
    int a, b;
    cout<<"Enter a and b of Affine Cipher: ";
    cin>>a>>b;
    if(!check_a(a))
    {
        cout<<"Invalid Key!!\nExitting...\n";
        exit(0);
    }
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n3. Exit\n";
    int ch;
    cin>>ch;
    string ofile, file;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: cout<<"name the file to encrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    p_to_c(file, ofile, a, b);
                    break;

            case 2: cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    c_to_p(file, ofile, a, b);
                    break;

            case 3: cout<<"Exitting\n";
                    exit(0);

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
        cin>>c;
    }while(ch == 'y' || ch == 'Y');
    return 0;
}