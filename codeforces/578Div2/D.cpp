#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000;
const int inf = 1e9;

struct state
{
    int l,r; //
};
int n,k;
int G[maxn][maxn];
int f[2][maxn][maxn];
int already_white = 0;
vector<state> v;
bool can_fill(int i,int j) {
    return j >= v[i].l && j <= v[i].r;
}
void solve(bool b)
{
    if (b) for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) {int t=G[i][j]; G[i][j]=G[j][i]; G[j][i]=t;} //swap row and col

    v.clear();
    for (int i=0;i<n;i++) { //for each row find range that it can be stamped to get all white
        int l=-1,r=-1;
        for (int j=0;j<n;j++)
            if (G[i][j]) {
                if (l==-1) l=j;
                r=j;
            }
        if (r-l >= k || l==-1) { //impossible or already white
            v.push_back({inf,-1});
            if (l==-1)
                already_white++;
        }
        else
            v.push_back({r-k+1,l});
    }

    for (int j=0;j<n-k+1;j++) {
        int sum=0;
        for (int i=0;i<n;i++) {
            if (can_fill(i,j)) sum++;
            if (i >= k && can_fill(i-k,j)) sum--;
            if (i+1 >= k)
                f[b][i-k+1][j] = sum;
        }
    }

}
int main()
{
    ios_base::sync_with_stdio(false); //faster I/O
    cin.tie(NULL); //include only for non-interactive problems

    cin>>n>>k;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) {
            char c;cin>>c;
            G[i][j] = c=='B';
        }

    solve(0); solve(1);
    int res=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            res = max(res,f[0][i][j]+f[1][j][i]);

    cout<<res+already_white<<'\n';
    return 0;
}
