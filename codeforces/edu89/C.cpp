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

int check(string x) {
    int init = 0;
    int res = 0;
    while(1) {
        bool b = 1;
        int cur = init;
        for (int i=0;i<x.size();i++) {
            res++;
            if (x[i]=='+') cur++; else cur--;
            if (cur<0) {
                b=0; break;
            }
        }
        if (b) break;
        init++;
    }
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        string x; cin>>x;
        vi v; v.pb(0);
        for (int i=0;i<x.size();i++)
            v.pb(x[i]=='+'? 1:-1);

        int n=x.size();
        int p = 0;

        vector<ll> s(n+1);
        int m = 0;
        for (int i=1;i<=n;i++) {
            p += -1*v[i];
            m = max(m,p);
            if (p>=0 && !s[p]) s[p] = i;
        }

        ll res = n;
        for (int i=1;i<=m;i++)
             res += s[i];

  //      assert(res == check(x));
        cout << res << '\n';
    }

    return 0;
}