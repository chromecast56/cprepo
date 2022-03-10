/*
            Problem Statement:
            - There is an NxN grid, filled with white/black in each (i,j).
            - To color any rectangle with length L and width W white, it costs max(L,W) cost
            - What is the minimum cost of painting the entire grid white?

            Intended solution is to use iterative dp and to maintain 2d prefix sums, but recursive dp is much more intuitive
 */
#include <bits/stdc++.h>

using namespace std;

int n;
string g[51];
bool v[51][51][51][51];
int dp[51][51][51][51];
int solve(int x1,int y1,int x2,int y2)
{
    if (x1>x2 || y1>y2) return 0;
    if(x1==x2 && y1==y2) return g[x1][y1] == '#';
    if (v[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
    v[x1][y1][x2][y2] = 1;

    int res = max(x2-x1+1, y2-y1+1); //max is just cover all first
    for(int row=y1;row<y2;row++) res = min(res,solve(x1,y1,x2,row) + solve(x1,row+1,x2,y2));
    for(int col=x1;col<x2;col++) res = min(res,solve(x1,y1,col,y2) + solve(col+1,y1,x2,y2));

    return dp[x1][y1][x2][y2] = res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i=0;i<n;i++) cin>>g[i];

    cout<<solve(0,0,n-1,n-1)<<'\n';
    return 0;
}