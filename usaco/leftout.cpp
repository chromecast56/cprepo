#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxn = 1010;

int n;
int a[maxn][maxn], l[maxn], r[maxn];
void flip(bool is_l,int i) //arr b is arbitrary l or r
{
    int *tl = is_l? l:r;
    int *tr = is_l? r:l;
    tl[i] = n-tl[i];
    for (int j=1;j<=n;j++) {
        int &x = is_l? a[i][j] : a[j][i];
        tr[j] += x? -1:1;
        x = 1-x;
    }
}
int main()
{
    ofstream fout("leftout.out");
    ifstream fin("leftout.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    fin>>n;

    if (n < 3)
        while(1);
    for (int i=1;i<=n;i++) {
        string x;
        fin>>x;
        for (int j=1;j<=n;j++) {
            int b = x[j-1] == 'L'? 0:1;
            a[i][j] += b; l[i] += b; r[j] += b;
        }
    }

    /*Make the edges into L*/
    for (int i=1;i<=n;i++)
        if (a[i][1])
            flip(1,i);

    for (int i=1;i<=n;i++)
        if (a[1][i])
            flip(0,i);

    /*make row/col sums 1*/
    for (int i=1;i<=n;i++)
        if (l[i] > 1)
            flip(1,i);

    for (int i=1;i<=n;i++)
        if (r[i] > 1)
            flip(0,i);

    int res_i, res_j;
    int cnt=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i][j]) {
                cnt++;
                res_i = i;
                res_j = j;
            }
    if (cnt != 1)
        fout << -1 << '\n';
    else
        fout << res_i << ' ' << res_j << '\n';
    return 0;
}