/*
            NOTE: There is an optimization to reduce by a log factor, no seg tree is needed.
            Note how all queries to the seg tree are of form (a[i].v,q) where q is the end.
            This means that you can just maintain reverse prefix maxes to obtain the answer
 */
#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5+5;

int n,q;
struct state {
    int v,t; //val, last time updated
};
state a[maxn];

struct SegTree
{
    int n;  // array size
    int t[2 * maxn];

    void build() {  // build the tree
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }

    int query(int l, int r) {  // max on interval [l, r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, t[l++]);
            if (r&1) res = max(res, t[--r]);
        }
        return res;
    }
};
SegTree s;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i].v;
        a[i].t = -1;
    }

    cin>>q; s.n = q;
    for (int i=0;i<q;i++) {
        int type;cin>>type;
        if(type==1) {
            int id,x;cin>>id>>x;
            a[id] = {x,i};
        }
        else {
            int x;cin>>x;
            s.t[i+q] = x;
        }
    }

    s.build();
    vector<int> res;
    for (int i=1;i<=n;i++) {
        a[i].v = max(a[i].v, s.query(a[i].t,q));
        res.push_back(a[i].v);
    }

    for(int i=0;i<n-1;i++) cout<<res[i]<<' ';
    cout<<res[n-1]<<'\n';

    return 0;
}