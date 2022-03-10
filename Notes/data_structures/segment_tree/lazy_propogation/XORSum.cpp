/*
                    Think of it as 2D array a[n][b] where b is the # of bits

                    If we XOR a number x with a given subarray l...r:

                        For all bits on x: If it is 0, then we do nothing. If it is 1, then for all elements a[l...r][b],we want to flip the bit
                        For range sum, is simply sum[l...r][b] * 2^b

                    Time complexity O(nlog^2n)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 1e5+100;
const ll INF = 1e18;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

int n;
struct segtree {
    ll t[4*MX], lazy[4*MX]; //1 = switch,0 = dont
    void push(int v,int l1,int l2) {
        if (!lazy[v]) return;
        lazy[2*v] ^= 1;
        lazy[2*v+1] ^= 1;
        t[2*v] = l1 - t[2*v];
        t[2*v+1] = l2 - t[2*v+1];
        lazy[v] = 0;
    }
    void upd(int l,int r,int tl=0,int tr=n,int v=1) { // [1,r)
        if (r <= l) return;
        if (l==tl&&r==tr) {
            t[v] = (tr-tl) - t[v];
            lazy[v] ^= 1;
        }
        else {
            int tm = (tl+tr)>>1;
            push(v,tm-tl,tr-tm);
            upd(l,min(r,tm),tl,tm,v*2);
            upd(max(l,tm),r,tm,tr,v*2+1);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
    ll query(int l,int r,int tl=0,int tr=n,int v=1) { // [l,r)
        if (r <= l) return 0;
        if (l==tl&&r==tr) return t[v];

        int tm = (tl+tr)>>1;
        push(v,tm-tl,tr-tm);
        return query(l,min(r,tm),tl,tm,v*2) + query(max(l,tm),r,tm,tr,v*2+1);
    }
};
segtree seg[21];
void upd(int l,int r,int x) {
    for (int i=0;i<=20;i++)
        if (x & 1<<i)
            seg[i].upd(l,r);
}
ll query(int l,int r) {
    ll res=0;
    for (int i=0;i<=20;i++)
        res += (1<<i)*seg[i].query(l,r);
    return res;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        upd(i,i+1,x);
    }

    int m;cin>>m;
    for (int i=0;i<m;i++) {
        int typ;cin>>typ;
        if (typ==1) {
            int l,r;cin>>l>>r;
            cout << query(l-1,r) << '\n';
        }
        else {
            int l,r,x;cin>>l>>r>>x;
            upd(l-1,r,x);
        }
    }

    return 0;
}