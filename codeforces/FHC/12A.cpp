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
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

ll l[1000100], h[1000100], w[1000100];

int n,k;
void IO() {
    cin>>n>>k;
    int al,bl,cl,dl;cin>>al>>bl>>cl>>dl;
    for (int i=k+1;i<=n;i++)
        l[i] = (al*l[i-2] + bl*l[i-1] + cl)%dl + 1;
    int aw,bw,cw,dw;cin>>aw>>bw>>cw>>dw;
    for (int i=k+1;i<=n;i++)
        w[i] = (aw*w[i-2] + bw*w[i-1] + cw)%dw + 1;
    int ah,bh,ch,dh;cin>>ah>>bh>>ch>>dh;
    for (int i=k+1;i<=n;i++)
        h[i] = (ah*h[i-2] + bh*h[i-1] + ch)%dh + 1;
}
ll solve() {
    set<pii> s;
    IO();

    ll res = 2*(w[1]+h[1]);
    ll psum = res;
    s.insert({l[1],1}); s.insert({l[1]+w[1],1});
    for (int i=2;i<=n;i++) {
        vpii t;
        unordered_set<int> remove;
        pii d = {0,0};

        auto L = s.lower_bound({l[i],0}), R = s.lower_bound({l[i]+w[i],1e9});
        if (L==s.end() || R==s.begin()) {
            psum += 2*(w[i]+h[i]);
            s.insert({l[i],i}); s.insert({l[i]+w[i],i});
            continue;
        }
        R = prev(R);
        if (s.find({L->}))

        bool lend=1,rend=1;
        for (auto itr = s.find(L); itr != s.end() && prev(itr) != s.find(R); itr++) {
            pii v = *itr;
            if (v.F-w[v.S] <= L.F && s.find({v.F-w[v.S],v.S}) != s.end())
                L = {v.F-w[v.S],v.S}, lend=0;
            if (v.F+w[v.S] >= R.F && s.find({v.F+w[v.S],v.S}) != s.end())
                R = {v.F+w[v.S],v.S}, rend=0;
        }

        for (auto itr = s.find(L); itr != s.end() && prev(itr) != s.find(R); itr++) {
            pii v = *itr;
            if ((!lend && v.S==0) || (!rend && v.S==1e9)) continue;
            t.pb(v);
        }

        s.erase({l[i],0}); s.erase({l[i]+w[i],1e9});

        ll dist = R.F-L.F;
        int cnt = 0;
        for (int j=0;j<sz(t)-1;j++)
            if (t[j].S == t[j+1].S)
                dist -= t[j+1].F-t[j].F,
                cnt++;
    }


    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int test;cin>>test;
    for (int i=1;i<=test;i++)
        cout << "Test #" << i << ": " << solve() << '\n';

    return 0;
}