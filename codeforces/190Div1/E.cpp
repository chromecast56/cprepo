#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int MAXN = 4040;
const int MAXK = 810;
int n,k;
int f[MAXK][MAXN];
int a[MAXN][MAXN];

int cost(int i,int j) { //return pairwise sums in interval (i,j] (no i)
    return (a[j][j]-2*a[i][j]+a[i][i])>>1;
}
void compute(int k,int l,int r,int optl,int optr) { //given a stage of states k, compute it's dp using previous states
    if (l>r) return;
    int m = (l+r)/2;
    pii best = {1e9,-1};
    for (int i=optl; i<=min(m,optr);i++) //calculate f[k][mid]
        best = min(best,{f[k-1][i] + cost(i,m), i});

    f[k][m] = best.F;
    int opt = best.S;
    compute(k,l,m-1,optl,opt);
    compute(k,m+1,r,opt,optr);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);

    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) a[i][j] += a[i-1][j]+a[i][j-1]-a[i-1][j-1];

    for (int i=1;i<=n;i++)
        f[1][i] = cost(0,i);
    for (int i=2;i<=k;i++)
        compute(i,1,n,1,n);

    printf("%d",f[k][n]);

    return 0;
}