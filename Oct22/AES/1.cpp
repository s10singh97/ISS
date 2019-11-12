// AES

#include<bits/stdc++.h>
using namespace std;

string sbox[16][16], c1[4][4], c2[4][4], c3[4][4], invsbox[16][16];

string str(char a)
{
    string s(1, a);
    return s;
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

void sub(int *a1,int *a2,int *res)
{
    for(int i = 0; i < 8; i++)
    {
        res[i] = a1[i] - a2[i];
        res[i] = abs(res[i]) % 2;
    }
}

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

void createSB()
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
            sbox[i][j]=str(a)+str(b);
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
}

void createISB()
{
    int deg;
    int *p1=new int[9];
    int *p2=new int[9];
    int *res=new int[9];
    int *inv=new int[9];
    char a, b;
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
            invsbox[i][j]=str(a)+str(b);
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
}

string xorr(string a, string b)
{
    string res = "";
    a = hextobin(a);
    b = hextobin(b);
    for(int i = 0; i < a.length(); i++)
    {
        if(a[i] == b[i])
            res += '0';
        else
            res += '1';
    }
    res = bintohex(res);
    return res;
}

string g(string a, int round)
{
    vector<string> byt;
    // Converting word to bytes
    for(int i = 0; i < a.size(); i += 2)
        byt.push_back(a.substr(i, 2));
    // Left Shift
    string temp = byt[0];
    for(int i = 1; i < byt.size(); i++)
        byt[i-1] = byt[i];
    byt[byt.size()-1] = temp;
    // Passing through S-Box
    for(int i = 0; i < byt.size(); i++)
    {
        int y, x;
        if(byt[i][0] >= '0' && byt[i][0] <= '9')
            y = byt[i][0] - '0';
        else
            y = byt[i][0] - 'A' + 10;
        
        if(byt[i][1] >= '0' && byt[i][1] <= '9')
            x = byt[i][1] - '0';
        else
            x = byt[i][1] - 'A' + 10;
        
        byt[i] = sbox[y][x];
    }
    // XOR with RC[round]
    string RC[10] = {"01", "02", "04", "08", "10", "20", "40", "80", "1B", "36"};
    string res = xorr(byt[0], RC[round]);
    for(int i = 1; i < byt.size(); i++)
        res += byt[i];
    return res;
}

void key_gen()
{
    // Create S-Box
    createSB();
    // Randomly generate 128 bit 
    string k;
    char v[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    vector<int> key;
    for(int i = 0; i < 32; i++)
    {
        char c = v[rand()%16];
        k += c;
        if(c >= '0' && c <= '9')
            key.push_back(c-'0');
        else
            key.push_back(c-'A'+10);
    }
    // k = "0F1571C947D9E8590CB7ADD6AF7F6798";
    cout<<"Key : "<<k<<"\n";

    vector<string> k_state_array;
    for(int i = 0; i < 32; i += 2)
        k_state_array.push_back(str(k[i])+str(k[i+1]));
    cout<<"K0 to K15 :\n";
    for(int i = 0; i < k_state_array.size(); i++)
        cout<<k_state_array[i]<<" ";

    vector<string> words;
    for(int i = 0; i < 32; i += 8)
        words.push_back(k.substr(i,8));

    int ro = 0; 
    for(int i = 4; i < 44; i++)
    {
        if(i % 4 == 0)
            words.push_back(xorr(words[i-4], g(words[i-1], ro++)));
        else
            words.push_back(xorr(words[i-4], words[i-1]));
    }    
    // Saving words to a file
    ofstream of("words.txt");
    for(int i = 0; i < words.size(); i++)
        of<<words[i]<<"\n";
}

void addroundkey(string pt[4][4], string word_state[4][4])
{
    string res[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            c3[i][j] = xorr(pt[i][j], word_state[i][j]);
        }
    }
}

void shiftRows(string pt[4][4])
{
    for(int i = 0; i < 4; i++)
        c1[0][i] = pt[0][i];
    
    string temp = pt[1][0];
    for(int i = 1; i < 4; i++)
        c1[1][i-1] = pt[1][i];
    c1[1][3] = temp;
    
    for(int i = 2; i < 4; i++)
        c1[2][i-2] = pt[2][i];
    c1[2][2] = pt[2][0];
    c1[2][3] = pt[2][1];

    c1[3][0] = pt[3][3];
    for(int i = 1; i < 4; i++)
        c1[3][i] = pt[3][i-1];
}

