#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t; cin>>t;
    while(t--) {
        int n,m,x,y; cin>>n>>m>>x>>y;
        int a[100][1000];
        for (int i=0;i<n;i++) {
            string x; cin>>x;
            for (int j=0;j<m;j++)
                a[i][j] = x[j];
        }

        bool b = y <= x * 2;
        int res = 0;
        for (int i=0;i<n;i++)
            for (int j=1;j<m;j++)
                if (a[i][j-1] == '.' && a[i][j] == '.' && b)
                    res += y, a[i][j-1] = ',', a[i][j] = ',';

        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                if (a[i][j] == '.')
                    res += x;


                cout << res << '\n';
    }

    return 0;
}