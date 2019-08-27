// One Time Pad

#include<bits/stdc++.h>
#include<random>
using namespace std;

string key_gen(int len)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 25); // define the range
    
    string key;
    for(int i = 0; i < len; i++)
        key.push_back(distr(eng)+'a'); // generate numbers

    return key;
}

void p_to_c(string file, string ofile, string key)
{
    ifstream ip(file.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    
    ofstream of(ofile.c_str());
    
    ofstream key_create(key.c_str());
    string enter_key = key_gen(a.length());
    key_create<<enter_key;
    key_create.close();

    ifstream key_fin(key.c_str());
    string kk;
    while(!key_fin.eof())
        getline(key_fin, kk);
    string res;
    for(int i = 0, j = 0; i < a.length(); i++)
    {
        if(a[i] >= 'a' && a[i] <= 'z')
        {
            res.push_back((((a[i]-'a') + (kk[(j++) % kk.length()] - 'a')) % 26) + 'A');
        }
        else
            res.push_back(a[i]);
    }
    of<<res;
}

void c_to_p(string file, string ofile, string key)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    ifstream k(key.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    string kk;
    while(!k.eof())
        getline(k, kk);
    string res;
    for(int i = 0, j = 0; i < a.length(); i++)
    {
        if(a[i] >= 'A' && a[i] <= 'Z')
        {
            int ind = ((a[i] - 'A') + (kk[(j++) % kk.length()] - 'a'));
            if(ind < 0)
                ind = ind + 26;
            res.push_back((ind % 26) + 'a');
        }
        else
            res.push_back(a[i]);
    }
    of<<res;
}

int main()
{
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n";
    int ch;
    cin>>ch;
    string ofile, file, key, k;
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