#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
#define lb lower_bound

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
}
int a[200000];
int f[2000000];
int query[2000000]; //optimize later
int inds[26][26]; //for each letter i, store number of occuerences of letters in front j
int n;
int main()
{
    setIO();
    string str;cin>>str;
    n = sz(str);
    vector<int> v;
    for (int i=0;i<n;i++) v.pb(str[i]-'a');
    sort(all(v));
    v.erase(unique(all(v)),v.end());
    int bt = sz(v);

    for (int i=0;i<n;i++) for (int j=0;j<bt;j++) if (str[i]-'a' == v[j]) a[i] = j;

    for (int i=0;i<n-1;i++) inds[a[i]][a[i+1]]++;


    //for (int i=0;i<n;i++) cout << a[i];
    for (int i=0;i<2000000;i++) f[i] = 2000000;
    f[0] = 1;


    for (int msk=0;msk<(1<<bt);msk++)
        for (int let=0;let<bt;let++)
            if (!(msk&(1<<let))) {
                int add = 0;
                int nmsk = msk + (1<<let);
                /*for (auto ind: inds[let])
                    if (ind+1 < n && (nmsk & (1<<a[ind+1])))
                        add++;*/
                for (int i=0;i<bt;i++) {
                    if (nmsk & (1<<i))
                        add += inds[let][i];
                }
                f[nmsk] = min(f[nmsk],f[msk]+add);
            }


    cout << f[(1<<bt)-1] << '\n';

    return 0;
}


