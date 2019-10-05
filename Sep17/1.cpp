// Letter frequency attack on additive (caesar) cipher

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

void predicting_best_phrase(string ofile)
{
    ifstream of(ofile.c_str());
    vector<string> a;
    while(!of.eof())
    {
        string in;
        getline(of, in);
        a.push_back(in);
    }
    
    vector<string> common;
    ifstream com("common_words.txt");
    if(!com)
    {
        cout<<"Error opening common_words.txt\nExiting..\n";
        exit(0);
    }
    while(!com.eof())
    {
        string in;
        getline(com, in);
        common.push_back(in);
    }
    
    vector<string> token;
    split(token, a);

    vector<string> res;
    for(int i = 0; i < token.size(); i++)
        for(int j = 0; j < common.size(); j++)
            if(token[i].compare(common[j]) == 0)
                res.push_back(token[i]);

    cout<<"10 most predicted words are\n";
    int k = res.size();
    for(int i = 0; i < min(k, 10); i++)
        cout<<res[i]<<"\n";

}

void caesar_to_k(string file, string ofile, int k)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str(), ios_base::app);

    string a;
    while(!ip.eof())
        getline(ip, a);
    for(int i = 0; i < a.length(); i++)
    {
        if(a[i] >= 'A' && a[i] <= 'Z')
        {
            a[i] -= k % 26;
            if(a[i] < 'A')
                a[i] = a[i]-'A'+'Z'+1;
            a[i] = tolower(a[i]);
        }
    }
    of<<a;
    of<<endl;
    of.close();
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
                    for(int i = 1; i < 26; i++)
                        caesar_to_k(file, ofile, i);
                    predicting_best_phrase(ofile);
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