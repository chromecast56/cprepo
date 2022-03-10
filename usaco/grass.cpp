#include <bits/stdc++.h>

using namespace std;
const int MAX = 100001;

int N,M;
vector<int> adj[MAX];
vector<int> adj_scc[MAX];
vector<int> adj_sccr[MAX];

int dp[2][MAX]; //max fields bessie can reach ending on node i, boolean for whether or not reversed

bool v[MAX];
int C[MAX], dfs_num[MAX], W[MAX]; //C: node i corresponds to which SCC
                              //dfs_num: helper array for tarjanSCC
                              //W: num nodes for each SCC
vector<int> S;                 //S: Stack for SCC
int num_counter = 0;
void tarjanSCC(int ind)
{
    C[ind] = dfs_num[ind] = ++num_counter;
    S.push_back(ind);
    v[ind] = 1;
    for (auto &ne: adj[ind])
    {
        if (dfs_num[ne] == -1) //visit
            tarjanSCC(ne);
        if (v[ne]) //take min
            C[ind] = min(C[ind], C[ne]);
    }

    if (C[ind] == dfs_num[ind]) //is a root of a scc
        while(1)
        {
            int ne = S.back(); S.pop_back(); v[ne] = 0;
            if (ind == ne)
                break;
        }
}
/*int dfs(const vector<int> *adj, bool cid, int s, int t) { //DOESNT WORK SEGFAULT
    if (s == t) {
        return 0;
    }

    int& ref = dp[cid][s];
    if (ref >= 0) {
        return ref;
    }

    ref = -1000000;
    for (auto &ne: adj[s]) {
        int res = dfs(adj, cid, ne, t);
        if (res >= 0) {
            ref = max(ref, W[s] + res);
        }
    }
    return ref;
}*/
int main()
{
//    ofstream fout("grass.out");
//    ifstream fin("grass.in");

    ios_base::sync_with_stdio(false); //faster I/O
    cin.tie(NULL); //include only for non-interactive problems

    cin >> N >> M;
    for (int i=0;i<M;i++)
    {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    memset(dfs_num,-1,sizeof(dfs_num)); //init

    for (int i=1;i<=N;i++) //start tarjan on every unvisited node
        if (dfs_num[i] == -1)
            tarjanSCC(i);

    for (int i=1;i<=N;i++) //count num_nodes for each scc
        W[C[i]]++;

    //create adj list for dag
    for (int i=1;i<=N;i++)
        for (auto &j: adj[i])
            if (C[i] != C[j]) {
                adj_scc[C[i]].push_back(C[j]);
                adj_sccr[C[j]].push_back(C[i]);
            }


    //Code below doesn't work because of some dumb fucking segfault

    /*memset(dp,-1,sizeof(dp));

    int res = -1;

    for (int i=2;i<=N;i++)
    {
        if (W[i] == 0) continue;

        int m1 = dfs(adj_scc,0,i,1);
        if (m1 < 0) continue;

        for (auto &v: adj_scc[i])
        {
            int m2 = dfs(adj_sccr,1,v,1);
            if (m2 < 0) continue;

            res = max(res, W[1] + m1 + m2);
        }
    }
    cout << res << '\n';*/

    return 0;
}