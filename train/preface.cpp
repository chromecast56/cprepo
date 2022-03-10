/*
ID: jamesli5
PROG: preface
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int n;
int res[1000], ord[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
string nums[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
char nums_reduced[] = {'I','V','X','L','C','D','M'};
int ord_reduced[] = {1,5,10,50,100,500,1000};

string convert(int num)
{
    string res = "";
    for (int i = 0; i < 13; i++) {
        while (ord[i] <= num) {
            res += nums[i];
            num -= ord[i];
        }
    }
    return res;
}
int main()
{
    ofstream fout("preface.out");
    ifstream fin("preface.in");

    fin >> n;

    for (int i = 1; i <= n; i++)
    {
        string cur = convert(i);
        for (int j = 0; j < (int) cur.length(); j++)
            res[cur.at(j)]++;
    }
    for (auto &a: nums_reduced)
        if (res[a])
            fout << a << ' ' << res[a] << "\n";

    return 0;
}
