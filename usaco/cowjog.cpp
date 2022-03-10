#include <bits/stdc++.h>

using namespace std;

int N,T;
int main()
{
//    ofstream fout("cowjog.out");
//    ifstream fin("cowjog.in");

    ios_base::sync_with_stdio(false); //faster I/O
    cin.tie(NULL); //include only for non-interactive problems

    vector<long long> v;

    cin >> N >> T;
    while(N--)
    {
        long long s,vel;
        cin >> s >> vel;

        long long x = -(s + T*vel);
        vector<long long>::iterator it = upper_bound(v.begin(),v.end(),x);

        if (it == v.end())
            v.push_back(x);
        else
            *it = x;
    }
    cout << v.size() << '\n';

    return 0;
}