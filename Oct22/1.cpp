// Construct S-BOX and INV S-BOX of AES

#include<bits/stdc++.h>
using namespace std;

int *represent2p()
{
    int *a = new int[8];
    for(int i = 0; i < 8; i++)
    {
        int b;
        cout<<"Enter coefficient of x^"<<i<<" : ";
        cin>>b;
        a[i] = b % 2;
    }
    return a;
}

int degreeof(int *p,int deg)
{
    for(int i=deg;i>=0;i--)
    {
        if(p[i]==1)
            return i;
    }
    return -1;
}

int* add(int *a, int *b)
{
    int *c = new int[8];
    for(int i = 0; i < 8; i++)
        c[i] = a[i] ^ b[i];
    return c;
}

void sub(int *a1,int *a2,int *res)
{
    for(int i = 0; i < 8; i++)
    {
        res[i] = a1[i] - a2[i];
        res[i] = abs(res[i]) % 2;
    }
}

// bool check_irp(int *a)
// {
//     for(int i = 8; i < 16; i++)
//         if(a[i] == 1)
//             return true;
//     return false;
// }

void findrem(int *ar1,int d1,int *ar2,int d2,int *res,int *quo)
{
    d1++;
    int *aa = new int[d1];
    d1--;
    for(int i = 0; i <= d1; i++)
        aa[i] = abs(ar1[i] % 2);
    int q = d1-d2;
    for(int i = 0;i <= q; i++)
        quo[i] = 0;
    do
    {
        q = degreeof(aa, d1) - d2;
        quo[q] = 1;
        for(int j = d2; j >= 0; j--)
        {
            aa[q+j] -= ar2[j];
            aa[q+j] = abs(aa[q+j])%2;
        }
    }while(degreeof(aa, d1) >= d2);
    for(int i = 0; i <= d1; i++)
        res[i] = aa[i];
}

void irp(int *ar, int deg, int *res)
{
    int *rp;
    rp = new int[9];
    for(int i = 0; i <= 8; i++)
        rp[i] = 0;
    rp[8]=1;
    rp[4]=1;
    rp[3]=1;
    rp[1]=1;
    rp[0]=1;
    int q = deg-8;
    q++;
    int *quo = new int[q];
    q--;
    findrem(ar, deg, rp, 8, res, quo);
}

void multiply(int *a1,int *a2,int *res)
{
    int rd = degreeof(a1, 8) + degreeof(a2, 8);
    if(rd <= 7)
    {
        for(int i = 0; i <= degreeof(a1, 8); i++)
        {
            for(int j = 0; j <= degreeof(a2, 8); j++)
            {
                res[i+j] += a1[i] * a2[j];
            }
        }
        for(int i=8;i>=0;i--)
            res[i]=abs(res[i]%2);
    }
    else
    {
        rd++;
        int *r = new int[rd];
        rd--;
        for(int i = 0; i <= rd; i++)
            r[i] = 0;
        for(int i = 0; i <= degreeof(a1, 8); i++)
        {
            for(int j = 0; j <= degreeof(a2, 8); j++)
            {
                r[i+j] += a1[i] * a2[j];
            }
        }
        for(int i = rd; i >= 0; i--)
            r[i] = abs(r[i] % 2);
        irp(r, rd, res);
    }
}

// void divide(int *c, int *b)
// {
//     int q[8] = {0};
//     int r[8] = {0};
//     while(check_irp(c))
//     {
//         for(int i = 15; i >= 0; i--)
//         {
//             if(c[i] == 1)
//             {
//                 if(i >= 8)
//                 {
//                     q[i-8] = 1;
//                     int *qq = new int[8];
//                     memset(qq, 0, 8*sizeof(int));
//                     qq[i-8] = 1;
//                     int *temp = multiply(c, qq);
//                 }
//             }
//         }
//     }
// }

