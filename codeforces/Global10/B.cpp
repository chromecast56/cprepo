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

int a[1000][1000];
int calc(int i,int j,int n,int m) {
    bool a = i==0 || i==n-1;
    bool b = j==0 || j==m-1;

    if (a&&b) return 2;
    if (a||b) return 3;
    return 4;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n,m; cin>>n>>m;

        bool res = 1;
        for (int i=0;i<n;i++) for (int j=0;j<m;j++) {
            cin>>a[i][j];
            int b = calc(i,j,n,m);
            if (a[i][j] > b)
                res = 0;
            else
                a[i][j] = b;
        }

        if (!res) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j++)
                cout << a[i][j] << ' ';
            cout << endl;
        }
    }

    return 0;
}