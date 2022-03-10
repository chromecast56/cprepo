/*
ID: jamesli5
PROG: zerosum
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> v; //0 for space, 1 for +, 2 for -
bool is_zero()
{
    bool add = 1;
    int last = 1, sum = 0;
    for (int i = 2; i <= N; i++)
    {
        if (v[i-2] == 0)
        {
            last = last*10 + i;
            continue;
        }
        sum = add? sum+last:sum-last;
        add = v[i-2]==1? 1:0;
        last = i;
    }
    sum = add? sum+last:sum-last;

    return sum==0;
}
void gen(int sz, ofstream &fout)
{
    if(sz==N-1)
    {
        if (is_zero())
        {
            for (int i = 1; i < N; i++)
            {
                fout << i;
                switch(v[i-1])
                {
                    case 0: fout << ' '; break;
                    case 1: fout << '+'; break;
                    case 2: fout << '-'; break;
                }
            }
            fout << N << "\n";
        }
        return;
    }
    v.push_back(0); gen(sz+1,fout); v.pop_back();
    v.push_back(1); gen(sz+1,fout); v.pop_back();
    v.push_back(2); gen(sz+1,fout); v.pop_back();
}
int main()
{
    ofstream fout("zerosum.out");
    ifstream fin("zerosum.in");

    fin >> N;

    gen(0, fout);
    return 0;
}