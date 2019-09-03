// Playfair

#include<bits/stdc++.h>
using namespace std;
#define N 5


void print(char mat[N][N], int r, int s)
{
    for(int r = 0; r < 5; r++)
    {
        for(int s = 0; s < 5; s++)
        {
            cout<<mat[r][s]<<"\t";
        }
        cout<<"\n";
    }
}

int cc(string kk)
{
    int count = 1, flag = 0;
    for(int i = 1; i < kk.length(); i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(kk[i] == kk[j])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            count++;
    }
    return count;
}

string search(char a, char b, char mat[N][N])
{
    int xa, xb, ya, yb;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(mat[i][j] == a)
            {
                xa = i; ya = j;
            }
            if(mat[i][j] == b)
            {
                xb = i; yb = j;
            }
        }
    }
    string res;
    if(xa == xb)
    {
        char p1 = mat[xa][(ya+1)%N];
        char p2 = mat[xb][(yb+1)%N];
        res.push_back(toupper(p1));
        res.push_back(toupper(p2));
        return res;
    }
    else if(ya == yb)
    {
        char p1 = mat[(xa+1)%N][ya];
        char p2 = mat[(xb+1)%N][yb];
        res.push_back(toupper(p1));
        res.push_back(toupper(p2));
        return res;
    }
    else
    {
        char p1 = mat[xa][yb];
        char p2 = mat[xb][ya];
        res.push_back(toupper(p1));
        res.push_back(toupper(p2));
        return res;
    }
}

void pl_encrypt(char mat[N][N], ofstream *of, string a)
{
    int count = 0; 
    for (int i = 0; i < a.length(); i++) 
        if (a[i] != ' ' || a[i] != '.') 
            a[count++] = a[i]; 
    a[count] = '\0'; 
    

    if(a.length() % 2 != 0)
        a.push_back('x');
    string res;
    for(int i = 0; i < a.length()-1; i += 2)
    {
        string p1 = search(a[i], a[i+1], mat);
        *of<<p1;
    }
}

void p_to_c(string file, string ofile, string key)
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
    char mat[N][N];
    int count = cc(kk);
    
    bool vis[26] = {false};
    int i = 0, j = 0;
    for(int l = 0; l < count; l++)
    {
        if(vis[kk[l]-'A'] == false)
        {
            mat[i][j] = kk[l];
            vis[kk[l]-'A'] = true;
            j++;
            if(j % 5 == 0)
            {
                i++;
                j = 0;
            }
        }
    }
    
    for(int l = 0; l < 26; l++)
    {
        if(vis[l] == false)
        {
            if('A'+ l == 'J')
                continue;
            mat[i][j] = char('A'+ l);
            vis[l] = true;
            j++;
            if(j % 5 == 0)
            {
                i++;
                j = 0;
            }
        }
    }
    
    print(mat, 5 ,5);

    pl_encrypt(mat, &of, a);

}

void c_to_p(string file, string ofile, string key)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    ifstream k(key.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    
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