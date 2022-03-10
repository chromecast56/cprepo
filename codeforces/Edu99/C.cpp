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

int b[100][2];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n,m;cin>>n>>m;
        int a[31][31];
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                cin>>a[i][j];

         //group 0 = (1,1), group 1 = (2,1),(1,2), etc. until group n+m-1
        //groups i and n+m-1-i must either all be 0 or all be 1 (assuming that i < n+m+1-i)
        //if they are equal the condition does not have to be satisfied (see tc1)
        memset(b,0,sizeof(b));

        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++) //(i,j) contributes to group i+j
                b[i+j][a[i][j]]++;

        int res = 0;
        for (int i=0;i<max(n,m);i++) {
            if (i >= n+m-2-i) break;
            res += min(b[i][0]+b[n+m-2-i][0], b[i][1]+b[n+m-2-i][1]);
        }

        cout << res << '\n';
    }

    return 0;
}