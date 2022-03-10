#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxx = 210;

int bef, res=0; //bef is # colors k before, res is the net gain after rectangles
int n,k;
int a[maxx][maxx]; //first records all points, then 2d prefix sums it, then converts it into a delta array
int l[maxx], r[maxx];
int sum(int A,int B,int C,int D) {
    return a[C][D] - a[A-1][D] - a[C][B-1] + a[A-1][B-1];
}
void solve()
{
    fill(l,l+maxx,0);
    fill(r,r+maxx,0);
    for (int i1=1;i1<=200;i1++) //at first, l and r represent largest sum w/ edge at j
        for (int i2=i1;i2<=200;i2++) {
            int running_l = 0;
            int running_r = sum(i1,1,i2,200);

            r[0] = max(r[0],running_r);
            for (int j=1;j<=200;j++) {
                running_l += sum(i1,j,i2,j);
                running_r -= sum(i1,j,i2,j);

                l[j] = max(l[j],running_l);
                r[j] = max(r[j],running_r);
            }
        }
    //update to global max
    for (int i=1;i<=200;i++) l[i] = max(l[i],l[i-1]);
    for (int i=200;i>=0;i--) r[i] = max(r[i],r[i+1]);

    for (int i=0;i<=200;i++) {
        res = max(res,l[i]);
        res = max(res,r[i]);
        res = max(res, l[i]+r[i]);
    }
}
int main()
{
   // ofstream fout("paintbarn.out");
  //  ifstream fin("paintbarn.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>k;
    while(n--)  { //NO MORE N
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x1++;x2++;y1++;y2++;
        a[x1][y1]++; a[x2][y2]++; a[x1][y2]--; a[x2][y1]--;
    }
    //psum
    for (int i=1;i<=200;i++)
        for (int j=1;j<=200;j++)
            a[i][j] += a[i-1][j]+a[i][j-1] - a[i-1][j-1];
        //delta, then presum the delta
    for (int i=1;i<=200;i++)
        for (int j=1;j<=200;j++) {
            if (a[i][j]==k-1) a[i][j]=1;
            else if (a[i][j]==k) a[i][j]=-1, bef++;
            else a[i][j]=0;

            a[i][j] += a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }

    solve(); //solve it up/down, and left/right
    for (int i=0;i<=200;i++)
        for (int j=0;j<i;j++)
            swap(a[i][j],a[j][i]);
    solve();
    cout << bef+res << '\n';
    return 0;
}