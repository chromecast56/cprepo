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
const ll MOD = 998244353;
const int maxn = 500500;

ll add(ll a,ll b) {return (a+b)%MOD;}
ll sub(ll a,ll b) {return (a-b+MOD)%MOD;}
ll mul(ll a,ll b) {return (a*b)%MOD;}

struct mi {
    ll v; explicit operator ll() const { return v; }
    mi() { v = 0; }
    mi(ll _v) {
        v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
        if (v < 0) v += MOD;
    }
    friend bool operator==(const mi& a, const mi& b) {
        return a.v == b.v; }
    friend bool operator!=(const mi& a, const mi& b) {
        return !(a == b); }
    friend bool operator<(const mi& a, const mi& b) {
        return a.v < b.v; }

    mi& operator+=(const mi& m) {
        if ((v += m.v) >= MOD) v -= MOD;
        return *this; }
    mi& operator-=(const mi& m) {
        if ((v -= m.v) < 0) v += MOD;
        return *this; }
    mi& operator*=(const mi& m) {
        v = v*m.v%MOD; return *this; }
    mi& operator/=(const mi& m) { return (*this) *= inv(m); }
    friend mi pow(mi a, ll p) {
        mi ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mi inv(const mi& a) { assert(a.v != 0);
        return pow(a,MOD-2); }

    mi operator-() const { return mi(-v); }
    mi& operator++() { return *this += 1; }
    mi& operator--() { return *this -= 1; }
    mi operator++(int) { mi temp; temp.v = v++; return temp; }
    mi operator--(int) { mi temp; temp.v = v--; return temp; }
    friend mi operator+(mi a, const mi& b) { return a += b; }
    friend mi operator-(mi a, const mi& b) { return a -= b; }
    friend mi operator*(mi a, const mi& b) { return a *= b; }
    friend mi operator/(mi a, const mi& b) { return a /= b; }
    friend ostream& operator<<(ostream& os, const mi& m) {
        os << m.v; return os;
    }
    friend istream& operator>>(istream& is, mi& m) {
        ll x; is >> x;
        m.v = x;
        return is;
    }
};
int n,m;
struct Node {
    mi xx,Xx,xX,XX;
};
Node t[4*maxn];
mi a[maxn];
mi c(int i) {
    mi v = a[i-1]*10+a[i];
    if (v < 10 || 18 < v) return 0;
    return 19-v;

}
Node modify(int ind, mi val,int tl=0,int tr=n,int v=1) {
    if (tl+1==tr) {
        t[v] = {0,1,1,val+1};
    }
    else {
        int m = (tl+tr)>>1;
        if (ind<m) modify(ind,val,tl,m,v*2);
        else       modify(ind,val,m,tr,v*2+1);

        //merge operation
        t[v].xx = t[2*v].xX*t[2*v+1].Xx + t[2*v].xx * c(m) * t[2*v+1].xx;
        t[v].Xx = t[2*v].XX*t[2*v+1].Xx + t[2*v].Xx * c(m) * t[2*v+1].xx;
        t[v].xX = t[2*v].xX*t[2*v+1].XX + t[2*v].xx * c(m) * t[2*v+1].xX;
        t[v].XX = t[2*v].XX*t[2*v+1].XX + t[2*v].Xx * c(m) * t[2*v+1].xX;

        /*t[v].xx = add(mul(t[2*v].xX,t[2*v+1].Xx),mul(mul(t[2*v].xx,c(m)),t[2*v+1].xx));
        t[v].Xx = add(mul(t[2*v].XX,t[2*v+1].Xx),mul(mul(t[2*v].Xx,c(m)),t[2*v+1].xx));
        t[v].xX = add(mul(t[2*v].xX,t[2*v+1].XX),mul(mul(t[2*v].xx,c(m)),t[2*v+1].xX));
        t[v].XX = add(mul(t[2*v].XX,t[2*v+1].XX),mul(mul(t[2*v].Xx,c(m)),t[2*v+1].xX));*/
    }
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>m;
    string val;cin>>val;
    for (int i=0;i<n;i++) {
        a[i] = val[i] - '0';
        modify(i,a[i]);
    }

    for (int i=0;i<m;i++) {
        int x,d;cin>>x>>d;
        x--;
        a[x] = d;
        modify(x,d);
        cout << t[1].XX << '\n';
    }

    return 0;
}