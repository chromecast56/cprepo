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

ll solve(vector<ll> &v) {
    ll res = 0, cur = 0;
    for (int i=0;i<v.size();i++) {
        cur += v[i];
        if (cur < 0) cur = 0;
        res = max(res,cur);
    }
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    int test;cin>>test;
    while(test--) {
        int n;cin>>n;
        vector<ll> a,b;
        vector<ll> A;

        ll res = 0;
        for (int i=0;i<n;i++) {
            int x;cin>>x;

            if (i%2==0) res += x;
            A.pb(x);
            if (i%2) b.pb(x); else a.pb(x);
        }

        vector<ll> c,d;
        for (int i=0;2*i+1<n;i++)
            c.pb(A[2*i+1]-A[2*i]);

        for (int i=1;2*i<n;i++)
            d.pb(A[2*i-1]-A[2*i]);

        ll delta = max(solve(c),solve(d));
        cout << res+delta << '\n';
    }

    return 0;
}