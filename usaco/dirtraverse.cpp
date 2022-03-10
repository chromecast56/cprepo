/*
   Simple solution: Loop over every directory, do a dfs to sum all distances to files
        dfs(i,j) --> dfs at node i, and the distance from our dfs source to i is j

   This is n^2 solution, maybe bronze/silver

   Since the graph is a tree, we can do tree-dp. Call dp[i] the path sum from node i.
   Base case: dp[src], just through direct computation

   Say that dp[j] is known. We know that to get dp[i] (child of j):
        - All nodes under i have their paths shortened (by length of j + '/')
        - All nodes outside of i have their paths lengthened (by "../", or 3)

   Define:
        - j = parent of i
        - l[i] = name length of node i
        - num[i] = number of nodes in subtree of i

    Then the formal dp transformation is:
    dp[i] = dp[j] - num[i]*(l[i]+1) + (num[root]-num[i])*3

    num[i] takes O(n) to calculate, but it can be precomputed in another dfs,
    resulting in final O(n) solution, which is min(dp[i])
 */
#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> adj[100001];
int l[100001], num[100001];
long long dp[100001];

void dfs1(int ind, int len) //dfs to preprocess num[] and dp[src]
{
    if (adj[ind].size()==0) //if its a file, base case
    {
        num[ind]=1;
        dp[1]+=len-1; //add to src
    }
    for (auto &i: adj[ind])
    {
        dfs1(i,len+l[i]+1);
        num[ind]+=num[i];
    }
}
void dfs2(int ind) //tree-dp to fill dp[]
{
    for (auto &i: adj[ind])
    {
        dp[i] = dp[ind] - num[i]*(l[i]+1)+(num[1]-num[i])*3;
        dfs2(i);
    }
}
int main()
{
    ofstream fout("dirtraverse.out");
    ifstream fin("dirtraverse.in");

    fin >> N;
    for (int i=1;i<=N;i++)
    {
        string x; int a;
        fin >> x >> a;
        l[i] = x.size();
        for (int j=0;j<a;j++)
        {
            int b; fin >> b;
            adj[i].push_back(b);
        }
    }
    dfs1(1,0);
    dfs2(1);
    long long res = LONG_LONG_MAX;
    for (int i=1;i<=N;i++)
        if (adj[i].size() != 0) //if its a directory
            res = min(res,dp[i]);

    fout << res << "\n";

    return 0;
}