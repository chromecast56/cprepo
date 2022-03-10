/*
        Not a simple type of dp:

        Is a style that focuses on intemediates, for every dp[l,r] try to dp[l,k] + [k,r] + c()

        Then instead of just looping on l, looping on r, you instead loop on the difference between l and r, and then on l
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

int dp[101][101];
int n,m;
pii c[101][101]; //each index, store what interval
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>m;
    for (int i=1;i<=n;i++) {
        int k;cin>>k;
        for (int j=0;j<k;j++) {
            int l,r;cin>>l>>r;

            for (int a=l;a<=r;a++)
                c[i][a] = {l,r};
        }
    }

    for (int d=0;d<m;d++)
        for (int l=1;l+d<=m;l++) {
            int r = l+d;
            for (int k=l;k<=r;k++) {
                int numint = 0;
                for (int a=1;a<=n;a++) if (l <= c[a][k].F && c[a][k].S <= r) numint++;
                dp[l][r] = max(dp[l][r], dp[l][k-1] + numint*numint + dp[k+1][r]);

            }
        }

    cout << dp[1][m] << '\n';

    return 0;
}