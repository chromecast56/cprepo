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
/*
                GOAL is: Just bsearch on t - Each one go out left, then try as much right
 */
int n,m,k,s;
ll a[1000100], b[1000100];
int v[1000100];
int bs[1000100]; //store the binary searched index of a[i] in b
int bsearch(ll val) {
    int l=1, r=m+1;
    while(l<r) {
        int mm = (l+r)>>1;
        if (val<=b[mm]) r=mm;
        else l=mm+1;
    }
    return l;
}
bool check(ll t) {
    int last = 0;
    for (int i=1;i<=n;i++) {
        //ll cur = 0; //current time
        int ind = bs[i];

        int left = 0;
        for (int j=ind-1;j>last;j--) { //have to do on left
            if (j==ind-1) left += a[i]-b[j];
            else left += b[j+1]-b[j];
            left += s;
        }
        if (left>t) return 0;

        last = ind-1;
        int right = 0;
        for (int j=ind;j<=m;j++) { //go far right as possible
            if (j==ind) right += b[j]-a[i];
            else right += b[j]-b[j-1];
            right += s;
            if (2*left+right>t && left+2*right>t) {
                if (i==n) return 0;
                break;
            }
            last = j;
        }
    }
    return 1;
}
ll solve() {
    cin>>n>>m>>k>>s;
    fill(a+1,a+n+1,0);
    fill(b+1,b+m+1,0);
    for (int i=1;i<=k;i++) cin>>a[i];
    ll ap,bp,cp,dp;cin>>ap>>bp>>cp>>dp;
    for (int i=k+1;i<=n;i++) a[i] = (a[i-2]*ap+a[i-1]*bp+cp)%dp+1;
    for (int i=1;i<=k;i++) cin>>b[i];
    ll ah,bh,ch,dh;cin>>ah>>bh>>ch>>dh;
    for (int i=k+1;i<=m;i++) b[i] = (b[i-2]*ah+b[i-1]*bh+ch)%dh+1;

    sort(a+1,a+n+1);
    sort(b+1,b+m+1);

    for (int i=1;i<=n;i++)
        bs[i] = bsearch(a[i]);

    ll l=0,r=3e9;
    while(l<r) {
        ll mm = (l+r)>>1;
        if (check(mm)) r=mm;
        else l=mm+1;
    }
    return l;
}
int main()
{
    //ofstream fout("PATH\\output.txt");
   // ifstream fin("PATH\\input.txt");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int test;cin>>test;
    for (int i=1;i<=test;i++)
        cout << "Case #" << i << ": " << solve() << '\n';


    return 0;
}