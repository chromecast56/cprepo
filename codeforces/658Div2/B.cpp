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

int f[200000][2]; //0 = first go, 1 = second go
int a[200000];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        for (int i=0;i<n;i++) {
            cin>>a[i];
        }
        f[n-1][0] = 0,f[n-1][1] =  1;
        for (int i=n-2;i>=0;i--)
            for (int j=0;j<2;j++) {
                if (a[i]==1) f[i][j] = f[i+1][1-j];
                else {
                    if (f[i+1][j]==j || f[i+1][1-j]==j) f[i][j] = j;
                    else f[i][j] = 1-j;
                }
            }

        if (!f[0][0]) cout << "First\n"; else cout << "Second\n";
    }

    return 0;
}