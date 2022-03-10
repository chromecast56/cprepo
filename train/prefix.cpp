/*
ID: jamesli5
PROG: prefix
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

bool v[200001];
vector<string> check;
int res = 0;
int main()
{
    ofstream fout("prefix.out");
    ifstream fin("prefix.in");

    string prim;
    fin >> prim;
    while(prim.at(0) != '.')
    {
        check.push_back(prim);
        fin >> prim;
    }
    string add, S = "";
    getline(fin,add);
    add = " ";
    while(add != "")
    {
        getline(fin,add);
        S.append(add);
    }

    for (auto &str: check)
        if (S.substr(0,str.length()) == str)
        {
            v[str.length()] = 1;
            res = max(res,(int)str.length());
        }

    for (int i = 0; i < (int) S.length(); i++)
    {
        for (auto &str: check)
        {
            int ind = i - (int) str.length() + 1;
            if (ind < 0) continue;
            if (v[ind] && S.substr(ind,(int) str.length()) == str)
            {
                v[ind+(int) str.length()] = 1;
                res = max(res,i+1);
                break;
            }
        }
    }

    fout << res << "\n";
    return 0;
}