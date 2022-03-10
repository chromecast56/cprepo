/*
                Inspiration: You know from the start that this is a simply game theory question. Look at the question
                carefuly (and any lemmas you make should actually solve the game stupid), and find a base case in which
                someone is guarenteed to win. Then you can expand on this base case (zugzwuang style)
 */


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

vector<int> G[1001];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;
    cin>>t;
    while(t--) {
        int n,x;
        cin>>n>>x;

        for (int i=0;i<=n;i++) G[i].clear();

        for (int i=0;i<n-1;i++) {
            int u,v;
            cin>>u>>v;
            G[u].pb(v);  G[v].pb(u);
        }

        if (n%2==0 || G[x].size() <= 1) cout << "Ayush\n"; else cout << "Ashish\n";


    }
    return 0;
}