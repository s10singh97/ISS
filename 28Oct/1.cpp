// RSA

#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool isprime(int a)
{
    if (a == 2)
        return true;
    for(int i = 2; i <= sqrt(a); i++)
    {
        if(a % i == 0)
            return false;        
    }
    return true;
}

vector<int> generate_prime()
{
    vector<int> v;
    int i = 2;
    while(v.size() != 100)
    {
        if(isprime(i))
            v.push_back(i);
        i++;
    }
    return v;
}

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

vector<int> e_gen(int phi)
{
    vector<int> v;
    for(int i = 1; i < phi; i++)
    {
        if(gcd(i, phi) == 1)
            v.push_back(i);
    }
    return v;
}

int cal_d(int phi, int e)
{
    for(int i = 1; i < phi; i++)
        if((e*i)%phi == 1)
            return i;
}

pair<pair<int, int>, int> key_gen()
{
    vector<int> v = generate_prime();
    int p, q;
    int ind = rand()%100;
    p = v[ind];
    ind = rand()%100;
    q = v[ind];
    int n = p*q;
    int phi = (p-1)*(q-1);
    vector<int> e_list = e_gen(phi);
    ind = rand() % e_list.size();
    int e = e_list[ind];
    int d = cal_d(phi, e);
    cout<<"\ne"<<" : "<<e;
    cout<<"\nd"<<" : "<<d;
    cout<<"\nn"<<" : "<<n<<"\n";
    return make_pair(make_pair(e, d), n);
}

long long poww(long long t, int e, int n)
{
    if(e == 1)
        return t;
    return (t*poww(t, e-1, n))%n;
}

void p_to_c(string file, string ofile)
{
    pair<pair<int, int>, int>k = key_gen();
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    bool flag = false;
    while(!ip.eof())
    {
        string a;
        ip>>a;
        int b = stoi(a);
        ll c = poww(b, k.first.first, k.second) % k.second;
        if (flag == false)
        {
            of<<c;
            flag = true;
        }
        else
            of<<" "<<c;
    }
}

void c_to_p(string file, string ofile, string key)
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    ifstream k(key.c_str());
    string ee, dd, nn;
    k>>ee; k>>dd; k>>nn;
    int e = stoi(ee); int d = stoi(dd); int n = stoi(nn);
    while(!ip.eof())
    {
        string a;
        ip>>a;
        int b = stoi(a);
        ll c = poww(b, d, n) % n;
        of<<c<<" ";
    }
}

int main()
{
    srand(time(NULL));
    cout<<"Choose the following: \n1. Key Generation\n2. Encrypt a file\n3. Decrypt a file\n4. Exit\n";
    int ch;
    cin>>ch;
    string ofile, file, key;
    char c = 'y';
    do{
        switch(ch)
        {
            case 1: key_gen();
                    break;

            case 2: cout<<"name the file to encrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    p_to_c(file, ofile);
                    break;

            case 3: cout<<"name the key file: ";
                    cin>>key;
                    cout<<"name the file to decrpyt: ";
                    cin>>file;
                    cout<<"name the output file: ";
                    cin>>ofile;
                    c_to_p(file, ofile, key);
                    break;
            
            case 4: cout<<"\nExitting..";
                    exit(0);

            default:cout<<"Enter correct choice\n";
        }
        cout<<"Do you want to try again[y/N]: ";
            cin>>c;
    }while(c == 'y');
    return 0;
}