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
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}


ll h[1000100],l[1000100];
ll solve() {
    int n,k,w;
    cin>>n>>k>>w;
    for (int i=1;i<=k;i++) cin>>l[i];
    int al,bl,cl,dl;cin>>al>>bl>>cl>>dl;
    for (int i=k+1;i<=n;i++)
        l[i] = (al*l[i-2] + bl*l[i-1] + cl)%dl + 1;

    for (int i=1;i<=k;i++) {
        cin>>h[i];
    }
    int ah,bh,ch,dh;cin>>ah>>bh>>ch>>dh;
    for (int i=k+1;i<=n;i++) {
        h[i] = (ah*h[i-2] + bh*h[i-1] + ch)%dh + 1;
    }

    ll res = 2*(w+h[1]);
    ll psum = res;
    for (int i=2;i<=n;i++) {
        ll hmax = 0;
        for (int j=i-1;j>=1 && l[j]+w >= l[i];j--)
            hmax = max(hmax,h[j]);

        psum += 2*(w+h[i]);
        ll delta = l[i] <= l[i-1]+w? l[i-1]+w-l[i] : -1;
        if (delta==-1) delta = 0;
        else {
            delta = 2*(delta+min(hmax,h[i]));
        }

        psum = (psum-delta)%MOD;
        res = (res*psum)%MOD;
    }

    return res;
}
int main()
{
    //ofstream fout("C:\\Users\\haita\\Desktop\\Coding\\CLionProjects\\projects\\codeforces\\FHC\\output.txt");
    //ifstream fin("C:\\Users\\haita\\Desktop\\Coding\\CLionProjects\\projects\\codeforces\\FHC\\input.txt");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int test;cin>>test;
    for (int i=1;i<=test;i++)
        cout << "Case #" << i << ": " << solve() << '\n';

    return 0;
}

