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


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;cin>>n;
    vi f(MX); //freqlist

    multiset<int> square;
    multiset<int> rect;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        f[x]++;

        if (f[x]%4==0 && f[x]) square.insert(x), rect.erase(rect.find(x));
        else if (f[x]%2==0 && f[x]) rect.insert(x);

    }

    int m;cin>>m;

    while(m--) {
        char c; int x;
        cin>>c>>x;
        if (c=='+') {
            f[x]++;
            if (f[x]%4==0 && f[x]) square.insert(x), rect.erase(rect.find(x));
            else if (f[x]%2==0 && f[x]) rect.insert(x);
        }
        else {
            if (f[x]%4==0) square.erase(square.find(x)), rect.insert(x);
            else if (f[x]%2==0) rect.erase(rect.find(x));

            f[x]--;
        }

        if ((square.size() && rect.size() >= 2) || (square.size() >= 2))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}