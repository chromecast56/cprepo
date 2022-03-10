#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;

int a[61][61];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    int t;
    cin>>t;
    while(t--) {
        int r,c;
        cin>>r>>c;
        for (int i=0;i<r;i++) {
            string x;
            cin>>x;
            for (int j=0;j<c;j++)
                a[i][j] = x[j];
        }

        int res = -1;
        for (int i=0;i<r;i++) for (int j=0;j<c;j++) if (a[i][j] == 'A') res = 4;
        bool a1=0,a2=0,a3=0,a4=0;
        bool p1=0,p2=0,p3=0,p4=0;
        for (int i=0;i<r;i++) {
            if (a[i][0]=='A') res = 3, a1=1;
            if (a[i][c-1]=='A') res=3,a2=1;

            if (a[i][0]=='P') p1=1;
            if (a[i][c-1]=='P') p2=1;
        }
        for (int i=0;i<c;i++) {
            if (a[0][i]=='A') res = 3, a3=1;
            if (a[r-1][i]=='A') res=3, a4=1;

            if (a[i][0]=='P') p3=1;
            if (a[i][c-1]=='P') p4=1;
        }

        if (a[0][0]=='A'||a[0][c-1]=='A'||a[r-1][0]=='A'||a[r-1][c-1]=='A') res = 2;

        if (!p1||!p2||!p3||!p4) res = 1;

        if (res==-1) cout << "MORTAL\n";
        else cout << res << '\n';
    }

    return 0;
}