void multiinv(int *a1,int *inv)
{
    int *rp;
    rp = new int[9];
    for(int i = 0; i <= 9; i++)
        rp[i] = 0;
    rp[8] = 1;
    rp[4] = 1;
    rp[3] = 1;
    rp[1] = 1;
    rp[0] = 1;
    int *vm,*wm,*vz,*wz,*q,*rem,*vv,*ww,*r1,*r2;
    vm = new int[9]; // v-1
    vv = new int[9]; // v
    ww = new int[9]; // w
    wm = new int[9]; // w-1
    vz = new int[9]; // v0
    wz = new int[9]; // w0
    q = new int[9];
    rem = new int[9];
    r1 = new int[9];
    r2 = new int[9];
    for(int i = 0; i <= 8; i++)
    {
        vm[i]=0;
        wm[i]=0;
        vz[i]=0;
        wz[i]=0;
        q[i]=0;
        rem[i]=0;
        vv[i]=0;
        ww[i]=0;
        r1[i]=0;
        r2[i]=0;
    }
    vm[0]=1;
    wz[0]=1;
    do
    {
        findrem(rp, degreeof(rp,8), a1, degreeof(a1,8), rem, q);
        multiply(q, vz, r1);
        multiply(q, wz, r2);
        sub(vm, r1, vv);
        sub(wm, r2, ww);
        for(int i = 0; i <= 8; i++)
        {
            vm[i]=vz[i];
            vz[i]=vv[i];
            wm[i]=wz[i];
            wz[i]=ww[i];
        }
        for(int i = 0; i <= 8; i++)
        {
            rp[i] = a1[i];
            a1[i] = rem[i];
        }
        for(int i = 0;i <= 8; i++)
        {
            q[i] = 0;
            rem[i] = 0;
            r1[i] = 0;
            r2[i] = 0;
        }
    }while(degreeof(a1,8)!=0);
    for(int i = 8; i >= 0; i--)
        inv[i] = ww[i];
}

void print8(int *a)
{
    for(int i = 0; i < 8; i++)
        cout<<a[i]<<"\t";
    cout<<"\n";
}

void print16(int *a)
{
    for(int i = 0; i < 16; i++)
        cout<<a[i]<<"\t";
    cout<<"\n";
}

string hextobin(string in)
{
    string res="";
    for(int i=0;i<in.length();i++)
    {
        char q=in[i];
        if(q=='0')
            res=res+"0000";
        else if(q=='1')
            res=res+"0001";
        else if(q=='2')
            res=res+"0010";
        else if(q=='3')
            res=res+"0011";
        else if(q=='4')
            res=res+"0100";
        else if(q=='5')
            res=res+"0101";
        else if(q=='6')
            res=res+"0110";
        else if(q=='7')
            res=res+"0111";
        else if(q=='8')
            res=res+"1000";
        else if(q=='9')
            res=res+"1001";
        else if(q=='A')
            res=res+"1010";
        else if(q=='B')
            res=res+"1011";
        else if(q=='C')
            res=res+"1100";
        else if(q=='D')
            res=res+"1101";
        else if(q=='E')
            res=res+"1110";
        else if(q=='F')
            res=res+"1111";
    }
    return res;
}

string bintohex(string in)
{
    string res="";
    for(int i=0;i<in.length();i=i+4)
    {
        string q=in.substr(i,4);
        if(q=="0000")
            res=res+'0';
        else if(q=="0001")
            res=res+'1';
        else if(q=="0010")
            res=res+'2';
        else if(q=="0011")
            res=res+'3';
        else if(q=="0100")
            res=res+'4';
        else if(q=="0101")
            res=res+'5';
        else if(q=="0110")
            res=res+'6';
        else if(q=="0111")
            res=res+'7';
        else if(q=="1000")
            res=res+'8';
        else if(q=="1001")
            res=res+'9';
        else if(q=="1010")
            res=res+'A';
        else if(q=="1011")
            res=res+'B';
        else if(q=="1100")
            res=res+'C';
        else if(q=="1101")
            res=res+'D';
        else if(q=="1110")
            res=res+'E';
        else if(q=="1111")
            res=res+'F';
    }
    return res;
}

// int main()
// {
//     int *a = represent2p();
//     print8(a);
//     int *b = represent2p();
//     print8(b);
//     int *c = add(a, b);
//     print8(c);
//     int *d = new int[9];
//     multiply(a, b, d);
//     for(int i = 0; i < 9; i++)
//         cout<<d[i]<<" ";
//     cout<<"\n";
//     // int irp[16] = {1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
//     // divide(d, irp);
//     return 0;
// }

string getString(char a)
{
    string s(1,a);
    return s;
}

