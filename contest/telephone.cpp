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
#define lb lower_bound
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
}
int n,k;

int a[50100];
int g[60][60];
int d[50100][60][2];

struct node {
    int x,k,b;
};
int main()
{
    setIO();
    cin>>n>>k;

    for (int i=0;i<n;i++) cin>>a[i];
    for (int i=1;i<=k;i++) {
        string x;cin>>x;
        for (int j=0;j<sz(x);j++)
            g[i][j+1] = x[j]-'0';
    }

    /*
                After testing out a few edge cases, we can come to the following conclusions:
                - There is a reason why we are working with Euclidian distances and not arbitrary distances
                - We must exploit this to reduce the trivial O(n^2) sol.

                - The minimum possible answer is n, n-1 exactly.
                - Any "backtracking" that we do will add - so excess backtracking is nonoptimal
                - This means that when jumping to some color k, its possible to "overjump". But we don't know
                how far to jump to optimize - this is a very hard problem

                - Our solution is to exploit the characteristics of the search space - it is built on a reduced
                graph of size k < 60. The graph is very very dense, and we can flatten it out.
                Instead of jumping directly to some color k, we can also exploit that distances are hamiltonian.
                'Instead of a big jump, we can do it step by step, keeping track on the current "jump color" that we
                are riding on. At every node (x,k) with jump color k we are riding on, we can either continue
                our previous jump, going to (x+1,k) or (x-1,k) if we are going back (this lends itself to
                another dimension for the direction!). Or, we can "stop" at the current x if we can
                finish the jump (check if g[k][a[x]] = 1), and then spread out in both directions.

                BFS and then if we can finish at the end, we stop.

                This BFS happens in O(nk), since the transition is O(1), which passes in the time constraints.
     */

    queue<node> q;
    q.push({0,a[0],1});
    for (int i=0;i<n;i++) for (int j=1;j<=k;j++) for (int b=0;b<2;b++) d[i][j][b] = -1;
    d[0][a[0]][1] = 0;
    while(!q.empty()) {
        node cur = q.front(); q.pop();
        //if (d[cur.x][cur.k][cur.b] != -1) continue;
        int D = d[cur.x][cur.k][cur.b]; //if we end, then end immidiately
        if (cur.x == n-1 && g[cur.k][a[n-1]]) {
            cout << D << '\n';
            return 0;
        }

        int dx = cur.b? 1:-1;
        if (d[cur.x+dx][cur.k][cur.b] == -1) q.push({cur.x+dx,cur.k,cur.b}), d[cur.x+dx][cur.k][cur.b] = D+1;
        if (g[cur.k][a[cur.x]]) {
            if (cur.x > 0 && d[cur.x-1][a[cur.x]][0] == -1) q.push({cur.x-1,a[cur.x],0}), d[cur.x-1][a[cur.x]][0] = D+1;
            assert(cur.x < n-1); //usually do if statement
            if (d[cur.x+1][a[cur.x]][1] == -1) q.push({cur.x+1,a[cur.x],1}), d[cur.x+1][a[cur.x]][1] = D+1;
        }
    }
    cout << "-1\n";

    return 0;
}


