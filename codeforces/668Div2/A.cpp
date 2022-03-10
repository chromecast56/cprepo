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


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n,k;cin>>n>>k;
        string x; cin>>x;
        vi bin(k,-1);
        bool b = 1;
        for (int i=0;i<n;i++)
            if (x[i]!='?') {
                if (bin[i%k]!=-1) {
                    if (bin[i%k] != x[i]-'0') b = 0;
                } else bin[i%k] = x[i]-'0';
            }
        if (!b) {
            cout << "NO\n";
            continue;
        }

        int cnt0=0,cnt1=0;
        for (int i=0;i<k;i++)
            if (bin[i]==0) cnt0++;
            else if (bin[i]==1) cnt1++;

        if (cnt0 > k/2 || cnt1 > k/2)
            cout << "NO\n";
         else cout << "YES\n";
    }


    return 0;
}