/*
ID: jamesli5
PROG: hamming
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

//Official solution used exponential time dfs to find the set, mine's a simple greedy algo that always puts in
//numbers when we can

//I'm not too sure why this works though
int N,B,D;
vector<int> res;
bool canHam(int a,int b)
{
    int c = a^b;
    int num = 0;
    while(c > 0)
    {
        c -= (c & -c);
        num++;
        if (num == D)
            return 1;
    }
    return 0;
}
int main()
{
    ofstream fout("hamming.out");
    ifstream fin("hamming.in");

    fin >> N >> B >> D;

    //the official solution notes that 0 can always be in the set, so the outer loop isn't even needed!
    for (int start = 0; start < pow(2,B); start++)
    {
        res.clear();
        res.push_back(start);
        int last = start;
        bool is_set = 0;
        for (int next = last+1; next < pow(2,B); next++)
        {
            bool can = 1;
            for (auto &a: res)
                if (!canHam(a,next))
                {
                    can = 0;
                    break;
                }

            if (can)
                res.push_back(next);
            if ((int) res.size() == N)
            {
                is_set = 1;
                break;
            }
        }
        if (is_set)
            break;
    }
    for (int i=0;i<(int) res.size()-1;i++)
    {
        if (i%10==9)
            fout << res[i] << "\n";
        else
            fout << res[i] << ' ';
    }
    fout << res[res.size()-1] << "\n";

    return 0;
}