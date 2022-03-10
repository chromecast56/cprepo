#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int N;
int T[2*MAXN];
map<int,int> mp; //time enter, cow id
int main()
{
//    ofstream fout("circlecross.out");
//    ifstream fin("circlecross.in");

    cin >> N;
    int res = 0;
    for (int i=1;i<=2*N;i++)
    {
        int val; cin >> val;
        if (T[val] == 0)
            T[val] = i, mp[i] = val;
        else
        {
            int ind = distance(mp.find(T[val]), mp.end());
        }
    }


    cout << res << "\n";
    return 0;
}