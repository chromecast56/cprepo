#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
/*
                    Find a greedy: (modulo 3, etc)
                    Prove it

                    Ex. In this case, you can split into 3 sets, which connect to each other. Removing a set will make the graph nondangerous
                    Prove that the size of the third set (V2) is <= 4/7n, because each node can only have 2 outgoing edges
 */

#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

unordered_set<int> res;
int contains(int a) {
    return res.find(a) != res.end();
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n,m;cin>>n>>m;
        vector<vi> G(n+1);
        vector<vi> GR(n+1);
        vi dp(n+1); //dp[i] = max path to i, delete all 2%3 afterwards

        for (int i=0;i<m;i++) {
            int a,b;cin>>a>>b;
            assert(a<b);
            G[a].pb(b);
            GR[b].pb(a);
        }

        res.clear();
        for (int i=1;i<=n;i++) {
            for (auto j: GR[i])
                dp[i] = max(dp[j]+1, dp[i]);

            if (dp[i] == 2) {
                res.insert(i);
                dp[i] = -1;
            }
        }



        assert(7*res.size() <= 4*n);
        cout << res.size() << '\n';
        for (auto a:res)
            cout << a << ' ';
        cout << endl;
    }

    return 0;
}