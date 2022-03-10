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
        int n,m; cin>>n>>m;
        int a[51][51];

        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                cin>>a[i][j];

        int res = 0;
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++) {
                bool row = 1, col = 1;

                for (int k=0;k<n;k++)
                    if (a[k][j]) row = 0;
                for (int k=0;k<m;k++)
                    if (a[i][k]) col = 0;

                if (row && col) res++, a[i][j] = 1;
            }
        if (res%2 == 1) cout << "Ashish\n";
        else            cout << "Vivek\n";
    }



    return 0;
}