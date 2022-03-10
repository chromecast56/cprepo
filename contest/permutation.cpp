#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define all(x) (x).begin(),(x).end()
#define pb push_back
void setIO() {
    ios_base::sync_with_stdio(0); cin.tie(0);
}
struct line {
    pii a,b;
};
int cr(pii a,pii b,pii c) {
    return (c.S - a.S) * (b.F - a.F) > (b.S - a.S) * (c.F - a.F);
}
int intersect(line a, line b) {
    if (a.a==b.a||a.a==b.b||a.b==b.a||a.b==b.b) return 0;
    return cr(a.a,b.a,b.b) != cr(a.b,b.a,b.b) && cr(a.a,a.b,b.a) != cr(a.a,a.b,b.b);
}
int main()
{
    setIO();
    int n;cin>>n;
    vpii a;
    for (int i=0;i<n;i++) {
        int x,y;cin>>x>>y;
        a.pb({x,y});
    }

    int res = 0;

    vector<line> seg;
    sort(all(a));
    do {
        seg.clear(); seg.pb({a[0],a[1]}); seg.pb({a[1],a[2]}); seg.pb({a[0],a[2]});

        int bb = 1;
        for (int i=3;i<n;i++) {
            int cnt = 0;
            for (int j=0;j<i;j++) {
                int b = 1;
                line u = {a[i],a[j]};
                for (auto v: seg)
                    if (intersect(u,v)) {
                        b = 0;
                        break;
                    }
                if (b) cnt++, seg.pb(u);
            }
            if (cnt != 3) {
                bb = 0;
                break;
            }
        }
        if (bb) res++;
    }
    while(next_permutation(all(a)));

    cout << res << '\n';

    //cout << intersect({{0,0},{1,1}},{{0,4},{0,0}});

    return 0;
}


