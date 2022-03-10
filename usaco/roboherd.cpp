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

int n,k;
vl r[100100];
struct state {
    int ind;
    vl a;
    state(int iind,vl v) {
        ind = iind,a = v;
    }
    vector<state> enumerate() {
        vector<state> res;
        for (int i=0;i<sz(r[ind]);i++) {
            vl ins = a; ins
        }
    }
};
int main()
{
//    ofstream fout("roboherd.out");
//    ifstream fin("roboherd.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    priority_queue<state> pq;
    cin>>n>>k;

    return 0;
}