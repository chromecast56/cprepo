/*
        This is non-decreasing, for increasing you switch upper_bound -> lower_bound

        For decreasing/non-increasing you reverse the array
 */

#include <bits/stdc++.h>

using namespace std;

int N,T;
vector<long long> v;
int main()
{
    ofstream fout("cowjog.out");
    ifstream fin("cowjog.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin >> N >> T;
    while(N--)
    {
        long long s,vel;
        fin >> s >> vel;

        long long x = -(s + T*vel);
        vector<long long>::iterator it = upper_bound(v.begin(),v.end(),x);

        if (it == v.end())
            v.push_back(x);
        else
            *it = x;
    }
    fout << v.size() << '\n';

    return 0;
}