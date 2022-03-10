/*
                        Basically: Just store # inversions for each a[i] (where a[i] is the smaller)
                        This means that for a given hair cut length l, all a[i] >= l do not count, only a[i] < l
                        So you can just prefix sum
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

ll a[1000000];
int BT[1000000];
int get(int i) {
    int res = 0;
    i++;
    while(i) {
        res += BT[i];
        i -= i & (-i);
    }

    return res;
}
void add(int i, int amt) {
    i++;
    while(i<1000000) {
        BT[i] += amt;
        i += i & (-i);
    }
}

ll res[1000000];
int main()
{
    ofstream fout("haircut.out");
    ifstream fin("haircut.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n; fin>>n;
    for (int i=0;i<n;i++)  {
        fin>>a[i];
        res[a[i]+1] += get(n) - get(a[i]);
        add(a[i],1);
    }

    for (int i=0;i<n;i++) {
        fout << res[i] << '\n';
        res[i+1] += res[i];
    }

    return 0;
}