void invshiftRows(string pt[4][4])
{
    for(int i = 0; i < 4; i++)
        c1[0][i] = pt[0][i];

    c1[1][0] = pt[1][3];
    for(int i = 1; i < 4; i++)
        c1[1][i] = pt[1][i-1];

    c1[2][2] = pt[2][0]; c1[2][3] = pt[2][1];
    c1[2][0] = pt[2][2]; c1[2][1] = pt[2][3];
    
    string temp = pt[3][0];
    for(int i = 1; i < 4; i++)
        c1[3][i-1] = pt[3][i];
    c1[3][3] = temp;
}

void mixcol(string pt[4][4])
{
    string mat[4][4];
    mat[0][0]="02";
    mat[0][1]="03";
    mat[0][2]="01";
    mat[0][3]="01";
    mat[1][0]="01";
    mat[1][1]="02";
    mat[1][2]="03";
    mat[1][3]="01";
    mat[2][0]="01";
    mat[2][1]="01";
    mat[2][2]="02";
    mat[2][3]="03";
    mat[3][0]="03";
    mat[3][1]="01";
    mat[3][2]="01";
    mat[3][3]="02";
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            string aa, bb, temp[4];
            for(int k = 0; k < 4; k++)
            {
                aa=hextobin(mat[i][k]);
                bb=hextobin(pt[k][j]);
                int p1[9];
                int p2[9];
                int p3[9];
                for(int kk=0;kk<=7;kk++)
                {
                    if(aa[kk]=='0')
                        p1[7-kk]=0;
                    else
                        p1[7-kk]=1;
                    if(bb[kk]=='0')
                        p2[7-kk]=0;
                    else
                        p2[7-kk]=1;
                    p3[kk]=0;
                }
                p1[8]=0;
                p2[8]=0;
                p3[8]=0;
                multiply(p1,p2,p3);
                string ss;
                ss="";
                for(int kk=7;kk>=0;kk--)
                {
                    if(p3[kk]==1)
                        ss=ss+"1";
                    else
                        ss=ss+"0";
                }
                temp[k] = bintohex(ss);
            }
            c2[i][j] = temp[0];
            for(int k = 1;k < 4; k++)
                c2[i][j] = xorr(c1[i][j], temp[k]);
        }
    }
}

void invmixcol(string pt[4][4])
{
    string mat[4][4];
    mat[0][0]="0E";
    mat[0][1]="0B";
    mat[0][2]="0D";
    mat[0][3]="09";
    mat[1][0]="09";
    mat[1][1]="0E";
    mat[1][2]="0B";
    mat[1][3]="0D";
    mat[2][0]="0D";
    mat[2][1]="09";
    mat[2][2]="0E";
    mat[2][3]="0B";
    mat[3][0]="0B";
    mat[3][1]="0D";
    mat[3][2]="09";
    mat[3][3]="0E";
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            string aa, bb, temp[4];
            for(int k = 0; k < 4; k++)
            {
                aa=hextobin(mat[i][k]);
                bb=hextobin(pt[k][j]);
                int p1[9];
                int p2[9];
                int p3[9];
                for(int kk=0;kk<=7;kk++)
                {
                    if(aa[kk]=='0')
                        p1[7-kk]=0;
                    else
                        p1[7-kk]=1;
                    if(bb[kk]=='0')
                        p2[7-kk]=0;
                    else
                        p2[7-kk]=1;
                    p3[kk]=0;
                }
                p1[8]=0;
                p2[8]=0;
                p3[8]=0;
                multiply(p1,p2,p3);
                string ss;
                ss="";
                for(int kk=7;kk>=0;kk--)
                {
                    if(p3[kk]==1)
                        ss=ss+"1";
                    else
                        ss=ss+"0";
                }
                temp[k] = bintohex(ss);
            }
            c2[i][j] = temp[0];
            for(int k = 1;k < 4; k++)
                c2[i][j] = xorr(c1[i][j], temp[k]);
        }
    }
}

