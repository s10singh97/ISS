// Hill cipher

#include<bits/stdc++.h>
using namespace std;

int** multiply(int m1, int m2, int mat1[][2], int n1, int n2, int mat2[][2]) 
{ 
    int x, i, j;
    int **res = new int *[m1];
    for (i = 0; i < m1; i++)  
    { 
        res[i] = new int [n2];
        for (j = 0; j < n2; j++)  
        { 
            res[i][j] = 0; 
            for (x = 0; x < m2; x++)  
            { 
                *(*(res + i) + j) += *(*(mat1 + i) + x) * *(*(mat2 + x) + j); 
            } 
        } 
    }
    return res;
} 

void print(int m1, int m2, int **res)
{
    for(int i = 0; i < m1; i++)
    {
        for(int j = 0; j < m2; j++)
            cout<<res[i][j]<<" ";
        cout<<"\n";
    }
}

int **mmod(int m1, int m2, int **ct)
{
    for(int i = 0; i < m1; i++)
        for(int j = 0; j < m2 ; j++)
            ct[i][j] = ct[i][j] % 26;
    return ct;
}

void p_to_c(string file, string ofile, int key[2][2])
{
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    string a;
    if(a.length() % 2 != 0)
        a.push_back('x');
    while(!ip.eof())
        getline(ip, a);
    int pt[1][2];
    string res;
    for(int i = 0; i < a.length(); i += 2)
    {
        pt[0][0] = int(a[i]-'a');
        pt[0][1] = int(a[i+1]-'a');
        int **ct = multiply(1, 2, pt, 2, 2, key);
        ct = mmod(1, 2, ct);
        for(int i = 0; i < 2; i++)
            res.push_back(char(toupper('a'+ct[0][i])));
    }
    of<<res;
}

int det_k(int mat[2][2], int n)   
{   
    int num1,num2,det = 1,index,total = 1; 
    int temp[n + 1]; 
    for(int i = 0; i < n; i++)    
    {  
        index = i;
        while(mat[index][i] == 0 && index < n)
            index++;       
        if(index == n)   
            continue;
        if(index != i)   
        {   
            for(int j = 0; j < n; j++)
                swap(mat[index][j],mat[i][j]);      
            det = det*pow(-1,index-i);     
        }   
           
        for(int j = 0; j < n; j++)   
           temp[j] = mat[i][j];   
               
        
        for(int j = i+1; j < n; j++)   
        {   
            num1 = temp[i];  
            num2 = mat[j][i];      
            for(int k = 0; k < n; k++)   
                mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);      
            total = total * num1;   
        }        
    }
    for(int i = 0; i < n; i++)
        det = det * mat[i][i];     
    return (det/total);  
}   

int det_inverse(int det)
{
    int inv = det % 26;
    if(inv < 0)
        inv = 26+inv;

    int i = 1;
    while((inv*i) % 26 != 1)    
    {
        i++;
        if(i >= 26)
        {
            cout<<"Wrong key!!\nExitting\n";
            exit(1);
        }
    }
    return i;
}

void getCofactor(int A[2][2], int temp[2][2], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int determinant(int A[2][2], int n) 
{ 
    int D = 0;
    if (n == 1) 
        return A[0][0]; 
  
    int temp[2][2];
  
    int sign = 1;
    for (int f = 0; f < n; f++) 
    { 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
        sign = -sign; 
    } 
  
    return D; 
} 

void adjoint(int A[2][2],int adj[2][2]) 
{ 
    int N = 2;
    if (N == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1, temp[2][2]; 
  
    for (int i=0; i<N; i++) 
    { 
        for (int j=0; j<N; j++) 
        { 
            getCofactor(A, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1)); 
        } 
    } 
} 

void pp(int a[2][2], int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            cout<<a[i][j]<<" ";
        cout<<"\n";
    }
}

void mmmod(int adj[2][2], int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            adj[i][j] = adj[i][j] % 26;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(adj[i][j] < 0)
            {
                adj[i][j] += 26;
            }
        }
    }
}

void c_to_p(string file, string ofile, int key[2][2])
{
    int key_final[2][2];
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            key_final[i][j] = key[i][j];
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    
    int det = det_k(key, 2);
    int det_inv = det_inverse(det);
    int adj[2][2];
    adjoint(key_final, adj);
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            adj[i][j] = det_inv*adj[i][j];
    mmmod(adj, 2, 2);

    int ct[1][2];
    string res;
    for(int i = 0; i < a.length(); i += 2)
    {
        ct[0][0] = int(a[i]-'A');
        ct[0][1] = int(a[i+1]-'A');
        int **pt = multiply(1, 2, ct, 2, 2, adj);
        pt = mmod(1, 2, pt);
        for(int i = 0; i < 2; i++)
            res.push_back(char('a'+pt[0][i]));
    }
    of<<res;
}

int main()
{
    cout<<"Enter Key: ";
    int key[2][2];
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            cin>>key[i][j];
    cout<<"Choose the following: \n1. Encrypt a file\n2. Decrypt a file\n";
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
                    p_to_c(file, ofile, key);
                    break;

            case 2: cout<<"name the file to decrpyt: ";
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