int main()
{
    int deg;
    int *p1=new int[9];
    int *p2=new int[9];
    int *res=new int[9];
    int *inv=new int[9];
    for(int i=0;i<=8;i++)
    {
        p1[i]=0;
        inv[i]=0;
    }
    string sbox[16][16];
    string ssbox[16][16];
    char a,b;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(i>=10)
                a=char(55+i);
            else
                a=char(i+48);
            if(j>=10)
                b=char(55+j);
            else
                b=char(j+48);
            sbox[i][j]=getString(a)+getString(b);
            ssbox[i][j]=sbox[i][j];
        }
    }
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(i==0 && j==0)
            {
             sbox[i][j]="00";
             continue;
            }
            string s;
            s=hextobin(sbox[i][j]);
            p1[8]=0;
            for(int k=0;k<s.length();k++)
            {
                if(s[k]=='0')
                    p1[7-k]=0;
                else
                    p1[7-k]=1;
            }
            if(sbox[i][j]=="01")
            {
                sbox[i][j]="01";
                continue;
            }
            multiinv(p1,inv);
            inv[8]=0;
            string ss="";
            for(int k=7;k>=0;k--)
            {
                if(inv[k]==0)
                    ss=ss+"0";
                else
                    ss=ss+"1";
            }
            sbox[i][j]=bintohex(ss);
            for(int i=0;i<=7;i++)
            {
                p1[i]=0;
                inv[i]=0;
            }
        }
    }
    int cc[8];
    cc[0]=1;
    cc[1]=1;
    cc[2]=0;
    cc[3]=0;
    cc[4]=0;
    cc[5]=1;
    cc[6]=1;
    cc[7]=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            string aa=hextobin(sbox[i][j]);
            int bb[8];
            int rr[8];
            for(int i=0;i<=7;i++)
            {
                if(aa[i]=='0')
                    bb[7-i]=0;
                else
                    bb[7-i]=1;
            }
            for(int i=0;i<=7;i++)
            {
                rr[i]=bb[i]^bb[(i+4)%8]^bb[(i+5)%8]^bb[(i+6)%8]^bb[(i+7)%8]^cc[i];
                if(rr[i]>0)
                    rr[i]=1;
            }
            string ss;
            ss="";
            for(int i=7;i>=0;i--)
            {
                if(rr[i]==1)
                    ss=ss+"1";
                else
                    ss=ss+"0";
            }
            sbox[i][j]=bintohex(ss);
        }
    }
    // Print S-BOX
    cout<<"S - BOX\n";
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            cout<<sbox[i][j]<<" ";
        }
        cout<<"\n";
    }
    string invsbox[16][16];
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(i>=10)
                a=char(55+i);
            else
                a=char(i+48);
            if(j>=10)
                b=char(55+j);
            else
                b=char(j+48);
            invsbox[i][j]=getString(a)+getString(b);
        }
    }
    int dd[8];
    dd[0]=1;
    dd[1]=0;
    dd[2]=1;
    dd[3]=0;
    dd[4]=0;
    dd[5]=0;
    dd[6]=0;
    dd[7]=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            string aa=hextobin(invsbox[i][j]);
            int bb[8];
            int rr[8];
            for(int i=0;i<=7;i++)
            {
                if(aa[i]=='0')
                    bb[7-i]=0;
                else
                    bb[7-i]=1;
            }
            for(int i=0;i<=7;i++)
            {
                rr[i]=bb[(i+2)%8]^bb[(i+5)%8]^bb[(i+7)%8]^dd[i];
                if(rr[i]>0)
                    rr[i]=1;
            }
            string ss;
            ss="";
            for(int i=7;i>=0;i--)
            {
                if(rr[i]==1)
                    ss=ss+"1";
                else
                    ss=ss+"0";
            }
            invsbox[i][j] = bintohex(ss);
        }
    }
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(invsbox[i][j] == "00")
            {
                invsbox[i][j] = "00";
                continue;
            }
            string s;
            s = hextobin(invsbox[i][j]);
            p1[8] = 0;
            for(int k = 0; k < s.length(); k++)
            {
                if(s[k] == '0')
                    p1[7 - k] = 0;
                else
                    p1[7 - k] = 1;
            }
            if(invsbox[i][j]=="01")
            {
                invsbox[i][j]="01";
                continue;
            }
            multiinv(p1,inv);
            inv[8]=0;
            string ss="";
            for(int k=7;k>=0;k--)
            {
                if(inv[k]==0)
                    ss=ss+"0";
                else
                    ss=ss+"1";
            }
            invsbox[i][j]=bintohex(ss);
            for(int i=0;i<=7;i++)
            {
                p1[i]=0;
                inv[i]=0;
            }
        }
    }
    cout<<"\n";
    cout<<"\nInverse S - BOX\n";
    // Print Inv S-Box
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            cout<<invsbox[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}