void p_to_c(string file, string ofile)
{
    createSB();
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    ifstream w("words.txt");
    string a;
    while(!ip.eof())
        getline(ip, a);
    vector<string> words;
    while(!w.eof())
    {
        string b;
        getline(w, b);
        words.push_back(b);
    }
    string pt[4][4];
    int k = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            pt[j][i] = a.substr(k, 2);
            k += 2;
        }
    }
    for(int i = 0; i < 11; i++)
    {
        string word_state[4][4];
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
                word_state[k][j] = words[4*i+j].substr(2*k, 2);
        }
        if(i == 0)
        {
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c3[ii][jj];
            }
        }
        else if(i >= 1 && i <= 9)
        {
            // Passing through S-Box
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    int y, x;
                    string val = pt[ii][jj];
                    if(val[0] >= '0' && val[0] <= '9')
                        y = val[0] - '0';
                    else
                        y = val[0] - 'A' + 10;
                    
                    if(val[1] >= '0' && val[1] <= '9')
                        x = val[1] - '0';
                    else
                        x = val[1] - 'A' + 10;
                    pt[ii][jj] = sbox[y][x];
                }
            }
            // shift rows
            shiftRows(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c1[ii][jj];
            }
            // mix column
            mixcol(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c2[ii][jj];
            }
            // add round key
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c3[ii][jj];
            }
        }
        else
        {
            // Passing through S-Box
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    int y, x;
                    string val = pt[ii][jj];
                    if(val[0] >= '0' && val[0] <= '9')
                        y = val[0] - '0';
                    else
                        y = val[0] - 'A' + 10;
                    
                    if(val[1] >= '0' && val[1] <= '9')
                        x = val[1] - '0';
                    else
                        x = val[1] - 'A' + 10;
                    pt[ii][jj] = sbox[y][x];
                }
            }
            // shift rows
            shiftRows(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c1[ii][jj];
            }
            // add round key
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    pt[ii][jj] = c3[ii][jj];
                    of<<pt[ii][jj];
                }
            }
            of<<"\n";
        }   
    }
}

void c_to_p(string file, string ofile, string key)
{
    createISB();
    ifstream ip(file.c_str());
    ofstream of(ofile.c_str());
    ifstream w(key.c_str());
    string a;
    while(!ip.eof())
        getline(ip, a);
    vector<string> words;
    while(!w.eof())
    {
        string b;
        getline(w, b);
        words.push_back(b);
    }
    string pt[4][4];
    int k = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            pt[j][i] = a.substr(k, 2);
            k += 2;
        }
    }
    for(int i = 10; i >= 0; i--)
    {
        string word_state[4][4];
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
                word_state[k][j] = words[4*i+j].substr(2*k, 2);
        }
        if(i == 10)
        {
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c3[ii][jj];
            }
        }
        else if(i >= 9 && i <= 1)
        {
            // inverse shift rows
            invshiftRows(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c1[ii][jj];
            }
            // Passing through Inverse S-Box
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    int y, x;
                    string val = pt[ii][jj];
                    if(val[0] >= '0' && val[0] <= '9')
                        y = val[0] - '0';
                    else
                        y = val[0] - 'A' + 10;
                    
                    if(val[1] >= '0' && val[1] <= '9')
                        x = val[1] - '0';
                    else
                        x = val[1] - 'A' + 10;
                    pt[ii][jj] = invsbox[y][x];
                }
            }
            // add round key
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c3[ii][jj];
            }
            // inverse mix column
            invmixcol(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c2[ii][jj];
            }
        }
        else
        {
            // inverse shift rows
            invshiftRows(pt);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                    pt[ii][jj] = c1[ii][jj];
            }
            // Passing through Inverse S-Box
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    int y, x;
                    string val = pt[ii][jj];
                    if(val[0] >= '0' && val[0] <= '9')
                        y = val[0] - '0';
                    else
                        y = val[0] - 'A' + 10;
                    
                    if(val[1] >= '0' && val[1] <= '9')
                        x = val[1] - '0';
                    else
                        x = val[1] - 'A' + 10;
                    pt[ii][jj] = invsbox[y][x];
                }
            }
            // add round key
            addroundkey(pt, word_state);
            for(int ii = 0; ii < 4; ii++)
            {
                for(int jj = 0; jj < 4; jj++)
                {
                    pt[ii][jj] = c3[ii][jj];
                    of<<pt[ii][jj];
                }
            }
            of<<"\n";
        }   
    }
}

int main()
{
    srand(time(NULL));
    char c = 'y';
    string file, ofile, key;
    do
    {
        cout<<"Choose the following: \n1. Key Generation\n2. Encryption\n3. Decryption\n4. Exit\n";
        int ch;
        cin>>ch;
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
        cout<<"\nDo you want to try again[y/N]: ";
            cin>>c;
    }while(c == 'y');
    return 0;
}