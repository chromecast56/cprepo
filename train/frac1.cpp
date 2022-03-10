/*
ID: jamesli5
PROG: frac1
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

struct frac
{
    int a,b;
};
bool comp(frac a,frac b)
{
    return a.a*b.b < a.b*b.a;
}
int gcd(int a, int b) //euclidean algo
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    if (a == b)
        return a;

    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}
int main()
{
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");

    int n;
    fin >> n;

    vector<frac> res;
    for (int num = 1; num < n; num++)
        for (int dem = num+1; dem <= n; dem++)
            if (gcd(num,dem) == 1)
            {
                frac f = {num,dem};
                res.push_back(f);
            }
    sort(res.begin(),res.end(),comp);

    fout << "0/1" << "\n";
    for (auto &next: res)
        fout << next.a << '/' << next.b << "\n";
    fout << "1/1" << "\n";

    return 0;
}
