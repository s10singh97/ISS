// Caesar cipher

#include<bits/stdc++.h>
using namespace std;

void p_to_caesar(string file, string ofile, int k)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());

    while(!ip.eof())
    {
        char a[1000];
        ip.getline(a, 1000);

        for(int i = 0; i < 1000; i++)
        {
            if(a[i] >= 'a' && a[i] <= 'z')
            {
                a[i] += k % 26;
                if(a[i] > 'z')
                    a[i] = a[i]-'z'+'a'-1;
                a[i] =  toupper(a[i]);
            }
        }
        of<<a;
        of<<endl;
    }
}

void caesar_to_k(string file, string ofile, int k)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());

    while(!ip.eof())
    {
        char a[1000];
        ip.getline(a, 1000);

        for(int i = 0; i < 1000; i++)
        {
            if(a[i] >= 'A' && a[i] <= 'Z')
            {
                a[i] -= k % 26;
                if(a[i] < 'A')
                    a[i] = a[i]-'A'+'Z'+1;
                tolower(a[i]);
            }
        }
        of<<a;
        of<<endl;
    }
}

int main()
{
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n";
    int ch;
    cin>>ch;
    int k;
    string ofile, file;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: cout<<"Enter key: ";
                    cin>>k;
                    cout<<"name the file to encrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    p_to_caesar(file, ofile, k);
                    break;

            case 2: cout<<"Enter key: ";
                    cin>>k;
                    cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    caesar_to_k(file, ofile, k);
                    break;

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(ch == 'y');
    return 0;
}